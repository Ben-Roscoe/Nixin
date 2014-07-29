#include "Nixin_Texture2D.h"
#include "Nixin_Debug.h"


namespace Nixin
{



    //
    // Texture2D
    //
    Texture2D::Texture2D()
    {
        Bind();

        // Set default texture parameters.
        gl->glTexParameteri( target, GL_TEXTURE_WRAP_S, wrapS );
        gl->glTexParameteri( target, GL_TEXTURE_WRAP_T, wrapT );
        gl->glTexParameteri( target, GL_TEXTURE_MAG_FILTER, magFilter );
        gl->glTexParameteri( target, GL_TEXTURE_MIN_FILTER, minFilter );
    }



    //
    // ~Texture2D
    //
    Texture2D::~Texture2D()
    {
    }



    //
    // Bind
    //
    void Texture2D::Bind() const
    {
        gl->glBindTexture( target, *id );
    }



    //
    // Release
    //
    void Texture2D::Release() const
    {
        gl->glBindTexture( target, 0 );
    }


    //
    // SetImmutableStorage
    //
    void Texture2D::SetImmutableStorage( GLint textureLevels, GLsizei textureWidth, GLsizei textureHeight, GLenum textureInternalFormat )
    {
        levels          = textureLevels;
        width           = textureWidth;
        height          = textureHeight;
        internalFormat  = textureInternalFormat;

        gl->glTexStorage2D( target, levels, internalFormat, width, height );
        isMutable = false;
    }



    //
    // SetMutableStorage
    //
    void Texture2D::SetMutableStorage( GLint textureLevel, GLsizei textureWidth, GLsizei textureHeight, GLenum textureInternalFormat, GLenum dataFormat, GLenum dataType, const GLvoid *data )
    {
        if( isMutable && data != nullptr )
        {
            width  = textureWidth;
            height = textureHeight;
            internalFormat = textureInternalFormat;

            gl->glTexImage2D( target, textureLevel, internalFormat, width, height, border, dataFormat, dataType, data );
        }
    }



    //
    // SetMutableStorage
    //
    void Texture2D::SetMutableStorage( GLint textureLevel, GLenum textureInternalFormat, const Image& image )
    {
        if( isMutable )
        {
            width   = image.GetWidth();
            height  = image.GetHeight();
            internalFormat = textureInternalFormat;

            gl->glTexImage2D( target, textureLevel, internalFormat, width, height, border, GL_BGRA, GL_UNSIGNED_BYTE, image.GetPixels<float>() );
        }
    }



    //
    // SetMutableStorage
    //
    void Texture2D::SetMutableStorage( GLint textureLevel, GLenum textureInternalFormat, const std::string& fileName )
    {
        if( isMutable )
        {
            Image image( fileName );
            SetMutableStorage( textureLevel, textureInternalFormat, image );
        }
    }



    //
    // SetData
    //
    void Texture2D::SetData( GLint level, GLenum dataFormat, GLenum dataType, GLsizei dataWidth, GLsizei dataHeight, const void* data, GLint xoffset, GLint yoffset ) const
    {
        if( xoffset < 0 || ( xoffset + dataWidth ) >= width || dataWidth < 0 || yoffset < 0 || ( yoffset + dataHeight ) >= height || dataHeight < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a immutable texture 2D array." );
        }
        gl->glTexSubImage2D( target, level, xoffset, yoffset, dataWidth, dataHeight, dataFormat, dataType, data );
    }



    //
    // CopyDataFromFramebuffer
    //
    void Texture2D::CopyDataFromFramebuffer( GLint level, GLint x, GLint y, GLsizei dataWidth, GLsizei dataHeight, GLint xoffset, GLint yoffset ) const
    {
        if( xoffset < 0 || ( xoffset + dataWidth ) >= width || dataWidth < 0 || yoffset < 0 || ( yoffset + dataHeight ) >= height || dataHeight < 0 )
        {
            Debug::FatalError( "Attempted to set data to an invalid range in a immutable texture 2D array." );
        }
        gl->glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, dataWidth, dataHeight );
    }



    //
    // GetData
    //
    void Texture2D::GetData( GLint level, GLenum format, GLenum type, GLvoid *data ) const
    {
        gl->glGetTexImage( target, level, format, type, data );
    }



    //
    // GetWidth
    //
    GLsizei Texture2D::GetWidth() const
    {
        return width;
    }



    //
    // GetHeight
    //
    GLsizei Texture2D::GetHeight() const
    {
        return height;
    }

}
