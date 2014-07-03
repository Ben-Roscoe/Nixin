#include <iostream>
#include <numeric>


#include "Nixin_ShaderProgram.h"
#include "Nixin_Utility.h"
#include "Nixin_Debug.h"





namespace Nixin
{


    // Public:



    //
    // ShaderProgram
    //
    ShaderProgram::ShaderProgram()
    {
        GenProgram();
    }



    //
    // ShaderProgram
    //
    ShaderProgram::ShaderProgram( ShaderProgram&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    ShaderProgram& ShaderProgram::operator=( ShaderProgram&& other )
    {
        swap( *this, other );
        return					*this;
    }



    //
    // ~ShaderProgram
    //
    ShaderProgram::~ShaderProgram()
    {
        if( id != 0 )
        {
            gl->glDeleteProgram( id );
        }
    }



    //
    // swap
    //
    void swap( ShaderProgram& a, ShaderProgram& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
        swap( a.linked, b.linked );
        swap( a.uniforms, b.uniforms );
    }



    //
    // GetID
    //
    GLuint ShaderProgram::GetID() const
    {
        return id;
    }



    //
    // LinkProgram
    //
    bool ShaderProgram::LinkProgram()
    {
        gl->glLinkProgram( id );

        // Check for errors.
        GLint              success = 0;
        gl->glGetProgramiv( id, GL_LINK_STATUS, &success );
        if( static_cast<GLboolean>( success ) == GL_TRUE )
        {
            linked = true;
            AddMetaData();
            return true;
        }
        else
        {
            GLint          length = 0;
            gl->glGetProgramiv( id, GL_INFO_LOG_LENGTH, &length );

            std::string errorMessage;
            errorMessage.resize( length + 1, '\0' );
            gl->glGetProgramInfoLog( id, length, nullptr, &errorMessage[0] );

            Debug::Write( "GLSL Link Error: %s", errorMessage.c_str() );
            return false;
        }
    }



    //
    // AddFile
    //
    void ShaderProgram::AddFile( const ShaderFile& shaderFile )
    {
        gl->glAttachShader( id, shaderFile.GetID() );

        for( const Field& field : shaderFile.GetAttributes() )
        {
            std::vector<Field>::iterator  result = std::find_if( attributeInfo.begin(), attributeInfo.end(), [&]( const Field& f ){ return f.name == field.name; } );
            if( result != attributeInfo.end() )
            {
                result->count++;
            }
            else
            {
                attributeInfo.push_back( field );
            }
        }


        // Add every uniform.
        for( const Field& field : shaderFile.GetUniforms() )
        {
            std::vector<Field>::iterator  result = std::find_if( uniformInfo.begin(), uniformInfo.end(), [&]( const Field& f ){ return f.name == field.name; } );
            if( result != uniformInfo.end() )
            {
                result->count++;
            }
            else
            {
                uniformInfo.push_back( field );
            }
        }

        // Add every type.
        types.insert( shaderFile.GetUniformTypes().begin(), shaderFile.GetUniformTypes().end() );
    }



    //
    // RemoveFile
    //
    void ShaderProgram::RemoveFile( const ShaderFile& shaderFile )
    {
        gl->glDetachShader( id, shaderFile.GetID() );

        for( const Field& field : shaderFile.GetAttributes() )
        {
            std::vector<Field>::iterator  result = std::find_if( attributeInfo.begin(), attributeInfo.end(), [&]( const Field& f ){ return f.name == field.name; } );
            if( result != attributeInfo.end() )
            {
                if( result->count > 1 )
                {
                    result->count--;
                }
                else
                {
                    attributeInfo.erase( result );
                }
            }
        }
    }



    //
    // EnableAttribute
    //
    void ShaderProgram::EnableAttribute( const std::string& name ) const
    {
        gl->glEnableVertexAttribArray( attributes.at( name ).GetID() );
    }



    //
    // EnableAllAttributes
    //
    void ShaderProgram::EnableAllAttributes() const
    {
        std::for_each( attributes.begin(), attributes.end(), [&]( const std::pair<std::string, VertexAttribute>& pair ){ gl->glEnableVertexAttribArray( pair.second.GetID() ); } );
    }



    //
    // DisableAttribute
    //
    void ShaderProgram::DisableAttribute( const std::string& name ) const
    {
        gl->glDisableVertexAttribArray( attributes.at( name ).GetID() );
    }



    //
    // DisableAllAttributes
    //
    void ShaderProgram::DisableAllAttributes() const
    {
        std::for_each( attributes.begin(), attributes.end(), [&]( const std::pair<std::string, VertexAttribute>& pair ){ gl->glDisableVertexAttribArray( pair.second.GetID() ); } );
    }



    //
    // SetAttribute
    //
    void ShaderProgram::SetAttribute( const std::string& name, int size, GLboolean normalised, GLenum type, int stride, int offset )
    {
        attributes[name].SetValue( size, type, normalised, stride, offset );
    }



    // Private:




    //
    // GenProgram
    //
    void ShaderProgram::GenProgram()
    {
        id = gl->glCreateProgram();
        if( id == 0 )
        {
            Debug::PrintGLError( gl->glGetError(), "glCreateProgram" );
            Debug::FatalError( "glCreateProgram failed to create the program object." );
        }
    }



    //
    // AddMetaData
    //
    void ShaderProgram::AddMetaData()
    {
        // Files might have been added / removed. Forget all meta data.
        attributes.clear();
        uniforms.clear();

        // Add all attributes.
        for( const Field& field : attributeInfo )
        {
            attributes[field.name] = VertexAttribute( field.name, this );
        }

        EnableAllAttributes();


        for( const Field& field : uniformInfo )
        {
            auto    itr = types.find( field.type );

            if( itr == types.end() )
            {
                AddUniform( field.name, field.type );
            }
            else
            {
                AddUniformStruct( field.name, itr->second );
            }
        }
    }



    //
    // AddUniformStruct
    //
    void ShaderProgram::AddUniformStruct( const std::string& name, const UniformType& type )
    {
        for( const Field& field : type.members )
        {
            auto    itr = types.find( field.type );
            if( itr == types.end() )
            {
                AddUniform( name + "." + field.name, field.type );
            }
            else
            {
                AddUniformStruct( name + "." + itr->second.name, itr->second );
            }
        }
    }



    //
    // AddUniform
    //
    void ShaderProgram::AddUniform( const std::string& name, const std::string& type )
    {
        size_t          typeValue = std::accumulate( type.begin(), type.end(), 0 );

        // It's a matrix.
        if( type.size() > 3 && type[0] == 'm' && type[1] == 'a' && type[2] == 't' )
        {
            uniforms[name] = std::unique_ptr<Uniform<UniformMatrix>>( new Uniform<UniformMatrix>( name, this ) );
        }
        else
        {
            switch( typeValue )
            {
                case 'v' + 'e' + 'c' + '2': uniforms[name] = std::unique_ptr<Uniform<Uniform2f>>( new Uniform<Uniform2f>( name, this ) ); break;
                case 'v' + 'e' + 'c' + '3': uniforms[name] = std::unique_ptr<Uniform<Uniform3f>>( new Uniform<Uniform3f>( name, this ) ); break;
                case 'v' + 'e' + 'c' + '4': uniforms[name] = std::unique_ptr<Uniform<Uniform4f>>( new Uniform<Uniform4f>( name, this ) ); break;

                case 'b' + 'v' + 'e' + 'c' + '2': uniforms[name] = std::unique_ptr<Uniform<Uniform2i>>( new Uniform<Uniform2i>( name, this ) ); break;
                case 'b' + 'v' + 'e' + 'c' + '3': uniforms[name] = std::unique_ptr<Uniform<Uniform3i>>( new Uniform<Uniform3i>( name, this ) ); break;
                case 'b' + 'v' + 'e' + 'c' + '4': uniforms[name] = std::unique_ptr<Uniform<Uniform4i>>( new Uniform<Uniform4i>( name, this ) ); break;

                case 'i' + 'v' + 'e' + 'c' + '2': uniforms[name] = std::unique_ptr<Uniform<Uniform2i>>( new Uniform<Uniform2i>( name, this ) ); break;
                case 'i' + 'v' + 'e' + 'c' + '3': uniforms[name] = std::unique_ptr<Uniform<Uniform3i>>( new Uniform<Uniform3i>( name, this ) ); break;
                case 'i' + 'v' + 'e' + 'c' + '4': uniforms[name] = std::unique_ptr<Uniform<Uniform4i>>( new Uniform<Uniform4i>( name, this ) ); break;

                case 'u' + 'v' + 'e' + 'c' + '2': uniforms[name] = std::unique_ptr<Uniform<Uniform2ui>>( new Uniform<Uniform2ui>( name, this ) ); break;
                case 'u' + 'v' + 'e' + 'c' + '3': uniforms[name] = std::unique_ptr<Uniform<Uniform3ui>>( new Uniform<Uniform3ui>( name, this ) ); break;
                case 'u' + 'v' + 'e' + 'c' + '4': uniforms[name] = std::unique_ptr<Uniform<Uniform4ui>>( new Uniform<Uniform4ui>( name, this ) ); break;

                case 'd' + 'v' + 'e' + 'c' + '3': uniforms[name] = std::unique_ptr<Uniform<Uniform3f>>( new Uniform<Uniform3f>( name, this ) ); break;
                case 'd' + 'v' + 'e' + 'c' + '4': uniforms[name] = std::unique_ptr<Uniform<Uniform4f>>( new Uniform<Uniform4f>( name, this ) ); break;

                case 'b' + 'o' + 'o' + 'l':                                 uniforms[name] = std::unique_ptr<Uniform<Uniform1i>>( new Uniform<Uniform1i>( name, this ) ); break;
                case 'i' + 'n' + 't':                                       uniforms[name] = std::unique_ptr<Uniform<Uniform1i>>( new Uniform<Uniform1i>( name, this ) ); break;
                case 'f' + 'l' + 'o' + 'a' + 't':                           uniforms[name] = std::unique_ptr<Uniform<Uniform1f>>( new Uniform<Uniform1f>( name, this ) ); break;
                case 'd' + 'o' + 'u' + 'b' + 'l' + 'e':                     uniforms[name] = std::unique_ptr<Uniform<Uniform1f>>( new Uniform<Uniform1f>( name, this ) ); break;
                case 's' + 'a' + 'm' + 'p' + 'l' + 'e' + 'r' + '2' + 'D':   uniforms[name] = std::unique_ptr<Uniform<UniformSampler2D>>( new Uniform<UniformSampler2D>( name, this ) ); break;

                default: uniforms[name] = std::unique_ptr<Uniform<Uniform2f>>( new Uniform<Uniform2f>( name, this ) );
            }
        }
    }
}
