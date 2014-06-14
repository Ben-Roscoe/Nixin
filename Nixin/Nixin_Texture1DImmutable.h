#ifndef NIXIN_TEXTURE1DIMMUTABLE_H
#define NIXIN_TEXTURE1DIMMUTABLE_H



#include "Nixin_TextureBase.h"



namespace Nixin
{
    class Texture1DImmutable : public TextureBase
    {



    public:



        Texture1DImmutable( GLint textureLevels, GLsizei textureWidth, GLenum textureInternalFormat );
        Texture1DImmutable( const Texture1DImmutable& other );
        Texture1DImmutable( Texture1DImmutable&& other );
        Texture1DImmutable& operator=( Texture1DImmutable other );
        ~Texture1DImmutable() override;

        friend void                         swap( Texture1DImmutable& a, Texture1DImmutable& b );

        GLuint                              Bind() const;
        void                                SetData( GLint level, GLenum format, GLenum type, GLsizei length, const void* data = nullptr, GLint offset = 0 ) const;
        void                                CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei length, GLint offset = 0 ) const;
        void                                GetData( GLint level, GLenum format, GLenum type, GLvoid* data = 0 ) const;

        GLsizei                             GetWidth() const;
        GLint                               GetLevels() const;
        GLenum                              GetInternalFormat() const;



    private:



        static const GLenum                 target          = GL_TEXTURE_1D;


        GLsizei                             width           = 0;
        GLint                               levels          = 0;
        GLenum                              internalFormat  = GL_RGBA8;



        void                                SetStorage() const;
    };
}



#endif // NIXIN_TEXTURE1DIMMUTABLE_H
