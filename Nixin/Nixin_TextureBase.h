#ifndef NIXIN_TEXTUREBASE_H
#define NIXIN_TEXTUREBASE_H



#include "Nixin_Types.h"
#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{
    class TextureBase
    {



    public:



        TextureBase();
        TextureBase( const TextureBase& other );
        TextureBase( TextureBase&& other );
        TextureBase& operator=( TextureBase other );
        virtual ~TextureBase();

        friend void                        swap( TextureBase& a, TextureBase& b );

        virtual void                       Bind() const = 0;
        virtual void                       GetData( GLint level, GLenum format, GLenum type, GLvoid* data = 0 ) const = 0;



    protected:




        OpenGLFunctions*                    gl    = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                              id    = 0;


        void                                GenTexture();



    };
}



#endif // NIXIN_TEXTUREBASE_H
