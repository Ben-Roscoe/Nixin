#include "Nixin_UniformBase.h"



namespace Nixin
{



    //
    // UniformBase
    //
    UniformBase::UniformBase( const std::string& uniformName, const ShaderProgram* uniformOwner , OpenGLFunctions *ownerGL )
    {
        name    = uniformName;
        owner   = uniformOwner;
        FindID();
    }



    //
    // GetID
    //
    GLint UniformBase::GetID() const
    {
        return id;
    }



    //
    // GetName
    //
    const std::string& UniformBase::GetName() const
    {
        return name;
    }



    //
    // GetOwner
    //
    const ShaderProgram* GetOwner() const
    {
        return owner;
    }



    // Private:



    //
    // FindID
    //
    void UniformBase::FindID()
    {
        gl->glGetUniformLocation( owner->GetID(), name.c_str() );
    }
}
