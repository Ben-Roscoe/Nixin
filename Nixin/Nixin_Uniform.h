#ifndef NIXIN_UNIFORM_H
#define NIXIN_UNIFORM_H


#include "Nixin_Matrix.h"
#include "Nixin_Types.h"
#include "Nixin_UniformBase.h"
#include "Nixin_UniformValues.h"

#include <QOpenGLFunctions_4_3_Core>
#include <functional>

namespace Nixin
{

    // Set uniform functions.
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1f& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2f& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3f& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4f& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1fv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1fv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1fv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1fv& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1i& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2i& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3i& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4i& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1iv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2iv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3iv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4iv& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1ui& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2ui& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3ui& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4ui& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform1uiv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform2uiv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform3uiv& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const Uniform4uiv& value );

    void    SetUniform( OpenGLFunctions* gl, GLint location, const UniformMatrix& value );
    void    SetUniform( OpenGLFunctions* gl, GLint location, const UniformMatrixv& value );


    template<typename T>
    class Uniform : public UniformBase
    {
    public:

        Uniform( const std::string& uniformName, const ShaderProgram* uniformOwner );

        void                        SetValue( const T& newValue );
        const T&                    GetValue() const;


    private:


        T                           value;


    };



    //
    // Uniform
    //
    template<typename T>
    Uniform<T>::Uniform( const std::string& uniformName, const ShaderProgram* uniformOwner ) : UniformBase( uniformName, uniformOwner )
    {
        assignToShader = shaderAssignment;
    }



    //
    // SetValue
    //
    template<typename T>
    void Uniform<T>::SetValue( const T& newValue )
    {
        SetUniform( gl, id, newValue );
    }



    //
    // GetValue
    //
    template<typename T>
    const T& Uniform<T>::GetValue() const
    {
        return value;
    }
}

#endif // NIXIN_UNIFORM_H
