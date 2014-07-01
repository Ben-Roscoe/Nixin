#ifndef NIXIN_UNIFORMVALUES_H
#define NIXIN_UNIFORMVALUES_H


#include "Nixin_Matrix.h"
#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>



namespace Nixin
{



    class Uniform1f
    {
    public:

        Uniform1f();
        Uniform1f( GLfloat v1 );


        GLfloat                     x      = 0.0f;

    };




    class Uniform2f
    {
    public:

        Uniform2f();
        Uniform2f( GLfloat v1, GLfloat v2 );


        GLfloat                     x      = 0.0f;
        GLfloat                     y      = 0.0f;


    };




    class Uniform3f
    {
    public:

        Uniform3f();
        Uniform3f( GLfloat v1, GLfloat v2, GLfloat v3 );



        GLfloat                     x      = 0.0f;
        GLfloat                     y      = 0.0f;
        GLfloat                     z      = 0.0f;

    };



    class Uniform4f
    {
    public:

        Uniform4f();
        Uniform4f( GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4 );


        GLfloat                     x      = 0.0f;
        GLfloat                     y      = 0.0f;
        GLfloat                     z      = 0.0f;
        GLfloat                     w      = 0.0f;
    };




    class Uniform1fv
    {
    public:

        Uniform1fv();
        Uniform1fv( const GLfloat* value, GLsizei valueCount );


        const GLfloat*              v       = nullptr;
        GLsizei                     count   = 0;
    };




    class Uniform2fv
    {
    public:

        Uniform2fv();
        Uniform2fv( const GLfloat* value, GLsizei valueCount );


        const GLfloat*              v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform3fv
    {
    public:

        Uniform3fv();
        Uniform3fv( const GLfloat* value, GLsizei valueCount );


        const GLfloat*              v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform4fv
    {
    public:

        Uniform4fv();
        Uniform4fv( const GLfloat* value, GLsizei valueCount );


        const GLfloat*              v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform1i
    {
    public:

        Uniform1i();
        Uniform1i( GLint v1 );


        GLint                       x      = 0;
    };



    class Uniform2i
    {
    public:

        Uniform2i();
        Uniform2i( GLint v1, GLint v2 );


        GLint                       x      = 0;
        GLint                       y      = 0;
    };



    class Uniform3i
    {
    public:

        Uniform3i();
        Uniform3i( GLint v1, GLint v2, GLint v3 );


        GLint                       x      = 0;
        GLint                       y      = 0;
        GLint                       z      = 0;
    };



    class Uniform4i
    {
    public:

        Uniform4i();
        Uniform4i( GLint v1, GLint v2, GLint v3, GLint v4 );


        GLint                       x      = 0;
        GLint                       y      = 0;
        GLint                       z      = 0;
        GLint                       w      = 0;
    };



    class Uniform1iv
    {
    public:

        Uniform1iv();
        Uniform1iv( const GLint* value, GLsizei valueCount );


        const GLint*                v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform2iv
    {
    public:

        Uniform2iv();
        Uniform2iv( const GLint* value, GLsizei valueCount );


        const GLint*                v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform3iv
    {
    public:

        Uniform3iv();
        Uniform3iv( const GLint* value, GLsizei valueCount );


        const GLint*                v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform4iv
    {
    public:

        Uniform4iv();
        Uniform4iv( const GLint* value, GLsizei valueCount );


        const GLint*                v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform1ui
    {
    public:

        Uniform1ui();
        Uniform1ui( GLuint v1 );


        GLuint                      x      = 0;
    };



    class Uniform2ui
    {
    public:

        Uniform2ui();
        Uniform2ui( GLuint v1, GLuint v2 );


        GLuint                      x      = 0;
        GLuint                      y      = 0;
    };



    class Uniform3ui
    {
    public:

        Uniform3ui();
        Uniform3ui( GLuint v1, GLuint v2, GLuint v3 );


        GLuint                      x      = 0;
        GLuint                      y      = 0;
        GLuint                      z      = 0;
    };



    class Uniform4ui
    {
    public:

        Uniform4ui();
        Uniform4ui( GLuint v1, GLuint v2, GLuint v3, GLuint v4 );


        GLuint                      x      = 0;
        GLuint                      y      = 0;
        GLuint                      z      = 0;
        GLuint                      w      = 0;
    };



    class Uniform1uiv
    {
    public:

        Uniform1uiv();
        Uniform1uiv( const GLuint* value, GLsizei valueCount );


        const GLuint*               v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform2uiv
    {
    public:

        Uniform2uiv();
        Uniform2uiv( const GLuint* value, GLsizei valueCount );


        const GLuint*               v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform3uiv
    {
    public:

        Uniform3uiv();
        Uniform3uiv( const GLuint* value, GLsizei valueCount );


        const GLuint*               v       = nullptr;
        GLsizei                     count   = 0;
    };



    class Uniform4uiv
    {
    public:

        Uniform4uiv();
        Uniform4uiv( const GLuint* value, GLsizei valueCount );


        const GLuint*               v       = nullptr;
        GLsizei                     count   = 0;
    };



    class UniformMatrix
    {
    public:

        UniformMatrix();
        UniformMatrix( const Matrix& v );


        const Matrix                       matrix;


    };



    class UniformMatrixv
    {
    public:

        UniformMatrixv();
        UniformMatrixv( const Matrix* v, GLsizei matrixCount );


        const Matrix*                       matrices        = nullptr;
        GLsizei                             count           = 0;


    };



    class UniformSampler2D
    {
    public:

        UniformSampler2D();
        UniformSampler2D( GLuint v, GLenum textureLocation, GLboolean bound );


        GLuint             value                            = 0;
        GLenum             location                         = 0;
        GLboolean          isBound                          = false;
    };

}


#endif // NIXIN_UNIFORMVALUES_H
