#include <iostream>


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
    }



    //
    // RemoveFile
    //
    void ShaderProgram::RemoveFile( const ShaderFile &shaderFile )
    {
        gl->glDetachShader( id, shaderFile.GetID() );
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
    // GenerateUniforms
    //
    void ShaderProgram::GeneratorUniforms()
    {
        uniforms.clear();


    }
}
