#ifndef _NIXIN_SHADERPROGRAM_H_
#define _NIXIN_SHADERPROGRAM_H_


#include <string>
#include <map>
#include <memory>
#include <QOpenGLFunctions>

#include "Nixin_Matrix.h"
#include "Nixin_Texture.h"


typedef unsigned int GLenum;

namespace Nixin
{




	//
	// Attribute
	//
	struct Attribute
	{
		char				name[50];
		unsigned int		id;
	};



	//
	// Uniform
	//
	struct Uniform
	{
		char				name[50];
		unsigned int		id;
	};



	//
	// ShaderFile
	//
	struct ShaderFile
	{


		//
		// ShaderType
		// Specifies the type of shader to compile and use.
		//
		enum Type
		{
			VERTEX,
			FRAGMENT,
		};


		unsigned int			id;
		Type				type;
		std::string			fileLocation;
		bool				compiled;


		//
		// ShaderFile
		//
		ShaderFile( const std::string& name, const Type shaderType )
		{
			type = shaderType;
			fileLocation = name;
			compiled = false;
		}
	};




	class ShaderProgram
	{



	public:







		//
		// ShaderError
		// Specifies a type of shader error.
		//
		enum class Error
		{
			LINK_ERROR,
			COMPILATION_ERROR,
			COULD_NOT_FIND_FILE,
			NO_FILES_FOUND,
			NONE,
		};


		ShaderProgram();																			// Empty program.
		ShaderProgram( ShaderProgram&& other );
		ShaderProgram( const ShaderFile* const shaderFile, const int numberOfFiles );				// Gets the specified files ready for linking.
		ShaderProgram( const ShaderFile vertex, const ShaderFile fragment );
		~ShaderProgram();

		ShaderProgram&												operator=( ShaderProgram other );

		const unsigned int											GetID() const;

		const ShaderProgram::Error									LinkProgram( const bool enableAllAttributes, const bool deleteFiles );
		void														AddAttribute( const std::string& name );
		void														EnableAttribute( const std::string& name );
		void														DisableAttribute( const std::string& name );

		void														AddFile( const ShaderFile& shaderFile );

		const ShaderProgram::Error									GetErrorStatus() const;

		// Uniforms:

		// Floats.
		void														SetUniform1f( const std::string& name, const float value1 );
		void														SetUniform2f( const std::string& name, const float value1, const float value2 );														
		void														SetUniform3f( const std::string& name, const float value1, const float value2, const float value3 );
		void														SetUniform4f( const std::string& name, const float value1, const float value2, const float value3, const float value4 );
		void														SetUniformfv( const std::string& name, const int size, const float* const value );

		// Ints.
		void														SetUniform1i( const std::string& name, const int value1 );
		void														SetUniform2i( const std::string& name, const int value1, const int value2 );
		void														SetUniform3i( const std::string& name, const int value1, const int value2, const int value3 );
		void														SetUniform4i( const std::string& name, const int value1, const int value2, const int value3, const int value4 );
		void														SetUniformiv( const std::string& name, const int size, const int* const value );

		// Unsigned ints.
//		void														SetUniform1ui( const std::string& name, const unsigned int value1 );
//		void														SetUniform2ui( const std::string& name, const unsigned int value1, const unsigned int value2 );
//		void														SetUniform3ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3 );
//		void														SetUniform4ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4 );
//		void														SetUniformuiv( const std::string& name, const int size, const unsigned int* const value );

		// Matrices.
		void														SetUniformMatrix( const std::string& name, const Matrix& matrix );

		// Samplers
		void														SetSampler2D( const std::string& name, const unsigned int textureLocation, const Texture& texture );
		void														SetSampler2D( const std::string& name, const unsigned int textureLocation, const unsigned int textureID );

		// Array Uniforms:

		// Floats.
		void														SetArrayStructUniform1f( const std::string& name, const float value1, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform2f( const std::string& name, const float value1, const float value2, const unsigned int index, const std::string& member );														
		void														SetArrayStructUniform3f( const std::string& name, const float value1, const float value2, const float value3, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform4f( const std::string& name, const float value1, const float value2, const float value3, const float value4, const unsigned int index, const std::string& member );
		void														SetArrayStructUniformfv( const std::string& name, const int size, const float* const value, const unsigned int index, const std::string& member );
																
		// Ints.													
		void														SetArrayStructUniform1i( const std::string& name, const int value1, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform2i( const std::string& name, const int value1, const int value2, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform3i( const std::string& name, const int value1, const int value2, const int value3, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform4i( const std::string& name, const int value1, const int value2, const int value3, const int value4, const unsigned int index, const std::string& member );
		void														SetArrayStructUniformiv( const std::string& name, const int size, const int* const value, const unsigned int index, const std::string& member );
																   
		// Unsigned ints.											   
		void														SetArrayStructUniform1ui( const std::string& name, const unsigned int value1, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform2ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform3ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int index, const std::string& member );
		void														SetArrayStructUniform4ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4, const unsigned int index, const std::string& member );
		void														SetArrayStructUniformuiv( const std::string& name, const int size, const unsigned int* const value, const unsigned int index, const std::string& member );
																  
		// Matrices.												  
		void														SetArrayStructUniformMatrix( const std::string& name, const Matrix& matrix, const unsigned int index, const std::string& member );
																  
		// Samplers													  
		void														SetArrayStructSampler2D( const std::string& name, const unsigned int textureLocation, const Texture& texture, const unsigned int index, const std::string& member );
		void														SetArrayStructSampler2D( const std::string& name, const unsigned int textureLocation, const int textureID, const unsigned int index, const std::string& member );

		// Attributes.
		void														SetVertexAttributePointer( const std::string& name, const int size, const Texture::DataType type, const int stride, const int offset );


		// Disable copying.
		ShaderProgram( const ShaderProgram& other )					= delete;



	private:



        std::unique_ptr<QOpenGLFunctions>                           gl                      = std::unique_ptr<QOpenGLFunctions>( new QOpenGLFunctions{ QOpenGLContext::currentContext() } );
        unsigned int                                                id;
		std::vector<ShaderFile>										files;
		std::map<std::string, int>									attributeLocations;
		std::map<std::string, bool>									shaderVariableStatus;
		bool														linked;
		int															takenLocations;

		ShaderProgram::Error										errorStatus;


		void														ReadLinkError() const;
		void														ReadCompilationError( const unsigned int shaderID ) const;
		const ShaderProgram::Error									CompileGLSLShader( ShaderFile& shaderFile );
		const ShaderProgram::Error									LoadShaderFile( ShaderFile& shaderFile );
		void														BindAttributeLocations( const bool enableAllAttributes );
		const int													GetUniformLocation( const std::string& name ) const;
		const int													GetAttributeLocation( const std::string& name ) const;
		std::string													GenerateFinalStructArrayName( const std::string& name, const std::string& member, const int index ) const;


	};

}


#endif

