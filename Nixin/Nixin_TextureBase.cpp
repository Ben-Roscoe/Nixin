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
