#include "Nixin_ShaderFile.h"
#include "Nixin_Debug.h"
#include "Nixin_Utility.h"

#include <locale>
#include <numeric>


namespace Nixin
{



    //Public:



    //
    // ShaderFile
    //
    ShaderFile::ShaderFile( GLenum shaderType )
    {
        type = shaderType;
        GenFile();
    }



    //
    // ShaderFile
    //
    ShaderFile::ShaderFile( const std::string& fileName, GLenum shaderType, bool compileShader )
    {
        type = shaderType;
        GenFile();
        LoadSourceFromFile( fileName );

        if( compileShader )
        {
            Compile();
        }
    }



    //
    // ShaderFile
    //
    ShaderFile::ShaderFile( const ShaderFile& other )
    {
        gl          = other.gl;
        type        = other.type;
        source      = other.source;
        compiled    = other.compiled;

        if( other.id != 0 )
        {
            GenFile();

            const char* src = source.c_str();
            gl->glShaderSource( id, 1, &src, nullptr );

            if( compiled )
            {
                Compile();
            }
        }
    }




    //
    // ShaderFile
    //
    ShaderFile::ShaderFile( ShaderFile&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    ShaderFile& ShaderFile::operator=( ShaderFile other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // ~ShaderFile
    //
    ShaderFile::~ShaderFile()
    {
        if( id != 0 )
        {
            gl->glDeleteShader( id );
        }
    }



    //
    // swap
    //
    void swap( ShaderFile& a, ShaderFile& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
        swap( a.type, b.type );
        swap( a.source, b.source );
        swap( a.compiled, b.compiled );
    }



    //
    // Compile
    //
    bool ShaderFile::Compile()
    {
        if( source.empty() )
        {
            Debug::Warning( "Attempted to compile shader file with no source." );
            return false;
        }

        // Store a temporary pointer so we can pass a char** to OpenGL.
        const char*         sourcePtr = source.c_str();

        gl->glShaderSource( id, 1, &sourcePtr, nullptr );
        gl->glCompileShader( id );

        GLint       success = 0;
        gl->glGetShaderiv( id, GL_COMPILE_STATUS, &success );
        if( static_cast<GLboolean>( success ) == GL_TRUE )
        {
            compiled = true;
            GenerateMetaData();
            return true;
        }
        else
        {
            GLint            length  = 0;
            gl->glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length );

            std::string      errorMessage;
            errorMessage.resize( length + 1, '\0' );
            gl->glGetShaderInfoLog( id, length, nullptr, &errorMessage[0] );

            Debug::Write( "GLSL Compilation Error: %s", errorMessage.c_str() );
            return false;
        }
    }



    //
    // GetAttributes
    //
    const std::vector<Field>& ShaderFile::GetAttributes() const
    {
        return attributeFields;
    }



    //
    // GetUniforms
    //
    const std::vector<Field> &ShaderFile::GetUniforms() const
    {
        return uniformFields;
    }



    //
    //
    //
    const std::map<std::string, UniformType>& ShaderFile::GetUniformTypes() const
    {
        return uniformTypes;
    }



    //
    // GetId
    //
    GLuint ShaderFile::GetID() const
    {
        return id;
    }



    //
    // GetType
    //
    GLenum ShaderFile::GetType() const
    {
        return type;
    }



    //
    // IsCompiled
    //
    bool ShaderFile::IsCompiled() const
    {
        return compiled;
    }



    //
    // GetSource
    //
    const std::string& ShaderFile::GetSource() const
    {
        return source;
    }



    //
    // GetSource
    //
    std::string& ShaderFile::GetSource()
    {
        return source;
    }



    //
    // SetSource
    //
    void ShaderFile::SetSource( const std::string& fileSource )
    {
        source = fileSource;
    }



    //
    // LoadSourceFromFile
    //
    void ShaderFile::LoadSourceFromFile( const std::string& fileName )
    {
        source = Utility::GetFileText( fileName );
    }



    // Private:



    //
    // GenFile
    //
    void ShaderFile::GenFile()
    {
        id = gl->glCreateShader( type );
        if( id == 0 )
        {
            Debug::PrintGLError( gl->glGetError(), "glCreateShader" );
            Debug::FatalError( "glCreateShader failed to create the shader object." );
        }
    }



    //
    // GenerateMetaData
    //
    void ShaderFile::GenerateMetaData()
    {
        // The source might have changed, so forget all we know about this shader.
        uniformFields.clear();
        uniformTypes.clear();

        // The last place the "in" keyword was found.
        size_t       last = 0;
        std::array<std::string, 3> tokens{ "in", "struct", "uniform" };
        while( true )
        {
            // Find the closest token to our position in the source.
            size_t      closest = source.npos;
            size_t      token   = 0;
            for( size_t i = 0; i < tokens.size(); i++ )
            {
                size_t   position = source.find( tokens[i], last );
                if( position < closest )
                {
                    closest = position;
                    token = i;
                }
            }
            last = closest;

            // If one of the tokens were found.
            if( last != source.npos )
            {
                // Make sure there is either a whitespace or semi-colon before and after a token, otherwise it part of an identifier or keyword. We don't want to deal
                // with those.
                if( std::isspace( source[last + tokens[token].size()], std::locale( "C" ) ) && ( std::isspace( source[last - 1], std::locale( "C" ) ) || source[last - 1] == ';' ) )
                {
                    // Check the first character to see if we found an "in", "struct", or "uniform" keyword.
                    switch( source[last] )
                    {
                        // "in"
                        case 'i':
                        {
                            // Get the line.
                            std::string  line       = source.substr( last, source.find( ';', last ) - last );

                            // Get the type.
                            Utility::TrimToWhiteSpace( line );
                            Utility::TrimTrailingWhiteSpace( line );
                            std::string  type       = line.substr( 0, Utility::IndexOfNextWhiteSpace( line ) );

                            // Get the name.
                            Utility::TrimToWhiteSpace( line );
                            Utility::TrimTrailingWhiteSpace( line );
                            std::string  name       = line.substr( 0, line.size() );

                            attributeFields.push_back( Field( name, type ) );
                            break;
                        }
                        // "struct"
                        case 's':
                        {
                            // Get the struct block.
                            std::string                     structBlock       = source.substr( last, source.find( '}', last ) - last );
                            Utility::TrimToWhiteSpace( structBlock );
                            Utility::TrimTrailingWhiteSpace( structBlock );
                            UniformType                     type( structBlock.substr( 0, Utility::IndexOfNextWhiteSpace( structBlock ) ) );

                            structBlock = structBlock.substr( structBlock.find( "{" ) + 1 );

                            // Add all the fields until we reach the end of the struct block.
                            while( true )
                            {
                                Field           field( "", "" );

                                Utility::TrimToWhiteSpace( structBlock );
                                Utility::TrimTrailingWhiteSpace( structBlock );
                                field.type = structBlock.substr( 0, Utility::IndexOfNextWhiteSpace( structBlock ) );
                                Utility::TrimToWhiteSpace( structBlock );
                                Utility::TrimTrailingWhiteSpace( structBlock );
                                field.name = structBlock.substr( 0, Utility::IndexOfNext( structBlock, ';' ) );
                                Utility::TrimToNext( structBlock, ';' );

                                if( structBlock.size() > 0 )
                                {
                                    type.members.push_back( field );
                                }
                                else
                                {
                                    break;
                                }
                            }

                            uniformTypes[type.name] = type;
                            break;
                        }
                        // "uniform"
                        case 'u':
                        {
                            // Get the line.
                            std::string  line       = source.substr( last, source.find( ';', last ) - last );

                            // Get the type.
                            Utility::TrimToWhiteSpace( line );
                            Utility::TrimTrailingWhiteSpace( line );
                            std::string  type       = line.substr( 0, Utility::IndexOfNextWhiteSpace( line ) );

                            // Get the name.
                            Utility::TrimToWhiteSpace( line );
                            Utility::TrimTrailingWhiteSpace( line );
                            std::string  name       = line.substr( 0, line.size() );

                            uniformFields.push_back( Field( name, type ) );
                            break;
                        }
                    }
                }
                last += tokens[token].size();
            }
            else
            {
                break;
            }
        }
    }
}
