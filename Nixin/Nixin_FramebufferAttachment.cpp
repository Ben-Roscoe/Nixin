#include "Nixin_FramebufferAttachment.h"



namespace Nixin
{


    //
    // FramebufferAttachment
    // Empty attachment. No owner.
    //
    FramebufferAttachment::FramebufferAttachment()
    {
        owner = nullptr;
    }



    //
    // FramebufferAttachment
    //
    FramebufferAttachment::FramebufferAttachment( const Framebuffer* framebufferOwner )
    {
        owner = framebufferOwner;
    }



    //
    // FramebufferAttachment
    // Has a texture attachment.
    //
    FramebufferAttachment::FramebufferAttachment( const Texture* textureAttachment, const Framebuffer* framebufferOwner )
    {
        texture = textureAttachment;
        owner   = framebufferOwner;
    }



    //
    // FramebufferAttachment
    // Has a renderbuffer attachment.
    //
    FramebufferAttachment::FramebufferAttachment( const Renderbuffer *renderbufferAttachment, const Framebuffer *framebufferOwner )
    {
        renderbuffer = renderbufferAttachment;
        owner        = framebufferOwner;
    }



    //
    // IsTexture
    //
    bool FramebufferAttachment::IsTexture() const
    {
        return texture != nullptr;
    }



    //
    // IsRenderbuffer
    //
    bool FramebufferAttachment::IsRenderbuffer() const
    {
        return renderbuffer != nullptr;
    }



    //
    // IsValid
    //
    bool FramebufferAttachment::IsEmpty() const
    {
        return ( texture != nullptr || renderbuffer != nullptr );
    }



    //
    // GetTexture
    // Retunrs the texture that is attached to owner. Returns null if the attachment is empty or a renderbuffer.
    //
    const Texture* FramebufferAttachment::GetTexture() const
    {
        return texture;
    }




    //
    // GetRenderbuffer
    // Returns the renderbuffer that is attached to owner. Returns null if the attachment is empty or a texture.
    //
    const Renderbuffer* FramebufferAttachment::GetRenderbuffer() const
    {
        return renderbuffer;
    }



    //
    // GetOwner
    // Returns the owner of this attachment. If null is returned, the attachment does not belong to any actual
    // framebuffer.
    //
    const Framebuffer* FramebufferAttachment::GetOwner() const
    {
        return owner;
    }
}
