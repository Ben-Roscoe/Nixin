#include "Nixin_Texture1D.h"
#include "Nixin_Debug.h"


namespace Nixin
{


    //
    // Texture1D
    //
    Texture1D::Texture1D()
    {

    }


    //
    // SetImmutableStorage
    //
    void Texture1D::SetImmutableStorage( GLint textureLevels, GLsizei textureWidth, GLenum textureInternalFormat )
    {
        GenTexture();

        levels          = textureLevels;
        width           = textureWidth;
        internalFormat  = textureInternalFormat;

        gl->glTexStorage1D( target, levels, internalFormat, width );
        isMutable = false;
    }



    //
    // SetMutableStorage
    //
    void Texture1D::SetMutableStorage( GLint textureLevel, GLsizei textureWidth, GLenum textureInternalFormat, GLenum dataFormat, GLenum dataType, const GLvoid* data )
    {
        if( isMutable && data != nullptr )
        {
            GenTexture();

            width  = textureWidth;
            internalFormat = textureInternalFormat;

            gl->glTexImage1D( target, textureLevel, internalFormat, width, border, dataFormat, dataType, data );
        }
    }



    //
    // SetData
    //
    void Texture1D::SetData( GLint level, GLenum format, GLenum type, GLsizei length, const void* data, GLint offset ) const
    {
        if( offset < 0 || ( offset + length ) >= width || length < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a texture 1D." );
        }
        gl->glTexSubImage1D( target, level, offset, length, format, type, data );
    }



    //
    // Bind
    //
    void Texture1D::Bind() const
    {
        gl->glBindTexture( target, *id );
    }



    //
    // Release
    //
    void Texture1D::Release() const
    {
        gl->glBindTexture( target, 0 );
    }



    //
    // ~Texture1D
    //
    Texture1D::~Texture1D()
    {

    }



    //
    // CopyDataFromFramebuffer
    //
    void Texture1D::CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei length, GLint offset ) const
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
    void Texture1D::GetData( GLint level, GLenum format, GLenum type, GLvoid* data ) const
    {
        gl->glGetTexImage( target, level, format, type, data );
    }



    //
    // GetWidth
    //
    GLsizei Texture1D::GetWidth() const
    {
        return width;
    }

}
