#include "Nixin_Texture1DImmutable.h"
#include "Nixin_Debug.h"



namespace Nixin
{



    // Public:



    //
    // Texture1DImmutable
    //
    Texture1DImmutable::Texture1DImmutable( GLint textureLevels, GLsizei textureWidth, GLenum textureInternalFormat )
    {
        levels          = textureLevels;
        width           = textureWidth;
        internalFormat  = textureInternalFormat;

        Bind();
        SetStorage();
    }



    //
    // Texture1DImmutable
    //
    Texture1DImmutable::Texture1DImmutable( const Texture1DImmutable& other ) : TextureBase( other )
    {
        levels             = other.levels;
        width              = other.width;
        internalFormat     = other.internalFormat;

        if( other.id != 0 )
        {
            Bind();
            SetStorage();

            for( GLint i = 0; i < levels; i++ )
            {
                gl->glCopyImageSubData( other.id, target, i, 0, 0, 0, id, target, i, 0, 0, 0, width, 1, 1 );
            }
        }
    }



    //
    // Texture1DImmutable
    //
    Texture1DImmutable::Texture1DImmutable( Texture1DImmutable&& other ) : TextureBase( other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    Texture1DImmutable& Texture1DImmutable::operator=( Texture1DImmutable other )
    {
        swap( static_cast<TextureBase&>( *this ), static_cast<TextureBase&>( other ) );
        swap( *this, other );
        return *this;
    }



    //
    // ~Texture1DImmutable
    //
    Texture1DImmutable::~Texture1DImmutable()
    {

    }



    //
    // swap
    //
    void swap( Texture1DImmutable& a, Texture1DImmutable& b )
    {
        using std::swap;

        swap( a.levels, b.levels );
        swap( a.width, b.width );
        swap( a.internalFormat, b.internalFormat );
    }



    //
    // Bind
    //
    GLuint Texture1DImmutable::Bind() const
    {
        return id;
    }



    //
    // SetData
    //
    void Texture1DImmutable::SetData( GLint level, GLenum format, GLenum type, GLsizei length, const void* data, GLint offset ) const
    {
        if( offset < 0 || ( offset + length ) >= width || length < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a immutable texture 1D." );
        }
        gl->glTexSubImage1D( target, level, offset, length, format, type, data );
    }



    //
    // CopyDataFrameFramebuffer
    //
    void Texture1DImmutable::CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei length, GLint offset ) const
    {
        if( offset < 0 || ( offset + length ) >= width || length < 0 )
        {
            Debug::FatalError( "Attempted to set data from framebuffer to an invalid range in a immutable texture 1D.");
        }
        gl->glCopyTexSubImage1D( target, level, offset, x, y, length );
    }



    //
    // GetData
    //
    void Texture1DImmutable::GetData( GLint level, GLenum format, GLenum type, GLvoid* data ) const
    {
        gl->glGetTexImage( target, level, format, type, data );
    }



    //
    // GetWidth
    //
    GLsizei Texture1DImmutable::GetWidth() const
    {
        return width;
    }



    //
    // GetLevels
    //
    GLint Texture1DImmutable::GetLevels() const
    {
        return levels;
    }



    //
    // GetInternalFormat
    //
    GLenum Texture1DImmutable::GetInternalFormat() const
    {
        return internalFormat;
    }



    // Private:



    //
    // SetStorage
    //
    void Texture1DImmutable::SetStorage() const
    {
        gl->glTexStorage1D( target, levels, internalFormat, width );
    }
}
