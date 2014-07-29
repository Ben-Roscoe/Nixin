#include "Nixin_TextureBase.h"



namespace Nixin
{



    // Public:



    //
    // TextureBase
    //
    TextureBase::TextureBase()
    {
        id = OpenGLHandle( new GLuint() );
        GenTexture();
    }



    //
    // ~TextureBase
    //
    TextureBase::~TextureBase()
    {
        if( id.unique() && id.get() != nullptr )
        {
            DisposeTexture();
        }
    }



    //
    // GetID
    //
    GLuint TextureBase::GetID() const
    {
        return *id;
    }



    //
    // IsMutable
    //
    bool TextureBase::IsMutable() const
    {
        return isMutable;
    }



    //
    // GetLevels
    //
    GLint TextureBase::GetLevels() const
    {
        return levels;
    }



    //
    // GetInternalFormat
    //
    GLenum TextureBase::GetInternalFormat() const
    {
        return internalFormat;
    }



    //
    // GetWrapS
    //
    GLenum TextureBase::GetWrapS() const
    {
        return wrapS;
    }



    //
    // SetWrapS
    //
    void TextureBase::SetWrapS( GLenum newWrapS )
    {
        wrapS = newWrapS;
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS );
    }



    //
    // GetWrapT
    //
    GLenum TextureBase::GetWrapT() const
    {
        return wrapT;
    }



    //
    // SetWrapT
    //
    void TextureBase::SetWrapT( GLenum newWrapT )
    {
        wrapT = newWrapT;
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT );
    }



    //
    // GetMagFilter
    //
    GLenum TextureBase::GetMagFilter() const
    {
        return magFilter;
    }



    //
    // SetMagFilter
    //
    void TextureBase::SetMagFilter( GLenum newMagFilter )
    {
        magFilter = newMagFilter;
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );
    }



    //
    // GetMinFilter
    //
    GLenum TextureBase::GetMinFilter() const
    {
        return minFilter;
    }



    //
    // SetMinFilter
    //
    void TextureBase::SetMinFilter( GLenum newMinFilter )
    {
        minFilter = newMinFilter;
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
    }



    // Private:



    //
    // GenTexture
    //
    void TextureBase::GenTexture()
    {
        gl->glGenTextures( 1, &( *id ) );
    }



    //
    // DisposeTexture
    //
    void TextureBase::DisposeTexture() const
    {
        gl->glDeleteTextures( 1, &( *id ) );
    }
}
