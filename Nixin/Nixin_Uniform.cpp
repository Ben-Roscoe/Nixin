#include "Nixin_Uniform.h"



namespace Nixin
{



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1f& value )
    {
        gl->glUniform1f( location, value.x );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2f& value )
    {
        gl->glUniform2f( location, value.x, value.y );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3f& value )
    {
        gl->glUniform3f( location, value.x, value.y, value.z );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4f& value )
    {
        gl->glUniform4f( location, value.x, value.y, value.z, value.w );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1fv& value )
    {
        gl->glUniform1fv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2fv& value )
    {
        gl->glUniform2fv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3fv& value )
    {
        gl->glUniform3fv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4fv& value )
    {
        gl->glUniform4fv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1i& value )
    {
        gl->glUniform1i( location, value.x );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2i& value )
    {
        gl->glUniform2i( location, value.x, value.y );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3i& value )
    {
        gl->glUniform3i( location, value.x, value.y, value.z );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4i& value )
    {
        gl->glUniform4i( location, value.x, value.y, value.z, value.w );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1iv& value )
    {
        gl->glUniform1iv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2iv& value )
    {
        gl->glUniform2iv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3iv& value )
    {
        gl->glUniform3iv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4iv& value )
    {
        gl->glUniform4iv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1ui& value )
    {
        gl->glUniform1ui( location, value.x );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2ui& value )
    {
        gl->glUniform2ui( location, value.x, value.y );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3ui& value )
    {
        gl->glUniform3ui( location, value.x, value.y, value.z );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4ui& value )
    {
        gl->glUniform4ui( location, value.x, value.y, value.z, value.w );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1uiv& value )
    {
        gl->glUniform1uiv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2uiv& value )
    {
        gl->glUniform2uiv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3uiv& value )
    {
        gl->glUniform3uiv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4uiv& value )
    {
        gl->glUniform4uiv( location, value.count, value.v );
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions* gl, GLint location, const UniformMatrix& value )
    {
        switch( value.matrix.GetRows() )
        {
            case 2:
            {
                if( value.matrix.GetColumns() == 2 )
                {
                    gl->glUniformMatrix2fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 3 )
                {
                    gl->glUniformMatrix2x3fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 4 )
                {
                    gl->glUniformMatrix2x4fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
            }
            case 3:
            {
                if( value.matrix.GetColumns() == 3 )
                {
                    gl->glUniformMatrix3fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 4 )
                {
                    gl->glUniformMatrix3x4fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 2 )
                {
                    gl->glUniformMatrix3x2fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
            }
            case 4:
            {
                if( value.matrix.GetColumns() == 4 )
                {
                    gl->glUniformMatrix4fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 2 )
                {
                    gl->glUniformMatrix4x2fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
                else if( value.matrix.GetColumns() == 3 )
                {
                    gl->glUniformMatrix4x3fv( location, 1, GL_TRUE, value.matrix.GetData() );
                }
            }
        }
    }



    //
    // SetUniform
    //
    void SetUniform( OpenGLFunctions *gl, GLint location, const UniformSampler2D& value )
    {
        if( !value.isBound )
        {
            gl->glActiveTexture( value.location );
            gl->glBindTexture( GL_TEXTURE_2D, value.value );
        }
        gl->glUniform1ui( location, value.location );
    }

}
