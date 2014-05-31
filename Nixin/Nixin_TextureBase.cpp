#include "Nixin_TextureBase.h"



namespace Nixin
{



    // Public:



    //
    // TextureBase
    //
    TextureBase::TextureBase()
    {
        GenTexture();
    }



    //
    // TextureBase
    // Derived classes are responsible for doing the actual deep copy,
    // as different types of textures are copied differently.
    //
    TextureBase::TextureBase( const TextureBase& other )
    {
        gl      = other.gl;

        if( other.id != 0 )
        {
            GenTexture();
            Bind();
        }
    }



    //
    // TextureBase
    //
    TextureBase::TextureBase( TextureBase&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    TextureBase& TextureBase::operator=( TextureBase other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // ~TextureBase
    //
    TextureBase::~TextureBase()
    {
        if( id != 0 )
        {
            gl->glDeleteTextures( 1, &id );
        }
    }



    //
    // swap
    //
    void swap( TextureBase& a, TextureBase& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
    }



    // Private:



    //
    // GenTexture
    //
    void TextureBase::GenTexture()
    {
        gl->glGenTextures( 1, &id );
    }
}
