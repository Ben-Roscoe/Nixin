#include "Nixin_VertexAttribute.h"
#include "Nixin_ShaderProgram.h"



namespace Nixin
{



    // Public:



    //
    // VertexAttribute
    //
    VertexAttribute::VertexAttribute()
    {
        name    = "";
        owner   = nullptr;
        id      = -1;
    }



    //
    // VertexAttribute
    //
    VertexAttribute::VertexAttribute( const std::string& attributeName, const ShaderProgram* attributeOwner )
    {
        name = attributeName;
        owner = attributeOwner;

        FindID();
    }



    //
    // GetID
    //
    GLint VertexAttribute::GetID() const
    {
        return id;
    }



    //
    // GetName
    //
    const std::string& VertexAttribute::GetName() const
    {
        return name;
    }



    //
    // GetOwner
    //
    const ShaderProgram* VertexAttribute::GetOwner() const
    {
        return owner;
    }



    //
    // SetValue
    //
    void VertexAttribute::SetValue( size_t size, GLenum type, GLboolean normalised, int stride, int offset )
    {
        gl->glVertexAttribPointer( id, size, type, normalised, stride, reinterpret_cast<GLvoid*>( NULL + offset ) );
    }



    // Private:



    //
    // FindID
    //
    void VertexAttribute::FindID()
    {
          id = gl->glGetAttribLocation( owner->GetID(), name.c_str() );
    }
}
