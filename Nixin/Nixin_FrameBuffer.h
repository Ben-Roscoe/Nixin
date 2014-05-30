#ifndef NIXIN_FRAME_BUFFER_H_
#define NIXIN_FRAME_BUFFER_H_



#include "Nixin_Texture.h"
#include "Nixin_Rectangle.h"
#include "Nixin_Renderbuffer.h"
#include "Nixin_FramebufferAttachment.h"
#include "Nixin_Types.h"

#include <array>
#include <memory>
#include <initializer_list>
#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{
    class Framebuffer
	{



	public:



        Framebuffer();
        Framebuffer( const Framebuffer& other );
        Framebuffer( Framebuffer&& other );
        Framebuffer& operator=( Framebuffer other );
        ~Framebuffer();
		
        void                                    swap( Framebuffer& a, Framebuffer& b );


        GLuint           						GetID() const;
        void                                    Bind( GLenum target ) const;

        void                                    AttachDepth( GLenum target, const Renderbuffer* renderbuffer );
        void                                    AttachDepth( GLenum target, const Texture* texture );
        void                                    AttachStencil( GLenum target, const Renderbuffer* renderbuffer );
        void                                    AttachStencil( GLenum target, const Texture* texture );
        void                                    AttachDepthStencil( GLenum target, const Renderbuffer* renderbuffer );
        void                                    AttachDepthStencil( GLenum target, const Texture* texture );
        void                                    AttachColour( GLenum target, unsigned int i, const Renderbuffer* renderbuffer );
        void                                    AttachColour( GLenum target, unsigned int i, const Texture* texture );
        void                                    DetachDepth( GLenum target );
        void                                    DetachStencil( GLenum target );
        void                                    DetachDepthStencil( GLenum target );
        void                                    DetachColour( GLenum target, unsigned int i );
        void                                    DetachAllColour( GLenum target );
        void                                    DetachAll( GLenum target );

        void                                    Invalidate( GLenum target, const std::initializer_list<GLenum>& attachments );
        void                                    Invalidate( GLenum target, const std::initializer_list<GLenum>& attachments, const Rectangle& region );

        bool                                    IsComplete( GLenum target ) const;
        GLenum                                  GetStatus( GLenum target ) const;
        void                                    PrintStatus( GLenum target ) const;



	private:



        static const GLint                      mipmapLevel             = 0;

        OpenGLFunctions*                        gl                      = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint      							id                      = 0;

        FramebufferAttachment                   depthAttachment         = { this };
        FramebufferAttachment                   stencilAttachment       = { this };
        FramebufferAttachment                   depthStencilAttachment  = { this };
        std::vector<FramebufferAttachment>      colourAttachments;



        void                                    GenFramebuffer();
		

	};
}



#endif
