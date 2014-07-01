#ifndef NIXIN_VERTEXATTRIBUTE_H
#define NIXIN_VERTEXATTRIBUTE_H


#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>
#include <string>


namespace Nixin
{
    class ShaderProgram;
    class VertexAttribute
    {



    public:


        VertexAttribute();
        VertexAttribute( const std::string& attributeName, const ShaderProgram* attributeOwner );


        GLint                   GetID() const;
        const std::string&      GetName() const;
        const ShaderProgram*    GetOwner() const;

        void                    SetValue( size_t size, GLenum type, GLboolean normalised, int stride = 0, int offset = 0 );


    private:



        OpenGLFunctions*        gl          = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLint                   id          = -1;
        std::string             name        = "";
        const ShaderProgram*    owner       = nullptr;

        void                    FindID();



    };
}



#endif // NIXIN_VERTEXATTRIBUTE_H
