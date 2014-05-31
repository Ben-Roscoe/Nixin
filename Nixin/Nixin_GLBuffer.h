#ifndef _NIXIN_VBUFFER_H_
#define _NIXIN_VBUFFER_H_

#include "Nixin_Debug.h"
#include "Nixin_Types.h"
#include <QOpenGLFunctions_4_3_Core>
#include <memory>

namespace Nixin
{
    class GLBuffer
	{



	public:



        GLBuffer( GLenum initialAccess );
        GLBuffer( GLenum target, GLenum initialAccess, GLsizei initialSize, const void* initialData = nullptr );
        GLBuffer( const GLBuffer& other );
        GLBuffer( GLBuffer&& other );
        GLBuffer& operator=( GLBuffer other );
        ~GLBuffer();

        friend void                 swap( GLBuffer& a, GLBuffer& b );

        GLuint                      GetID() const;

        void						Bind( GLenum target ) const;
        void                        Release(GLenum target ) const;
        void                        Reserve( GLenum target, GLsizei dataSize );
        void                        SetData( GLenum target, GLsizei dataSize, const void* data = nullptr );
        void                        SetData( GLenum target, const std::vector<GLbyte>& data );
        void                        SetDataRange( GLenum target, GLintptr start, GLsizeiptr length, const void* data );
        void                        SetDataRange( GLenum target, GLintptr start, const std::vector<GLbyte>& data );
        void                        Clear( GLenum target, GLenum internalFormat, GLenum format, GLenum type, const void* data );
        void                        Clear( GLenum target, GLenum internalFormat, GLenum format, GLenum type, const std::vector<GLbyte>& data );
        void                        ClearRange( GLenum target, GLenum internalFormat, GLintptr start, GLsizeiptr length, GLenum format, GLenum type, const void* data );
        void                        ClearRange( GLenum target, GLenum internalFormat, GLintptr start, GLenum format, GLenum type, const std::vector<GLbyte>& data );

        void*                       Map( GLenum target, GLenum access );
        void*                       MapRange( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access );
        bool                        Unmap( GLenum target );


        bool                        IsBound( GLenum target ) const;
        GLsizei                     GetSize() const;


	private:



        OpenGLFunctions*                            gl              = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                                      id				= 0;
        GLsizei                                     size			= 0;
        GLenum                                      access          = GL_STATIC_DRAW;
        bool                                        isMapped        = false;


        void                                        GenBuffer();



	};


}





#endif
