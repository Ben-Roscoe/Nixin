#ifndef NIXIN_TRANSFORMFEEDBACK_H
#define NIXIN_TRANSFORMFEEDBACK_H


#include "Nixin_TransformFeedbackBinding.h"
#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>
#include <vector>


namespace Nixin
{
    class TransformFeedback
    {



    public:



        TransformFeedback();
        TransformFeedback( const TransformFeedback& other );
        TransformFeedback( TransformFeedback&& other );
        TransformFeedback& operator=( TransformFeedback other );
        ~TransformFeedback();

        friend void                                 swap( TransformFeedback& a, TransformFeedback& b );

        void                                        Bind() const;
        void                                        Release() const;
        void                                        BindBuffer( const GLBuffer* buffer, GLuint index );
        void                                        BindBuffer( const GLBuffer* buffer, GLuint index, GLint offset, GLsizei length );
        void                                        ReleaseBuffer( GLuint index );
        void                                        ReleaseAllBuffers();

        void                                        Begin( GLenum primitiveMode ) const;
        void                                        End() const;
        void                                        Pause() const;
        void                                        Resume() const;

        size_t                                      GetBindingCount() const;
        size_t                                      GetMaxBindings() const;


    private:


        static const GLenum                         target          = GL_TRANSFORM_FEEDBACK;
        static const GLenum                         bindingTarget   = GL_TRANSFORM_FEEDBACK_BUFFER;


        OpenGLFunctions*                            gl              = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                                      id              = 0;
        std::vector<TransformFeedbackBinding>       bindings;


        void                                        GenTransformFeedback();

    };
}




#endif // NIXIN_TRANSFORMFEEDBACK_H
