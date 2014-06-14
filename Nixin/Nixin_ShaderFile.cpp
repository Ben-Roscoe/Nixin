#include "Nixin_ShaderFile.h"
#include "Nixin_Debug.h"
#include "Nixin_Utility.h"

#include <locale>


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

        gl->glCompileShader( id );

        GLint       success = 0;
        gl->glGetShaderiv( id, GL_COMPILE_STATUS, &success );
        if( static_cast<GLboolean>( success ) == GL_TRUE )
        {
            compiled = true;
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
        uniformFields.clear();
        uniformTypes.clear();


        // Read every type.
        size_t              pos   = 0;
        size_t              end   = 0;


        pos   = source.find( "{", source.find( "struct", pos ) );
        end   = source.find( ";", source.find( "}", pos ) );

        std::string structDefinition  = source.substr( pos, end - pos );

        while( pos != end )
        {
            std::string field             = structDefinition.substr( pos + 1, structDefinition.find( ";", pos ) - pos );

            for( size_t i = field.begin(); std::isspace( field[i], std::locale( "C" ) ); i++ )
            {
                field.erase( i );
            }

            std::string         type = "";
            for( size_t i = field.begin(); !std::isspace( field[i], std::locale( "C" ) ); i++ )
            {
                type.push_back( field[i] );
            }

            field.erase( field.begin(), type.size() );
            for( size_t i = field.begin(); std::isspace( field[i], std::locale( "C" ) ); i++ )
            {
                field.erase( i );
            }

            std::string name = "";
            for( size_t i = field.begin(); !std::isspace( field[i], std::locale( "C" ) ); i++ )
            {
                name.push_back( field[i] );
            }

            pos = structDefinition.find( ";", pos ) + 1;
        }
    }
}
