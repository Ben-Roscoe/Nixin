#include "Nixin_Texture1DArrayImmutable.h"
#include "Nixin_Debug.h"



namespace Nixin
{



    // Public:



    //
    // Texture1DArrayImmutable
    //
    Texture1DArrayImmutable::Texture1DArrayImmutable( GLsizei textureLevels, GLenum textureInternalFormat, GLsizei textureWidth, GLsizei textureHeight )
    {
        levels          = textureLevels;
        internalFormat  = textureInternalFormat;
        width           = textureWidth;
        height          = textureHeight;

        SetStorage();
    }



    //
    // Texture1DArrayImmutable
    //
    Texture1DArrayImmutable::Texture1DArrayImmutable( const Texture1DArrayImmutable& other ) : TextureBase( other )
    {
        internalFormat          = other.internalFormat;
        levels                  = other.levels;
        width                   = other.width;
        height                  = other.height;


        if( other.id != 0 )
        {
            Bind();
            SetStorage();

            for( GLint i = 0; i < levels; i++ )
            {
                gl->glCopyImageSubData( other.id, target, i, 0, 0, 0, id, target, i, 0, 0, 0, width, height, 1 );
            }
        }
    }



    //
    // ~Texture1DArrayImmutable
    //
    Texture1DArrayImmutable::~Texture1DArrayImmutable()
    {

    }



    //
    // Texture1DArrayImmutable
    //
    Texture1DArrayImmutable::Texture1DArrayImmutable( Texture1DArrayImmutable&& other ) : TextureBase( other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    Texture1DArrayImmutable& Texture1DArrayImmutable::operator=( Texture1DArrayImmutable other )
    {
        swap( static_cast<TextureBase&>( *this ), static_cast<TextureBase&>( other ) );
        swap( *this, other );
        return *this;
    }



    //
    // swap
    //
    void swap( Texture1DArrayImmutable& a, Texture1DArrayImmutable& b )
    {
        using std::swap;

        swap( a.internalFormat, b.internalFormat );
        swap( a.levels, b.levels );
        swap( a.width, b.width );
        swap( a.height, b.height );
    }



    //
    // Bind
    //
    void Texture1DArrayImmutable::Bind() const
    {
        gl->glBindTexture( target, id );
    }



    //
    // SetData
    //
    void Texture1DArrayImmutable::SetData( GLint level, GLenum format, GLenum type, GLsizei dataWidth, GLsizei dataHeight, const void* data, GLint xoffset, GLint yoffset ) const
    {
        if( xoffset < 0 || ( xoffset + dataWidth ) >= width || dataWidth < 0 || yoffset < 0 || ( yoffset + dataHeight ) >= height || dataHeight < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a immutable texture 1D array." );
        }
        gl->glTexSubImage2D( target, level, xoffset, yoffset, dataWidth, dataHeight, format, type, data );
    }



    //
    // CopyDataFromFramebuffer
    //
    void Texture1DArrayImmutable::CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei dataWidth, GLsizei dataHeight, GLint xoffset, GLint yoffset ) const
    {
        if( xoffset < 0 || ( xoffset + dataWidth ) >= width || dataWidth < 0 || yoffset < 0 || ( yoffset + dataHeight ) >= height || dataHeight < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a immutable texture 1D array." );
        }
        gl->glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, dataWidth, dataHeight );
    }



    //
    // GetData
    //
    void Texture1DArrayImmutable::GetData( GLint level, GLenum format, GLenum type, GLvoid* data ) const
    {
        gl->glGetTexImage( target, level, format, type, data );
    }



    //
    // GetInternalFormat
    //
    GLenum Texture1DArrayImmutable::GetInternalFormat() const
    {
        return internalFormat;
    }



    //
    // GetLevels
    //
    GLsizei Texture1DArrayImmutable::GetLevels() const
    {
        return levels;
    }



    //
    // GetWidth
    //
    GLsizei Texture1DArrayImmutable::GetWidth() const
    {
        return width;
    }



    //
    // GetHeight
    //
    GLsizei Texture1DArrayImmutable::GetHeight() const
    {
        return height;
    }
}
