#ifndef NIXIN_TEXTURE1D_H
#define NIXIN_TEXTURE1D_H



#include "Nixin_TextureBase.h"


namespace Nixin
{

    class Texture1D : TextureBase
    {



    public:



        Texture1D();
        ~Texture1D() override;

        void                                Bind() const;
        void                                Release() const;
        void                                SetImmutableStorage( GLint textureLevels, GLsizei textureWidth, GLenum textureInternalFormat );
        void                                SetMutableStorage( GLint textureLevel, GLsizei textureWidth, GLenum textureInternalFormat, GLenum dataFormat, GLenum dataType, const GLvoid* data );
        void                                SetData( GLint level, GLenum dataFormat, GLenum dataType, GLsizei length, const void* data = nullptr, GLint offset = 0 ) const;
        void                                CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei length, GLint offset = 0 ) const;
        void                                GetData( GLint level, GLenum format, GLenum type, GLvoid* data = 0 ) const;


        GLsizei                             GetWidth() const;




    private:



        static const GLenum                 target          = GL_TEXTURE_1D;
        static const GLint                  border          = 0;


        GLsizei                             width           = 0;




    };
}


#endif // NIXIN_TEXTURE1D_H
