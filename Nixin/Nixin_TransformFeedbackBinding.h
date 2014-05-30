#ifndef NIXIN_TRANSFORMFEEDBACKBINDING_H
#define NIXIN_TRANSFORMFEEDBACKBINDING_H


#include <QOpenGLFunctions>


namespace Nixin
{


    class TransformFeedback;
    class GLBuffer;
    class TransformFeedbackBinding
    {



    public:



        TransformFeedbackBinding( const TransformFeedback* bindingOwner );
        TransformFeedbackBinding( const TransformFeedback* bindingOwner, const GLBuffer* bindingBuffer );
        TransformFeedbackBinding( const TransformFeedback* bindingOwner, const GLBuffer* bindingBuffer, GLsizei bindingOffset, GLsizei bindingLength );


        const GLBuffer*                 GetBuffer() const;
        const TransformFeedback*        GetOwnder() const;
        GLsizei                         GetOffset() const;
        GLsizei                         GetLength() const;

        bool                            IsValid() const;
        bool                            IsEmpty() const;
        bool                            IsSubBuffer() const;
        bool                            IsWholeBuffer() const;


    private:



        const GLBuffer*                 buffer      = nullptr;
        const TransformFeedback*        owner       = nullptr;
        GLsizei                         offset      = 0;
        GLsizei                         length      = 0;


    };
}



#endif // NIXIN_TRANSFORMFEEDBACKBINDING_H
