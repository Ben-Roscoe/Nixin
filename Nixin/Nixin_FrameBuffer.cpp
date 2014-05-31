#include "Nixin_Framebuffer.h"
#include "Nixin_Debug.h"


namespace Nixin
{

    // Public:



    //
    // FrameBuffer
    //
    Framebuffer::Framebuffer()
    {
        // Get the max number of colour attachments available on this system.
        GLint       maxColourAttachments        = 0;
        gl->glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &maxColourAttachments );
        colourAttachments.resize( maxColourAttachments );

        // Initialise all colour attachments as empty.
        for( auto& attachment : colourAttachments )
        {
            attachment = { this };
        }
    }



    //
    // Framebuffer
    //
    Framebuffer::Framebuffer( const Framebuffer &other )
    {
        gl                      = other.gl;

        depthAttachment         = other.depthAttachment;
        stencilAttachment       = other.stencilAttachment;
        depthStencilAttachment  = other.depthStencilAttachment;
        colourAttachments       = other.colourAttachments;

        if( other.id != 0 )
        {
            GenFramebuffer();
            Bind( GL_READ_FRAMEBUFFER );

            // Copy the depth attachments.
            if( other.depthAttachment.IsRenderbuffer() )
            {
                AttachDepth( GL_READ_FRAMEBUFFER, other.depthAttachment.GetRenderbuffer() );
            }
            else if( other.depthAttachment.IsTexture() )
            {
                AttachDepth( GL_READ_FRAMEBUFFER, other.depthAttachment.GetTexture() );
            }
            // Copy the stencil attachments.
            if( other.stencilAttachment.IsRenderbuffer() )
            {
                AttachStencil( GL_READ_FRAMEBUFFER, other.stencilAttachment.GetRenderbuffer() );
            }
            else if( other.stencilAttachment.IsTexture() )
            {
                AttachStencil( GL_READ_FRAMEBUFFER, other.stencilAttachment.GetTexture() );
            }
            // Copy the depth-stencil attachments.
            if( other.depthStencilAttachment.IsRenderbuffer() )
            {
                AttachDepthStencil( GL_READ_FRAMEBUFFER, other.depthStencilAttachment.GetRenderbuffer() );
            }
            else if( other.depthStencilAttachment.IsTexture() )
            {
                AttachDepthStencil( GL_READ_FRAMEBUFFER, other.depthStencilAttachment.GetTexture() );
            }
            // Copy the colour attachments.
            for( size_t i = 0; i < other.colourAttachments.size(); i++ )
            {
                if( other.colourAttachments[i].IsRenderbuffer() )
                {
                    AttachColour( GL_READ_FRAMEBUFFER, i, other.colourAttachments[i].GetRenderbuffer() );
                }
                else if( other.colourAttachments[i].IsTexture() )
                {
                    AttachColour( GL_READ_FRAMEBUFFER, i, other.colourAttachments[i].GetTexture() );
                }
            }
        }
    }



    //
    // Framebuffer
    //
    Framebuffer::Framebuffer( Framebuffer&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    Framebuffer& Framebuffer::operator=( Framebuffer other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // ~FrameBuffer
    //
    Framebuffer::~Framebuffer()
    {
        if( id != 0 )
        {
            gl->glDeleteFramebuffers( 1, &id );
            id = 0;
        }
    }




    //
    // GetID
    //
    GLuint Framebuffer::GetID() const
    {
        return id;
    }



    //
    // swap
    //
    void swap( Framebuffer& a, Framebuffer& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
        swap( a.depthAttachment, b.depthAttachment );
        swap( a.stencilAttachment, b.stencilAttachment );
        swap( a.depthStencilAttachment, b.depthStencilAttachment );
        swap( a.colourAttachments, b.colourAttachments );
    }



    //
    // Bind
    //
    void Framebuffer::Bind( GLenum target ) const
    {
        gl->glBindFramebuffer( target, id );
    }



    //
    // AttachDepth
    //
    void Framebuffer::AttachDepth( GLenum target, const Renderbuffer* renderbuffer )
    {
        gl->glFramebufferRenderbuffer( target, GL_DEPTH_ATTACHMENT, Renderbuffer::target, renderbuffer->GetID() );
        depthAttachment = FramebufferAttachment( renderbuffer, this );
    }



    //
    // AttachDepth
    //
    void Framebuffer::AttachDepth( GLenum target, const Texture* texture )
    {
        gl->glFramebufferTexture( target, GL_DEPTH_ATTACHMENT, texture->GetID(), mipmapLevel );
        depthAttachment = FramebufferAttachment( texture, this );
    }



    //
    // AttachStencil
    //
    void Framebuffer::AttachStencil( GLenum target, const Renderbuffer* renderbuffer )
    {
        gl->glFramebufferRenderbuffer( target, GL_STENCIL_ATTACHMENT, Renderbuffer::target, renderbuffer->GetID() );
        stencilAttachment = FramebufferAttachment( renderbuffer, this );
    }



    //
    // AttachStencil
    //
    void Framebuffer::AttachStencil( GLenum target, const Texture* texture )
    {
        gl->glFramebufferTexture( target, GL_STENCIL_ATTACHMENT, texture->GetID(), mipmapLevel );
        stencilAttachment = FramebufferAttachment( texture, this );
    }



    //
    // AttachDepthStencil
    //
    void Framebuffer::AttachDepthStencil( GLenum target, const Renderbuffer* renderbuffer )
    {
        gl->glFramebufferRenderbuffer( target, GL_DEPTH_STENCIL_ATTACHMENT, Renderbuffer::target, renderbuffer->GetID() );
        depthStencilAttachment = FramebufferAttachment( renderbuffer, this );
    }



    //
    // AttachDepthStencil
    //
    void Framebuffer::AttachDepthStencil( GLenum target, const Texture* texture )
    {
        gl->glFramebufferTexture( target, GL_DEPTH_STENCIL_ATTACHMENT, texture->GetID(), mipmapLevel );
        depthStencilAttachment = FramebufferAttachment( texture, this );
    }



    //
    // AttachColour
    //
    void Framebuffer::AttachColour( GLenum target, unsigned int i, const Renderbuffer* renderbuffer )
    {
        gl->glFramebufferRenderbuffer( target, GL_COLOR_ATTACHMENT0 + i, Renderbuffer::target, renderbuffer->GetID() );
        colourAttachments[i] = FramebufferAttachment( renderbuffer, this );
    }


    //
    // AttachColour
    //
    void Framebuffer::AttachColour( GLenum target, unsigned int i, const Texture* texture )
    {
        gl->glFramebufferTexture( target, GL_COLOR_ATTACHMENT0 + i, texture->GetID(), mipmapLevel );
        colourAttachments[i] = FramebufferAttachment( texture, this );
    }



    //
    // DetachDepth
    //
    void Framebuffer::DetachDepth( GLenum target )
    {
        if( !depthAttachment.IsEmpty() )
        {
            gl->glFramebufferRenderbuffer( target, GL_DEPTH_ATTACHMENT, Renderbuffer::target, 0 );
            depthAttachment = FramebufferAttachment( this );
        }
    }



    //
    // DetachStencil
    //
    void Framebuffer::DetachStencil( GLenum target )
    {
        if( !stencilAttachment.IsEmpty() )
        {
            gl->glFramebufferRenderbuffer( target, GL_STENCIL_ATTACHMENT, Renderbuffer::target, 0 );
            stencilAttachment = FramebufferAttachment( this );
        }
    }



    //
    // DetachDepthStencil
    //
    void Framebuffer::DetachDepthStencil( GLenum target )
    {
        if( !depthStencilAttachment.IsEmpty() )
        {
            gl->glFramebufferRenderbuffer( target, GL_DEPTH_STENCIL_ATTACHMENT, Renderbuffer::target, 0 );
            depthStencilAttachment = FramebufferAttachment( this );
        }
    }



    //
    // DetachColour
    //
    void Framebuffer::DetachColour( GLenum target, unsigned int i )
    {
        if( !colourAttachments[i].IsEmpty() )
        {
            gl->glFramebufferRenderbuffer( target, GL_COLOR_ATTACHMENT0 + i, Renderbuffer::target, 0 );
            colourAttachments[i] = FramebufferAttachment( this );
        }
    }



    //
    // DetachAllColour
    //
    void Framebuffer::DetachAllColour( GLenum target )
    {
        // If any colour attachment is not empty, make it empty.
        for( size_t i = 0; i < colourAttachments.size(); i++ )
        {
            if( !colourAttachments[i].IsEmpty() )
            {
                gl->glFramebufferRenderbuffer( target, GL_COLOR_ATTACHMENT0 + i, Renderbuffer::target, 0 );
                colourAttachments[i] = FramebufferAttachment( this );
            }
        }
    }



    //
    // DetachAll
    // Resets all render targets to the default, or detaches them.
    //
    void Framebuffer::DetachAll( GLenum target )
    {
        DetachDepth( target );
        DetachStencil( target );
        DetachDepthStencil( target );
        DetachAllColour( target );
    }



    //
    // Invalidate
    //
    void Framebuffer::Invalidate( GLenum target, const std::initializer_list<GLenum>& attachments )
    {
        gl->glInvalidateFramebuffer( target, static_cast<GLsizei>( attachments.size() ), attachments.begin() );
    }



    //
    // Invalidate
    //
    void Framebuffer::Invalidate( GLenum target, const std::initializer_list<GLenum>& attachments, const Rectangle& region )
    {
        gl->glInvalidateSubFramebuffer( target, static_cast<GLsizei>( attachments.size() ), attachments.begin(), region.x, region.y, region.width, region.height );
    }



    //
    // IsComplete
    //
    bool Framebuffer::IsComplete( GLenum target ) const
    {
        return gl->glCheckFramebufferStatus( target ) == GL_FRAMEBUFFER_COMPLETE;
    }



    //
    // GetStatus
    //
    GLenum Framebuffer::GetStatus( GLenum target ) const
    {
        return gl->glCheckFramebufferStatus( target );
    }



    //
    // PrintStatus
    //
    void Framebuffer::PrintStatus( GLenum target ) const
    {
        Debug::PrintFramebufferStatus( gl->glCheckFramebufferStatus( target ) );
    }





    // Private:





    //
    // GenFramebuffer
    //
    void Framebuffer::GenFramebuffer()
    {
        gl->glGenFramebuffers( 1, &id );
        if( id == 0 )
        {
            if( id == 0 )
            {
                Debug::PrintGLError( gl->glGetError(), "glGenFramebuffers" );
                Debug::FatalError( "glGenFramebuffers returned 0 while attempting to create a renderbuffer inside Nixin::Renderbuffer." );
            }
        }
    }
}
