#ifndef NIXIN_UNIFORMBASE_H
#define NIXIN_UNIFORMBASE_H


#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{


    class ShaderProgram;
    class UniformBase
    {



    public:




        UniformBase( const std::string& uniformName, const ShaderProgram* uniformOwner );


        GLint                       GetID() const;
        const std::string&          GetName() const;
        const ShaderProgram*        GetOwner() const;



    protected:




        OpenGLFunctions*            gl          = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLint                       id          = -1;
        std::string                 name        = "";
        const ShaderProgram*        owner       = nullptr;



        void                        FindID();



    };
}



#endif // NIXIN_UNIFORMBASE_H
