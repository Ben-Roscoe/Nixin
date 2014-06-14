#ifndef NIXIN_TEXTURE1DARRAYIMMUTABLE_H
#define NIXIN_TEXTURE1DARRAYIMMUTABLE_H


#include "Nixin_TextureBase.h"



namespace Nixin
{
    class Texture1DArrayImmutable : public TextureBase
    {



    public:



        Texture1DArrayImmutable( GLsizei textureLevels, GLenum textureInternalFormat, GLsizei textureWidth, GLsizei textureHeight );
        Texture1DArrayImmutable( const Texture1DArrayImmutable& other );
        Texture1DArrayImmutable( Texture1DArrayImmutable&& other );
        Texture1DArrayImmutable& operator=( Texture1DArrayImmutable other );
        ~Texture1DArrayImmutable() override;

        friend void                         swap( Texture1DArrayImmutable& a, Texture1DArrayImmutable& b );

        void                                Bind() const;
        void                                SetData( GLint level, GLenum format, GLenum type, GLsizei dataWidth, GLsizei dataHeight, const void* data = nullptr, GLint xoffset = 0, GLint yoffset = 0 ) const;
        void                                CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei dataWidth, GLsizei dataHeight, GLint xoffset = 0, GLint yoffset = 0 ) const;
        void                                GetData( GLint level, GLenum format, GLenum type, GLvoid* data = 0 ) const;

        GLenum                              GetInternalFormat() const;
        GLsizei                             GetLevels() const;
        GLsizei                             GetWidth() const;
        GLsizei                             GetHeight() const;



    private:



        static const GLenum                 target           = GL_TEXTURE_1D_ARRAY;


        GLenum                              internalFormat   = 0;
        GLsizei                             levels           = 0;
        GLsizei                             width            = 0;
        GLsizei                             height           = 0;



        void                                SetStorage() const;
    };
}




#endif // NIXIN_TEXTURE1DARRAYIMMUTABLE_H
