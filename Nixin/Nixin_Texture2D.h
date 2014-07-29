#ifndef NIXIN_TEXTURE2D_H
#define NIXIN_TEXTURE2D_H



#include "Nixin_TextureBase.h"
#include "Nixin_Image.h"



namespace Nixin
{


    class Texture2D : public TextureBase
    {


    public:


        Texture2D();
        ~Texture2D() override;

        void                                Bind() const;
        void                                Release() const;
        void                                SetImmutableStorage( GLint textureLevels, GLsizei textureWidth, GLsizei textureHeight, GLenum textureInternalFormat );
        void                                SetMutableStorage( GLint textureLevel, GLsizei textureWidth, GLsizei textureHeight, GLenum textureInternalFormat, GLenum dataFormat, GLenum dataType, const GLvoid* data );
        void                                SetMutableStorage( GLint textureLevel, GLenum textureInternalFormat, const Image& image );
        void                                SetMutableStorage( GLint textureLevel, GLenum textureInternalFormat, const std::string& fileName );
        void                                SetData( GLint level, GLenum dataFormat, GLenum dataType, GLsizei dataWidth, GLsizei dataHeight, const void* data = nullptr, GLint xoffset = 0, GLint yoffset = 0 ) const;
        void                                CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei dataWidth, GLsizei dataHeight, GLint xoffset = 0 , GLint yoffset = 0) const;
        void                                GetData( GLint level, GLenum format, GLenum type, GLvoid* data = 0 ) const;


        GLsizei                             GetWidth() const;
        GLsizei                             GetHeight() const;




    private:



        static const GLenum                 target           = GL_TEXTURE_2D;
        static const GLint                  border           = 0;


        GLsizei                             width            = 0;
        GLsizei                             height           = 0;



    };
}

#endif // NIXIN_TEXTURE2D_H
