#ifndef NIXIN_FRAMEBUFFERATTACHMENT_H
#define NIXIN_FRAMEBUFFERATTACHMENT_H



namespace Nixin
{
    class Texture;
    class Renderbuffer;
    class Framebuffer;

    class FramebufferAttachment
    {



    public:



        FramebufferAttachment();
        FramebufferAttachment( const Framebuffer* framebufferOwner );
        FramebufferAttachment( const Texture* textureAttachment, const Framebuffer* framebufferOwner );
        FramebufferAttachment( const Renderbuffer* renderbufferAttachment, const Framebuffer* framebufferOwner );



        bool                    IsTexture() const;
        bool                    IsRenderbuffer() const;
        bool                    IsEmpty() const;

        const Texture*          GetTexture() const;
        const Renderbuffer*     GetRenderbuffer() const;
        const Framebuffer*      GetOwner() const;


    private:



        const Texture*           texture             = nullptr;
        const Renderbuffer*      renderbuffer        = nullptr;
        const Framebuffer*       owner               = nullptr;


    };
}




#endif // NIXIN_FRAMEBUFFERATTACHMENT_H
