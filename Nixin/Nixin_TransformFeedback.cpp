#include "Nixin_TransformFeedback.h"
#include "Nixin_GLBuffer.h"
#include "Nixin_Debug.h"



namespace Nixin
{



    // Public:



    //
    // TransformFeedback
    //
    TransformFeedback::TransformFeedback()
    {
        GenTransformFeedback();

        // Find out the maximum buffer bindings allowed on this system.
        GLint       maxBindings     = 0;
        gl->glGetIntegerv( GL_MAX_TRANSFORM_FEEDBACK_BUFFERS, &maxBindings );

        // Make all bindings empty for now.
        for( size_t i = 0; i < maxBindings; i++ )
        {
            bindings.push_back( TransformFeedbackBinding( this ) );
        }
    }



    //
    // TransformFeedback
    //
    TransformFeedback::TransformFeedback( const TransformFeedback& other )
    {
        gl          = other.gl;
        bindings    = other.bindings;

        if( other.id != 0 )
        {
            GenTransformFeedback();
            Bind();

            for( size_t i = 0; i < bindings.size(); i++ )
            {
                if( !bindings[i].IsEmpty() )
                {
                    if( !bindings[i].IsSubBuffer() )
                    {
                        gl->glBindBufferBase( bindingTarget, i, bindings[i].GetBuffer()->GetID() );
                    }
                    else
                    {
                        gl->glBindBufferRange( bindingTarget, i, bindings[i].GetBuffer()->GetID(), bindings[i].GetOffset(), bindings[i].GetLength() );
                    }
                }
            }
        }
    }



    //
    // TransformFeedback
    //
    TransformFeedback::TransformFeedback( TransformFeedback&& other )
    {
        swap( *this, other );
    }



    //
    // operator=
    //
    TransformFeedback& TransformFeedback::operator=( TransformFeedback other )
    {
        swap( *this, other );
        return *this;
    }



    //
    // ~TransformFeedback
    //
    TransformFeedback::~TransformFeedback()
    {
        if( id != 0 )
        {
            gl->glDeleteTransformFeedbacks( 1, &id );
        }
    }



    //
    // swap
    //
    void swap( TransformFeedback& a, TransformFeedback& b )
    {
        using std::swap;

        swap( a.gl, b.gl );
        swap( a.id, b.id );
        swap( a.bindings, b.bindings );
    }



    //
    // Bind
    //
    void TransformFeedback::Bind() const
    {
        gl->glBindTransformFeedback( target, id );
    }



    //
    // Release
    //
    void TransformFeedback::Release() const
    {
        gl->glBindTransformFeedback( target, 0 );
    }



    //
    // BindBuffer
    //
    void TransformFeedback::BindBuffer( const GLBuffer* buffer, GLuint index )
    {
        if( static_cast<size_t>( index ) >= bindings.size() )
        {
            Debug::FatalError( "An attempt was made to bind a buffer to a transform feedback at index %i while the system only supports %i bindings.", index, bindings.size() );
        }

        gl->glBindBufferBase( bindingTarget, index, buffer->GetID() );
        bindings[index] = TransformFeedbackBinding( this, buffer );
    }



    //
    // BindBuffer
    //
    void TransformFeedback::BindBuffer( const GLBuffer* buffer, GLuint index, GLint offset, GLsizei length )
    {
        if( static_cast<size_t>( index ) >= bindings.size() )
        {
            Debug::FatalError( "Attempted to bind a buffer to a transform feedback at index %i while the system only supports %i bindings.", index, bindings.size() );
        }
        if( offset < 0 || offset >= buffer->GetSize() || length < 0 || length >= buffer->GetSize() )
        {
            Debug::FatalError( "Attempted to bind a buffer to a transform feedback at index %i with an invalide range.", index );
        }

        gl->glBindBufferRange( bindingTarget, index, buffer->GetID(), static_cast<GLintptr>( NULL + offset ), static_cast<GLsizeiptr>( NULL + length ) );
        bindings[index] = TransformFeedbackBinding( this, buffer, offset, length );
    }



    //
    // ReleaseBuffer
    //
    void TransformFeedback::ReleaseBuffer( GLuint index )
    {
        if( index > 0 && index < bindings.size() )
        {
            gl->glBindBufferBase( bindingTarget, index, 0 );
            bindings[index] = TransformFeedbackBinding( this );
        }
        else
        {
            Debug::Warning( "Attempted to release buffer that is outside the range that of bindings that this system supports." );
        }
    }



    //
    // ReleaseAll
    //
    void TransformFeedback::ReleaseAllBuffers()
    {
        for( size_t i = 0; i < bindings.size(); i++ )
        {
            if( !bindings[i].IsEmpty() )
            {
                ReleaseBuffer( i );
            }
        }
    }



    //
    // Begin
    //
    void TransformFeedback::Begin( GLenum primitiveMode ) const
    {
        gl->glBeginTransformFeedback( primitiveMode );
    }



    //
    // End
    //
    void TransformFeedback::End() const
    {
        gl->glEndTransformFeedback();
    }



    //
    // Pause
    //
    void TransformFeedback::Pause() const
    {
        gl->glPauseTransformFeedback();
    }



    //
    // Resume
    //
    void TransformFeedback::Resume() const
    {
        gl->glResumeTransformFeedback();
    }




    //
    // GetBindingsCount
    //
    size_t TransformFeedback::GetBindingCount() const
    {
        size_t count = 0;
        std::for_each( bindings.begin(), bindings.end(), [&count]( const TransformFeedbackBinding& x ){ if( !x.IsEmpty() ) count++; } );
        return count;
    }



    //
    // GetMaxBindings
    //
    size_t TransformFeedback::GetMaxBindings() const
    {
        return bindings.size();
    }



    // Private:



    //
    // GenTransformFeedback
    //
    void TransformFeedback::GenTransformFeedback()
    {
        gl->glGenTransformFeedbacks( 1, &id );

        if( id == 0 )
        {
            Debug::PrintGLError( gl->glGetError(), "glGenTransformFeedbacks" );
            Debug::FatalError( "OpenGL failed to generate a transform feedback object." );
        }
    }
}
