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
#include "Nixin_VertexAttribute.h"



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
        void									AddFile( const ShaderFile& shaderFile );
        void									RemoveFile( const ShaderFile& shaderFile );
        void                                    EnableAttribute( const std::string& name ) const;
        void                                    EnableAllAttributes() const;
        void                                    DisableAttribute( const std::string& name ) const;
        void                                    DisableAllAttributes() const;

        template<typename T>
        const T&                                GetUniform( const std::string& name ) const;
        template<typename T>
        void                                    SetUniform( const std::string& name, const T& value );

		// Attributes.
        void									SetAttribute( const std::string& name, int size, GLboolean normalised, GLenum type, int stride, int offset );


		// Disable copying.
        ShaderProgram( const ShaderProgram& other )				= delete;



	private:



        OpenGLFunctions*                          gl            = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                                    id            = 0;
        bool									  linked        = false;

        std::map<std::string, std::unique_ptr<UniformBase>> uniforms;
        std::map<std::string, VertexAttribute>              attributes;
        std::map<std::string, UniformType>                  types;

        std::vector<Field>                        attributeInfo;
        std::vector<Field>                        uniformInfo;



        void                                      GenProgram();
        void                                      AddMetaData();
        void                                      AddUniformStruct( const std::string& name, const UniformType& type );
        void                                      AddUniform( const std::string& name, const std::string& type );
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
        static_cast<Uniform<T>&>( *uniforms[name].get() ).SetValue( value );
    }


}


#endif

