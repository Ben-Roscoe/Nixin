#ifndef _NIXIN_SHADERPROGRAM_H_
#define _NIXIN_SHADERPROGRAM_H_


#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Nixin_Matrix.h"
#include "Nixin_Texture.h"
#include "Nixin_ShaderFile.h"
#include "Nixin_Uniform.h"
#include "Nixin_UniformBase.h"



namespace Nixin
{


	class ShaderProgram
	{



	public:





        ShaderProgram();
		ShaderProgram( ShaderProgram&& other );
        ShaderProgram& operator=( ShaderProgram&& other );
		~ShaderProgram();

        friend void                             swap( ShaderProgram& a, ShaderProgram& b );

        GLuint                                  GetID() const;
        bool                                    LinkProgram();
        void									AddFile( const ShaderFile &shaderFile );
        void									RemoveFile( const ShaderFile &shaderFile );

        template<typename T>
        const T&                                GetUniform( const std::string& name ) const;
        template<typename T>
        void                                    SetUniform( const std::string& name, const T& value );

		// Attributes.
        void									SetVertexAttributePointer( const std::string& name, const int size, const Texture::DataType type, const int stride, const int offset );


		// Disable copying.
        ShaderProgram( const ShaderProgram& other )				= delete;



	private:



        OpenGLFunctions*                          gl            = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                                    id            = 0;
        bool									  linked        = false;

        std::vector<ShaderFile*>                   files;
        std::map<std::string, std::unique_ptr<UniformBase>> uniforms;



        void                                      GenProgram();
        void                                      GeneratorUniforms();
	};




    //
    // GetUniform
    //
    template<typename T>
    const T& ShaderProgram::GetUniform( const std::string& name ) const
    {
        return static_cast<Uniform<T>&>( uniforms[name].get() ).GetValue();
    }



    //
    // SetUniform
    //
    template<typename T>
    void ShaderProgram::SetUniform( const std::string& name, const T& value )
    {
        static_cast<Uniform<T>&>( uniforms[name].get() ).SetValue( value );
    }

}


#endif

