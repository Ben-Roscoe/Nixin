#include "Nixin_UniformBase.h"
#include "Nixin_ShaderProgram.h"


namespace Nixin
{



    //
    // UniformBase
    //
    UniformBase::UniformBase( const std::string& uniformName, const ShaderProgram* uniformOwner )
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
    const ShaderProgram* UniformBase::GetOwner() const
    {
        return owner;
    }



    // Private:



    //
    // FindID
    //
    void UniformBase::FindID()
    {
        id = gl->glGetUniformLocation( owner->GetID(), name.c_str() );
    }
}
