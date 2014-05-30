#ifndef NIXIN_RENDERBUFFER_H
#define NIXIN_RENDERBUFFER_H

#include <QOpenGLFunctions_4_3_Core>x
#include <memory>

#include "Nixin_Point.h"
#include "Nixin_Rectangle.h"
#include "Nixin_Types.h"



namespace Nixin
{
    class Renderbuffer
    {



    public:


        static const GLenum                     target              = GL_RENDERBUFFER;


        Renderbuffer();
        Renderbuffer( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat );
        Renderbuffer( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat, GLsizei samples );
        Renderbuffer( Renderbuffer&& other );
        Renderbuffer& operator=( Renderbuffer&& other );
        ~Renderbuffer();

        // Disable copying. Renderbuffers can still be copied through framebuffers, however
        // this must be done manually.
        Renderbuffer( const Renderbuffer& other )               = delete;
        Renderbuffer& operator=( const Renderbuffer& other )    = delete;

        void                                    swap( Renderbuffer& a, Renderbuffer& b );

        GLuint                                  GetID() const;
        void                                    Bind() const;
        void                                    SetStorage( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat );
        void                                    SetStorage( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat, GLsizei samples );


        bool                                    IsMultisampled() const;
        GLsizei                                 SampleCount() const;
        GLsizei                                 Width() const;
        GLsizei                                 Height() const;
        Point                                   Size() const;
        Rectangle                               Bounds() const;
        GLenum                                  InternalFormat() const;


    private:



        OpenGLFunctions*                        gl                  = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                                  id                  = 0;
        GLenum                                  internalFormat      = GL_NONE;
        GLsizei                                 width               = 0;
        GLsizei                                 height              = 0;

        // Is the renderbuffer multisampled?
        bool                                    multisampled        = false;
        GLsizei                                 sampleCount         = 0;


        void                                    GenRenderbuffer();

    };
}




#endif // NIXIN_RENDERBUFFER_H
