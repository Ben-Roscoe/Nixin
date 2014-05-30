#include "Nixin_GLBuffer.h"
#include "Nixin_Debug_Output.h"


namespace Nixin
{


    // Public:



    //
    // GLBuffer
    //
    GLBuffer::GLBuffer( GLenum initialAccess )
    {
        access = initialAccess;
        size   = 0;
        GenBuffer();
    }



    //
    // GLBuffer
    //
    GLBuffer::GLBuffer( GLenum target, GLenum initialAccess, GLsizei initialSize, const void* initialData )
    {
        size	= std::max( initialSize, 0 );
        access	= initialAccess;

        gl->initializeOpenGLFunctions();
        GenBuffer();
        Bind( target );
        SetData( target, initialSize, initialData );
    }



    //
    // GLBuffer
    //
    GLBuffer::GLBuffer( const Nixin::GLBuffer& other )
    {
        gl         = other.gl;
        size       = other.size;
        access     = other.access;

        if( other.id != 0 )
        {
            GenBuffer();

            other.Bind( GL_COPY_READ_BUFFER );
            Bind( GL_COPY_WRITE_BUFFER );

            Reserve( GL_COPY_WRITE_BUFFER, other.size );
            gl->glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, ( GLsizeiptr )( NULL + 0 ), ( GLsizeiptr )( NULL + 0 ), ( GLsizeiptr )( NULL + other.size ) );
        }
    }



    //
    // GLBuffer
    //
    GLBuffer::GLBuffer( GLBuffer&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    GLBuffer& Nixin::GLBuffer::operator=( GLBuffer other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // ~GLBuffer
    //
    GLBuffer::~GLBuffer()
    {
        if( id != 0 )
        {
            gl->glDeleteBuffers( 1, &id );
            id = 0;
        }
    }




    //
    // swap
    //
    void GLBuffer::swap(Nixin::GLBuffer& a, Nixin::GLBuffer& b)
    {
        using           std::swap;

        swap( a.id, b.id );
        swap( a.gl, b.gl );
        swap( a.size, b.size );
        swap( a.access, b.access );
    }



    //
    // Bind
    //
    void GLBuffer::Bind( GLenum target ) const
    {
        gl->glBindBuffer( target, id );
    }



    //
    // Release
    //
    void GLBuffer::Release( GLenum target ) const
    {
        gl->glBindBuffer( target, 0 );
    }



    //
    // Reserve
    //
    void GLBuffer::Reserve( GLenum target, GLsizei dataSize )
    {
        size = dataSize;
        gl->glBufferData( target, size, nullptr, access );
    }



    //
    // SetData
    //
    void GLBuffer::SetData( GLenum target, GLsizei dataSize, const void *data )
    {
        size = dataSize;
        gl->glBufferData( target, size, data, access );
    }



    //
    // SetData
    //
    void GLBuffer::SetData( GLenum target, const std::vector<GLbyte>& data )
    {
        size = data.size();
        gl->glBufferData( target, size, data.data(), access );
    }



    //
    // Map
    //
    void* GLBuffer::Map( GLenum target, GLenum access )
    {
        void* ptr = gl->glMapBuffer( target, access );
        if( ptr == nullptr )
        {
            Debug::PrintGLError( gl->glGetError(), "glMapBuffer" );
            Debug::Warning( "Mapping pointer to GLBuffer returned null. Pointer is not valid." );
        }
        else
        {
            isMapped = true;
        }
        return ptr;
    }



    //
    // MapRange
    //
    void* GLBuffer::MapRange( GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access )
    {
        void* ptr = gl->glMapBufferRange( target, offset, length, access );
        if( ptr == nullptr )
        {
            Debug::PrintGLError( gl->glGetError(), "glMapBufferRange" );
            Debug::Warning( "Mapping pointer to GLBuffer range returned null. Pointer is not valid." );
        }
        else
        {
            isMapped = true;
        }
        return ptr;
    }



    //
    // Unmap
    //
    bool GLBuffer::Unmap( GLenum target )
    {
        isMapped = false;
        return gl->glUnmapBuffer( target );
    }



    //
    // SetDataRange
    // Throw an exception if data is written outside the buffer.
    //
    void GLBuffer::SetDataRange( GLenum target, GLintptr start, GLsizeiptr length, const void *data )
    {
        if( ( start + length ) > size )
        {
            Debug::FatalError( "Set data range called with a start of %i and a length of %i writes outside the total buffer size of %i.", start, length, size );
        }
        gl->glBufferSubData( target, start, length, data );
    }



    //
    // SetDataRange
    // Throw an exception if data is written outside the buffer.
    //
    void GLBuffer::SetDataRange( GLenum target, GLintptr start, const std::vector<GLbyte>& data )
    {
        if( ( start + data.size() ) > size )
        {
            Debug::FatalError( "Set data range called with a start of %i and a length of %i writes outside the total buffer size of %i.", start, data.size(), size );
        }
        gl->glBufferSubData( target, start, data.size(), data.data() );
    }



    //
    // Clear
    //
    void GLBuffer::Clear( GLenum target, GLenum internalFormat, GLenum format, GLenum type, const std::vector<GLbyte> &data )
    {
        gl->glClearBufferData( target, internalFormat, format, type, data.data() );
    }



    //
    // Clear
    //
    void GLBuffer::Clear( GLenum target, GLenum internalFormat, GLenum format, GLenum type, const void* data )
    {
        gl->glClearBufferData( target, internalFormat, format, type, data );
    }



    //
    // ClearRange
    //
    void GLBuffer::ClearRange( GLenum target, GLenum internalFormat, GLintptr start, GLsizeiptr length, GLenum format, GLenum type, const void* data )
    {
        gl->glClearBufferSubData( target, internalFormat, start, length, format, type, data );
    }



    //
    // ClearRange
    //
    void GLBuffer::ClearRange( GLenum target, GLenum internalFormat, GLintptr start, GLenum format, GLenum type, const std::vector<GLbyte>& data )
    {
        gl->glClearBufferSubData( target, internalFormat, start, static_cast<GLsizeiptr>( data.size() ), format, type, data.data() );
    }


    //
    // IsBound
    // Returns true if the buffer is bound to target, false if it is not.
    //
    bool GLBuffer::IsBound( GLenum target ) const
    {
        GLint                  bufferBinding = 0;
        gl->glGetIntegerv( GL_BUFFER_BINDING, &bufferBinding );
        return ( static_cast<GLuint>( bufferBinding ) == id );
    }



    // Private:



    //
    // GenBuffers
    // Attempts to assign id a vaild buffer name. Throws a Nixin::FatalError exception
    // if the id cannot be assigned.
    //
    void GLBuffer::GenBuffer()
    {
        gl->glGenBuffers( 1, &id );

        if( id == 0 )
        {
            Debug::PrintGLError( gl->glGetError(), "glGenBuffers" );
            Debug::FatalError( "glGenBuffers returned 0 while attempting to create a vertex buffer object inside Nixin::GLBuffer." );
        }
    }

}
