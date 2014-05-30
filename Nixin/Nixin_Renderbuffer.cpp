#include "Nixin_Renderbuffer.h"
#include "Nixin_Debug.h"



namespace Nixin
{


    // Public:



    //
    // Renderbuffer
    //
    Renderbuffer::Renderbuffer()
    {
        GenRenderbuffer();
    }



    //
    // Renderbuffer
    //
    Renderbuffer::Renderbuffer( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat )
    {
        GenRenderbuffer();
        Bind();
        SetStorage( storageWidth, storageHeight, storageInternalFormat );
    }



    //
    // RenderBuffer
    //
    Renderbuffer::Renderbuffer( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat, GLsizei samples )
    {
        GenRenderbuffer();
        Bind();
        SetStorage( storageWidth, storageHeight, storageInternalFormat, samples );
    }



    //
    // Renderbuffer
    //
    Renderbuffer::Renderbuffer( Renderbuffer&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    Renderbuffer& Renderbuffer::operator=( Renderbuffer&& other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // swap
    //
    void Renderbuffer::swap( Renderbuffer& a, Renderbuffer& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
        swap( a.internalFormat, b.internalFormat );
        swap( a.width, a.width );
        swap( a.height, b.height );
        swap( a.multisampled, b.multisampled );
        swap( a.sampleCount, b.sampleCount );
    }



    //
    // ~Renderbuffer
    //
    Renderbuffer::~Renderbuffer()
    {
        if( id != 0 )
        {
            gl->glDeleteRenderbuffers( 1, &id );
        }
    }



    //
    // GetID
    //
    GLuint Renderbuffer::GetID() const
    {
        return id;
    }



    //
    // Bind
    //
    void Renderbuffer::Bind() const
    {
        gl->glBindRenderbuffer( Renderbuffer::target, id );
    }



    //
    // SetStorage
    //
    void Renderbuffer::SetStorage( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat )
    {
        gl->glRenderbufferStorage( target, storageInternalFormat, storageWidth, storageHeight );
        if( Debug::PrintGLError( gl->glGetError(), "glRenderbufferStorage" ) != GL_NO_ERROR )
        {
            Debug::Warning( "Renderbuffer storage could not be set." );
            return;
        }

        width           = storageWidth;
        height          = storageHeight;
        internalFormat  = storageInternalFormat;
        multisampled    = false;
        sampleCount     = 0;
    }



    //
    // SetStorage
    //
    void Renderbuffer::SetStorage( GLsizei storageWidth, GLsizei storageHeight, GLsizei storageInternalFormat, GLsizei samples )
    {
        gl->glRenderbufferStorageMultisample( target, samples, storageInternalFormat, storageWidth, storageHeight );
        if( Debug::PrintGLError( gl->glGetError(), "glRenderbufferStorage" ) != GL_NO_ERROR )
        {
            Debug::Warning( "Renderbuffer multisample storage could not be set." );
            return;
        }

        width           = storageWidth;
        height          = storageHeight;
        internalFormat  = storageInternalFormat;
        sampleCount     = samples;

        if( samples != 0 )
        {
            multisampled    = true;
        }
        else
        {
            multisampled    = false;
        }
    }



    //
    // IsMultisampled
    //
    bool Renderbuffer::IsMultisampled() const
    {
        return multisampled;
    }



    //
    // SampleCount
    //
    GLsizei Renderbuffer::SampleCount() const
    {
        return sampleCount;
    }



    //
    // Width
    //
    GLsizei Renderbuffer::Width() const
    {
        return width;
    }



    //
    // Height
    //
    GLsizei Renderbuffer::Height() const
    {
        return height;
    }



    //
    // Size
    //
    Point Renderbuffer::Size() const
    {
        return Point( static_cast<float>( width ), static_cast<float>( height ) );
    }



    //
    // Bounds
    //
    Rectangle Renderbuffer::Bounds() const
    {
        return Rectangle( 0.0f, 0.0f, static_cast<float>( width ), static_cast<float>( height ) );
    }



    //
    // InternalFormat
    //
    GLenum Renderbuffer::InternalFormat() const
    {
        return internalFormat;
    }




    // Private:



    //
    // GenRednerbuffer
    //
    void Renderbuffer::GenRenderbuffer()
    {
        gl->glGenRenderbuffers( 1, &id );
        if( id == 0 )
        {
            if( id == 0 )
            {
                Debug::PrintGLError( gl->glGetError(), "glGenRenderbuffers" );
                Debug::FatalError( "glGenRenderbuffers returned 0 while attempting to create a renderbuffer inside Nixin::Renderbuffer." );
            }
        }
    }
}
