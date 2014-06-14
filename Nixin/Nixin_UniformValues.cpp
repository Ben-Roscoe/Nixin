#include "Nixin_UniformValues.h"



namespace Nixin
{



    //
    // Uniform1f
    //
    Uniform1f::Uniform1f()
    {
    }



    //
    // Uniform1f
    //
    Uniform1f::Uniform1f( GLfloat v1 )
    {
        x = v1;
    }



    //
    // Uniform2f
    //
    Uniform2f::Uniform2f()
    {
    }



    //
    // Uniform2f
    //
    Uniform2f::Uniform2f( GLfloat v1, GLfloat v2 )
    {
        x = v1;
        y = v2;
    }



    //
    // Uniform3f
    //
    Uniform3f::Uniform3f()
    {
    }



    //
    // Uniform3f
    //
    Uniform3f::Uniform3f( GLfloat v1, GLfloat v2, GLfloat v3 )
    {
        x = v1;
        y = v2;
        z = v3;
    }



    //
    // Uniform4f
    //
    Uniform4f::Uniform4f()
    {
    }



    //
    // Uniform4f
    //
    Uniform4f::Uniform4f( GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4 )
    {
        x = v1;
        y = v2;
        z = v3;
        w = v4;
    }



    //
    // Uniform1fv
    //
    Uniform1fv::Uniform1fv()
    {
    }



    //
    // Uniform1fv
    //
    Uniform1fv::Uniform1fv( const GLfloat* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform2fv
    //
    Uniform2fv::Uniform2fv()
    {
    }



    //
    // Uniform2fv
    //
    Uniform2fv::Uniform2fv( const GLfloat* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }


    //
    // Uniform3fv
    //
    Uniform3fv::Uniform3fv()
    {
    }



    //
    // Uniform3fv
    //
    Uniform3fv::Uniform3fv( const GLfloat* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform4fv
    //
    Uniform4fv::Uniform4fv()
    {
    }



    //
    // Uniform4fv
    //
    Uniform4fv::Uniform4fv( const GLfloat* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform1i
    //
    Uniform1i::Uniform1i()
    {
    }



    //
    // Uniform1i
    //
    Uniform1i::Uniform1i( GLint v1 )
    {
        x = v1;
    }



    //
    // Uniform2i
    //
    Uniform2i::Uniform2i()
    {
    }



    //
    // Uniform2i
    //
    Uniform2i::Uniform2i( GLint v1, GLint v2 )
    {
        x = v1;
        y = v2;
    }



    //
    // Uniform3i
    //
    Uniform3i::Uniform3i()
    {
    }



    //
    // Uniform3i
    //
    Uniform3i::Uniform3i( GLint v1, GLint v2, GLint v3 )
    {
        x = v1;
        y = v2;
        z = v3;
    }



    //
    // Uniform4i
    //
    Uniform4i::Uniform4i()
    {
    }



    //
    // Uniform4i
    //
    Uniform4i::Uniform4i( GLint v1, GLint v2, GLint v3, GLint v4 )
    {
        x = v1;
        y = v2;
        z = v3;
        w = v4;
    }



    //
    // Uniform1iv
    //
    Uniform1iv::Uniform1iv()
    {
    }



    //
    // Uniform1iv
    //
    Uniform1iv::Uniform1iv( const GLint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform2iv
    //
    Uniform2iv::Uniform2iv()
    {
    }



    //
    // Uniform2iv
    //
    Uniform2iv::Uniform2iv( const GLint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform3iv
    //
    Uniform3iv::Uniform3iv()
    {
    }



    //
    // Uniform3iv
    //
    Uniform3iv::Uniform3iv( const GLint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform4iv
    //
    Uniform4iv::Uniform4iv()
    {
    }



    //
    // Uniform4iv
    //
    Uniform4iv::Uniform4iv( const GLint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform1ui
    //
    Uniform1ui::Uniform1ui()
    {
    }



    //
    // Uniform1ui
    //
    Uniform1ui::Uniform1ui( GLuint v1 )
    {
        x = v1;
    }



    //
    // Uniform2ui
    //
    Uniform2ui::Uniform2ui()
    {
    }



    //
    // Uniform2ui
    //
    Uniform2ui::Uniform2ui( GLuint v1, GLuint v2 )
    {
        x = v1;
        y = v2;
    }



    //
    // Uniform3ui
    //
    Uniform3ui::Uniform3ui()
    {
    }



    //
    // Uniform3ui
    //
    Uniform3ui::Uniform3ui( GLuint v1, GLuint v2, GLuint v3 )
    {
        x = v1;
        y = v2;
        z = v3;
    }



    //
    // Uniform4ui
    //
    Uniform4ui::Uniform4ui()
    {
    }



    //
    // Uniform4ui
    //
    Uniform4ui::Uniform4ui( GLuint v1, GLuint v2, GLuint v3, GLuint v4 )
    {
        x = v1;
        y = v2;\
        z = v3;
        w = v4;
    }



    //
    // Uniform1uiv
    //
    Uniform1uiv::Uniform1uiv()
    {
    }



    //
    // Uniform1uiv
    //
    Uniform1uiv::Uniform1uiv( const GLuint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform2uiv
    //
    Uniform2uiv::Uniform2uiv()
    {
    }



    //
    // Uniform2uiv
    //
    Uniform2uiv::Uniform2uiv( const GLuint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform3uiv
    //
    Uniform3uiv::Uniform3uiv()
    {
    }



    //
    // Uniform3uiv
    //
    Uniform3uiv::Uniform3uiv( const GLuint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // Uniform4uiv
    //
    Uniform4uiv::Uniform4uiv()
    {
    }



    //
    // Uniform4uiv
    //
    Uniform4uiv::Uniform4uiv( const GLuint* value, GLsizei valueCount )
    {
        v       = value;
        count   = valueCount;
    }



    //
    // UniformMatrix
    //
    UniformMatrix::UniformMatrix()
    {
    }



    //
    // UniformMatrix
    //
    UniformMatrix::UniformMatrix( const Matrix& v )
    {
        matrix = v;
    }



    //
    // UniformMatrixv
    //
    UniformMatrixv::UniformMatrixv()
    {
    }



    //
    // UniformMatrixv
    //
    UniformMatrixv::UniformMatrixv( const Matrix* v, GLsizei matrixCount )
    {
        matrices    = v;
        count       = matrixCount;
    }

}

