#ifndef NIXIN_TEXTUREBASE_H
#define NIXIN_TEXTUREBASE_H



#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>
#include <memory>


namespace Nixin
{
    class TextureBase
    {



    public:



        TextureBase();
        virtual ~TextureBase();

        GLuint                             GetID() const;
        bool                               IsMutable() const;
        GLint                              GetLevels() const;
        GLenum                             GetInternalFormat() const;

        GLenum                             GetWrapS() const;
        void                               SetWrapS( GLenum newWrapS );
        GLenum                             GetWrapT() const;
        void                               SetWrapT( GLenum newWrapT );
        GLenum                             GetMagFilter() const;
        void                               SetMagFilter( GLenum newMagFilter );
        GLenum                             GetMinFilter() const;
        void                               SetMinFilter( GLenum newMinFilter );


    protected:




        OpenGLFunctions*                    gl          = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        OpenGLHandle                        id;
        bool                                isMutable   = true;
        GLenum                              internalFormat   = 0;
        GLsizei                             levels           = 0;

        GLenum                              wrapS            = GL_REPEAT;
        GLenum                              wrapT            = GL_REPEAT;
        GLenum                              magFilter        = GL_LINEAR;
        GLenum                              minFilter        = GL_LINEAR;

        bool                                firstBind        = true;

        void                                GenTexture();
        void                                DisposeTexture() const;



    };
}



#endif // NIXIN_TEXTUREBASE_H
