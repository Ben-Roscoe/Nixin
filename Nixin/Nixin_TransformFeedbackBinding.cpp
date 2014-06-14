#include "Nixin_TransformFeedbackBinding.h"
#include "Nixin_GLBuffer.h"


namespace Nixin
{


    //
    // TransformFeedbackBinding
    //
    TransformFeedbackBinding::TransformFeedbackBinding( const TransformFeedback* bindingOwner, const GLBuffer* bindingBuffer, GLsizei bindingOffset, GLsizei bindingLength )
    {
        owner   = bindingOwner;
        buffer  = bindingBuffer;
        offset  = bindingOffset;
        length  = bindingLength;
    }



    //
    // TransformFeedbackBinding
    //
    TransformFeedbackBinding::TransformFeedbackBinding( const TransformFeedback *bindingOwner )
    {
        owner  = bindingOwner;
        buffer = nullptr;
        offset = 0;
        length = 0;
    }



    //
    // TransformFeedbackBinding
    //
    TransformFeedbackBinding::TransformFeedbackBinding( const TransformFeedback *bindingOwner, const GLBuffer *bindingBuffer )
    {
        owner   = bindingOwner;
        buffer  = bindingBuffer;
        offset  = 0;
        length  = buffer->GetSize();
    }



    //
    // GetBuffer
    //
    const GLBuffer* TransformFeedbackBinding::GetBuffer() const
    {
        return buffer;
    }



    //
    // GetOwner
    //
    const TransformFeedback* TransformFeedbackBinding::GetOwnder() const
    {
        return owner;
    }



    //
    // GetOffset
    //
    GLsizei TransformFeedbackBinding::GetOffset() const
    {
        return offset;
    }



    //
    // GetLength
    //
    GLsizei TransformFeedbackBinding::GetLength() const
    {
        return length;
    }



    //
    // IsValud
    //
    bool TransformFeedbackBinding::IsValid() const
    {
        return ( owner != nullptr ) && ( buffer != nullptr );
    }



    //
    // IsEmpty
    //
    bool TransformFeedbackBinding::IsEmpty() const
    {
        return buffer == nullptr;
    }



    //
    // IsSubBuffer
    //
    bool TransformFeedbackBinding::IsSubBuffer() const
    {
        return !( IsValid() && ( offset == 0 ) && ( length == buffer->GetSize() ) );
    }



    //
    // IsWholeBuffer
    //
    bool TransformFeedbackBinding::IsWholeBuffer() const
    {
        return IsValid() && ( offset == 0 ) && ( length == buffer->GetSize() );
    }
}
