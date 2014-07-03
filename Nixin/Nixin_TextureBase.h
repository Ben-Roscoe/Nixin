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


    protected:




        OpenGLFunctions*                    gl          = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        OpenGLHandle                        id;
        bool                                isMutable   = true;
        GLenum                              internalFormat   = 0;
        GLsizei                             levels           = 0;

        void                                GenTexture();
        void                                DisposeTexture() const;



    };
}



#endif // NIXIN_TEXTUREBASE_H
