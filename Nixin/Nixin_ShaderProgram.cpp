#include <iostream>


#include "Nixin_ShaderProgram.h"
#include "Nixin_Utility.h"
#include "Nixin_Debug.h"






// Public:



//
// ShaderProgram
//
Nixin::ShaderProgram::ShaderProgram()
{
	linked = false;
	takenLocations = 0;
	id = 0;
}



//
// ShaderProgram
//
Nixin::ShaderProgram::ShaderProgram( const ShaderFile* const shaderFiles, const int numberOfFiles )
{
	linked = false;
	takenLocations = 0;
	id = 0;
	for( int i = 0; i < numberOfFiles; i++ )
	{
		ShaderFile								temp = ShaderFile( shaderFiles[i] );
		errorStatus = LoadShaderFile( temp );
		errorStatus = CompileGLSLShader( temp );
		files.push_back( temp );
	}
}



//
// ShaderProgram
//
Nixin::ShaderProgram::ShaderProgram( const ShaderFile vertex, const ShaderFile fragment )
{
	linked = false;
	takenLocations = 0;
	id = 0;

	// Load vertex shader file.
	ShaderFile									shaderFile = ShaderFile( vertex );
	errorStatus = LoadShaderFile( shaderFile );
	errorStatus = CompileGLSLShader( shaderFile );
	files.push_back( shaderFile );

	// Load fragment shader file.
	shaderFile = ShaderFile( fragment );
	errorStatus = LoadShaderFile( shaderFile );
	errorStatus = CompileGLSLShader( shaderFile );
	files.push_back( shaderFile );
}



//
// ShaderProgram
//
Nixin::ShaderProgram::ShaderProgram( ShaderProgram&& other )
{
	id						= other.id;
	files					= other.files;
	attributeLocations		= other.attributeLocations;
	shaderVariableStatus	= other.shaderVariableStatus;
	linked					= other.linked;
	takenLocations			= other.takenLocations;


	// Move the shader.
	id						= other.id;
	other.id				= 0;

	// Move the files.
	files					= other.files;
	other.files.clear();

    gl                      = std::move( other.gl );
}



//
// operator=
//
Nixin::ShaderProgram& Nixin::ShaderProgram::operator=( ShaderProgram other )
{
	id						= other.id;
	files					= other.files;
	attributeLocations		= other.attributeLocations;
	shaderVariableStatus	= other.shaderVariableStatus;
	linked					= other.linked;
	takenLocations			= other.takenLocations;


	// Move the shader.
	id						= other.id;
	other.id				= 0;

	// Move the files.
	files					= other.files;
	other.files.clear();

    gl                      = std::move( other.gl );

	return					*this;
}



//
// ~ShaderProgram
//
Nixin::ShaderProgram::~ShaderProgram()
{
	if( id != 0 )
	{
        gl->glDeleteProgram( id );
		for( unsigned int i = 0; i < files.size(); i++ )
		{
			if( files[i].id != 0 )
			{
                gl->glDeleteProgram( files[i].id );
			}
		}
		files.clear();
	}
}



//
// GetID
//
const unsigned int Nixin::ShaderProgram::GetID() const
{
	return id;
}




// Main Methods:


//
// LinkProgram
//
const Nixin::ShaderProgram::Error Nixin::ShaderProgram::LinkProgram( const bool enableAllAttributes, const bool deleteFiles )
{
	int						programStatus;

	if( files.size() > 0 )
	{
		// Create the program id.
		if( id != 0 )
		{
            gl->glDeleteProgram( id );
		}
        id = gl->glCreateProgram();

		for( unsigned int i = 0; i < files.size(); i++ )
		{
			// Link to each file using glAttachShader.
            gl->glAttachShader( id, files[i].id );
		}
		BindAttributeLocations( enableAllAttributes );
        gl->glLinkProgram( id );									// Link the program together.

		// Check for errors.
        gl->glGetProgramiv( id, GL_LINK_STATUS, &programStatus );
		if( !programStatus )
		{
			ReadLinkError();
			return Error::LINK_ERROR; // Linking failed.
		}
		else
		{
			linked = true;

			// If specified, we delete all the source files from memory. We don't need them now that the program is compile, and this
			// saves a lot of memory.
			if( deleteFiles )
			{
				for( unsigned int i = 0; i < files.size(); i++ )
				{
					if( files[i].id != 0 )
					{
                        gl->glDeleteProgram( files[i].id );
					}
				}
			}
			return Error::NONE;		 // Success.
		}
	}
	else
	{
		// No files present.
		return Error::NO_FILES_FOUND;
	}
}



//
// AddAttribute
//
void Nixin::ShaderProgram::AddAttribute( const std::string& name )
{
	attributeLocations[name] = takenLocations;
	takenLocations++;
}



//
// EnableAttribute
//
void Nixin::ShaderProgram::EnableAttribute( const std::string& name )
{
	if( attributeLocations.find( name ) != attributeLocations.end() )
	{
		if( linked )
		{
            gl->glEnableVertexAttribArray( attributeLocations[name] );
		}
		else
		{
			std::cout << "The program must be linked before enabling attributes." << std::endl;
		}
	}
	else
	{
		std::cout << "The attribute " << name << "was not found in program " << id << "while trying to enable it." << std::endl;
	}
}



//
// DisableAttribute
//
void Nixin::ShaderProgram::DisableAttribute( const std::string& name )
{
	if( attributeLocations.find( name ) != attributeLocations.end() )
	{
		if( linked )
		{
            gl->glDisableVertexAttribArray( attributeLocations[name] );
		}
		else
		{
			std::cout << "The program must be linked before disabling attributes." << std::endl;
		}
	}
	else
	{
		std::cout << "The attribute " << name << "was not found in program " << id << "while trying to disable it." << std::endl;
	}
}



//
// AddFile
//
void Nixin::ShaderProgram::AddFile( const ShaderFile& shaderFile )
{
	ShaderFile									temp = ShaderFile( shaderFile );

	errorStatus = LoadShaderFile( temp );
	errorStatus = CompileGLSLShader( temp );
	files.push_back( temp );
}



//
// GetErrorStatus
//
const Nixin::ShaderProgram::Error Nixin::ShaderProgram::GetErrorStatus() const
{
	return errorStatus;
}



//==================================================//
// Uniform and Attribute setters.					//
//==================================================//



//
// SetUniform1f
//
void Nixin::ShaderProgram::SetUniform1f( const std::string& name, const float value1 )
{
    gl->glUniform1f( GetUniformLocation( name ), value1 );
}



//
// SetUniform2f
//
void Nixin::ShaderProgram::SetUniform2f( const std::string& name, const float value1, const float value2 )
{
    gl->glUniform2f( GetUniformLocation( name ), value1, value2 );
}



//
// SetUniform3f
//
void Nixin::ShaderProgram::SetUniform3f( const std::string& name, const float value1, const float value2, const float value3 )
{
    gl->glUniform3f( GetUniformLocation( name ), value1, value2, value3 );
}



//
// SetUniform4f
//
void Nixin::ShaderProgram::SetUniform4f( const std::string& name, const float value1, const float value2, const float value3, const float value4 )
{
    gl->glUniform4f( GetUniformLocation( name ), value1, value2, value3, value4 );
}



//
// SetUniformfv
//
void Nixin::ShaderProgram::SetUniformfv( const std::string& name, const int size, const float* const value )
{
    gl->glUniform1fv( GetUniformLocation( name ), size, value );
}




//
// SetUniform1i
//
void Nixin::ShaderProgram::SetUniform1i( const std::string& name, const int value1 )
{
    gl->glUniform1i( GetUniformLocation( name ), value1 );
}



//
// SetUniform2i
//
void Nixin::ShaderProgram::SetUniform2i( const std::string& name, const int value1, const int value2 )
{
    gl->glUniform2i( GetUniformLocation( name ), value1, value2 );
}



//
// SetUniform3i
//
void Nixin::ShaderProgram::SetUniform3i( const std::string& name, const int value1, const int value2, const int value3 )
{
    gl->glUniform3i( GetUniformLocation( name ), value1, value2, value3 );
}



//
// SetUniform4i
//
void Nixin::ShaderProgram::SetUniform4i( const std::string& name, const int value1, const int value2, const int value3, const int value4 )
{
    gl->glUniform4i( GetUniformLocation( name ), value1, value2, value3, value4 );
}



//
// SetUniformiv
//
void Nixin::ShaderProgram::SetUniformiv( const std::string& name, const int size, const int* const value )
{
    gl->glUniform1iv( GetUniformLocation( name ), size, value );
}



////
//// SetUniform1ui
////
//void Nixin::ShaderProgram::SetUniform1ui( const std::string& name, const unsigned int value1 )
//{
//    gl.glUniform1ui( GetUniformLocation( name ), value1 );
//}



////
//// SetUniform2ui
////
//void Nixin::ShaderProgram::SetUniform2ui( const std::string& name, const unsigned int value1, const unsigned int value2 )
//{
//    gl.glUniform2ui( GetUniformLocation( name ), value1, value2 );
//}



////
//// SetUniform3ui
////
//void Nixin::ShaderProgram::SetUniform3ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3 )
//{
//    gl.glUniform3ui( GetUniformLocation( name ), value1, value2, value3 );
//}



////
//// SetUniform4ui
////
//void Nixin::ShaderProgram::SetUniform4ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4 )
//{
//    gl.glUniform4ui( GetUniformLocation( name ), value1, value2, value3, value4 );
//}



////
//// SetUniform1uiv
////
//void Nixin::ShaderProgram::SetUniformuiv( const std::string& name, const int size, const unsigned int* const value )
//{
//    gl.glUniform1uiv( GetUniformLocation( name ), size, value );
//}



//
// SetUniformMatrix
//
void Nixin::ShaderProgram::SetUniformMatrix( const std::string& name, const Matrix& matrix )
{
	if( matrix.GetColumns() == 2 && matrix.GetRows() == 2 )
	{
        gl->glUniformMatrix2fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 3 && matrix.GetRows() == 3 )
	{
        gl->glUniformMatrix3fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 4 && matrix.GetRows() == 4 )
	{
        gl->glUniformMatrix4fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 2 && matrix.GetRows() == 3 )
	{
        //gl.glUniformMatrix2x3fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 3 && matrix.GetRows() == 2 )
	{
       // gl.glUniformMatrix3x2fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 2 && matrix.GetRows() == 4 )
	{
       // gl.glUniformMatrix2x4fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 4 && matrix.GetRows() == 2 )
	{
       // gl.glUniformMatrix4x2fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 3 && matrix.GetRows() == 4 )
	{
        //gl.glUniformMatrix3x4fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
	else if( matrix.GetColumns() == 4 && matrix.GetRows() == 3 )
	{
        //gl.glUniformMatrix4x3fv( GetUniformLocation( name ), 1, true, matrix.GetData() );
	}
}



//
// SetSampler2D
//
void Nixin::ShaderProgram::SetSampler2D( const std::string& name, const unsigned int textureLocation, const Texture& texture )
{
    gl->glActiveTexture( GL_TEXTURE0 + textureLocation );
    gl->glBindTexture( GL_TEXTURE_2D, texture.GetID() );
    gl->glUniform1i( GetUniformLocation( name ), textureLocation );
}



//
// SetSampler2D
//
void Nixin::ShaderProgram::SetSampler2D( const std::string& name, const unsigned int textureLocation, const unsigned int textureID )
{
    gl->glActiveTexture( GL_TEXTURE0 + textureLocation );
    gl->glBindTexture( GL_TEXTURE_2D, textureID );
    gl->glUniform1i( GetUniformLocation( name ), textureLocation );
}





//
// SetArrayStructUniform1f
//
void Nixin::ShaderProgram::SetArrayStructUniform1f( const std::string& name, const float value1, const unsigned int index, const std::string& member )
{
	SetUniform1f( GenerateFinalStructArrayName( name, member, index ), value1 );
}



//
// SetArrayStructUniform2f
//
void Nixin::ShaderProgram::SetArrayStructUniform2f( const std::string& name, const float value1, const float value2, const unsigned int index, const std::string& member )
{
	SetUniform2f( GenerateFinalStructArrayName( name, member, index ), value1, value2 );
}



//
// SetArrayStructUniform3f
//
void Nixin::ShaderProgram::SetArrayStructUniform3f( const std::string& name, const float value1, const float value2, const float value3, const unsigned int index, const std::string& member )
{
	SetUniform3f( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3 );
}



//
// SetArrayStructUniform4f
//
void Nixin::ShaderProgram::SetArrayStructUniform4f( const std::string& name, const float value1, const float value2, const float value3, const float value4, const unsigned int index, const std::string& member )
{
	SetUniform4f( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3, value4 );
}



//
// SetArrayStructUniformfv
//
void Nixin::ShaderProgram::SetArrayStructUniformfv( const std::string& name, const int size, const float* const value, const unsigned int index, const std::string& member )
{
	SetUniformfv( GenerateFinalStructArrayName( name, member, index ), size, value );
}




//
// SetArrayStructUniform1i
//
void Nixin::ShaderProgram::SetArrayStructUniform1i( const std::string& name, const int value1, const unsigned int index, const std::string& member )
{
	SetUniform1i( GenerateFinalStructArrayName( name, member, index ), value1 );
}



//
// SetArrayStructUniform2i
//
void Nixin::ShaderProgram::SetArrayStructUniform2i( const std::string& name, const int value1, const int value2, const unsigned int index, const std::string& member )
{
	SetUniform2i( GenerateFinalStructArrayName( name, member, index ), value1, value2 );
}



//
// SetArrayStructUniform3i
//
void Nixin::ShaderProgram::SetArrayStructUniform3i( const std::string& name, const int value1, const int value2, const int value3, const unsigned int index, const std::string& member )
{
	SetUniform3i( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3 );
}



//
// SetArrayStructUniform4i
//
void Nixin::ShaderProgram::SetArrayStructUniform4i( const std::string& name, const int value1, const int value2, const int value3, const int value4, const unsigned int index, const std::string& member )
{
	SetUniform4i( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3, value4 );
}



//
// SetArrayStructUniformiv
//
void Nixin::ShaderProgram::SetArrayStructUniformiv( const std::string& name, const int size, const int* const value, const unsigned int index, const std::string& member )
{
	SetUniformiv( GenerateFinalStructArrayName( name, member, index ), size, value );
}



//
// SetArrayStructUniform1ui
//
void Nixin::ShaderProgram::SetArrayStructUniform1ui( const std::string& name, const unsigned int value1, const unsigned int index, const std::string& member )
{
    //SetUniform1ui( GenerateFinalStructArrayName( name, member, index ), value1 );
}



//
// SetArrayStructUniform2ui
//
void Nixin::ShaderProgram::SetArrayStructUniform2ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int index, const std::string& member )
{
    //SetUniform2ui( GenerateFinalStructArrayName( name, member, index ), value1, value2 );
}



//
// SetArrayStructUniform3ui
//
void Nixin::ShaderProgram::SetArrayStructUniform3ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int index, const std::string& member )
{
    //SetUniform3ui( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3 );
}



//
// SetArrayStructUniform4ui
//
void Nixin::ShaderProgram::SetArrayStructUniform4ui( const std::string& name, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4, const unsigned int index, const std::string& member )
{
    //SetUniform4ui( GenerateFinalStructArrayName( name, member, index ), value1, value2, value3, value4 );
}



//
// SetArrayStructUniform1uiv
//
void Nixin::ShaderProgram::SetArrayStructUniformuiv( const std::string& name, const int size, const unsigned int* const value, const unsigned int index, const std::string& member )
{
    //SetUniformuiv( GenerateFinalStructArrayName( name, member, index ), size, value );
}



//
// SetArrayStructUniformMatrix
//
void Nixin::ShaderProgram::SetArrayStructUniformMatrix( const std::string& name, const Matrix& matrix, const unsigned int index, const std::string& member )
{
	SetUniformMatrix( GenerateFinalStructArrayName( name, member, index ), matrix );
}



//
// SetArrayStructSampler2D
//
void Nixin::ShaderProgram::SetArrayStructSampler2D( const std::string& name, const unsigned int textureLocation, const Texture& texture, const unsigned int index, const std::string& member )
{
	SetSampler2D( GenerateFinalStructArrayName( name, member, index ), textureLocation, texture );
}



//
// SetArrayStructSampler2D
//
void Nixin::ShaderProgram::SetArrayStructSampler2D( const std::string& name, const unsigned int textureLocation, const int textureID, const unsigned int index, const std::string& member )
{
	SetSampler2D( GenerateFinalStructArrayName( name, member, index ), textureLocation, textureID );
}




//
// SetVertexAttributePointer
//
void Nixin::ShaderProgram::SetVertexAttributePointer( const std::string& name, const int size, const Texture::DataType type, const int stride, const int offset )
{
    gl->glVertexAttribPointer( GetAttributeLocation( name ), size, ( GLenum )( type ), false, stride, ( GLvoid* )( int )offset );
}




// Private:



//
// ReadLinkError
//
void Nixin::ShaderProgram::ReadLinkError() const
{
	int							length				= 0;			// Length of the error message.
	char*						errorMessage		= NULL;			// The error message.

	// Get message length.
    gl->glGetProgramiv( GetID(), GL_INFO_LOG_LENGTH, &length );

	// Allocate space for the error message and the null terminator. Then get the message and null terminate it. 
	errorMessage = new char[length + 1];
    gl->glGetProgramInfoLog( GetID(), length, NULL, errorMessage );
	errorMessage[length] = '\0';

    Debug::Warning( "GLSL Link Error: %s", errorMessage );

	delete[] errorMessage;

}



//
// ReadCompilationError
// Reads the compilation error text handed back by opengl.
//
void Nixin::ShaderProgram::ReadCompilationError( const unsigned int shaderID ) const
{
	int							length				= 0;			// Length of the error message.
	char*							errorMessage		= NULL;			// The error message.


	// Get the the length of the error message.
    gl->glGetShaderiv( shaderID, GL_INFO_LOG_LENGTH, &length );


	// Allocate space for the message + the null terminator. Then get the message.
	errorMessage = new char[length + 1];
    gl->glGetShaderInfoLog( shaderID, length, &length, errorMessage );

    Debug::Warning( "GLSL Compilation Error: %s", errorMessage );

	delete[] errorMessage;
}



//
// BindAttributeLocations
//
void Nixin::ShaderProgram::BindAttributeLocations( const bool enableAllAttributes )
{
	// Find an empty attribute location for the new attribute.
	for( std::map<std::string, int>::iterator itr = attributeLocations.begin(); itr != attributeLocations.end(); itr++ )	// Search the map for the next unused attribute location.
	{
		// Bind it.
        gl->glBindAttribLocation( id, itr->second, itr->first.c_str() );
		if( enableAllAttributes )
		{
			// Enable it.
            gl->glEnableVertexAttribArray( itr->second );
		}
	}
}



//
// GetUniformLocation
// Calls glGetUniformLocation, and checks the result.
//
const int Nixin::ShaderProgram::GetUniformLocation( const std::string& name ) const
{
	int							location;
    location = gl->glGetUniformLocation( id, name.c_str() );

	if( location == -1 )
	{
		std::cout << "Uniform location " << name << " was not found in program with program ID " << id << "." << std::endl;
		return -1;
	}
	
	return location;
}



//
// GetAttributeLocation
//
const int Nixin::ShaderProgram::GetAttributeLocation( const std::string& name ) const
{
	if( attributeLocations.find( name ) != attributeLocations.end() )
	{
		return attributeLocations.at( name );
	}
	else
	{
		std::cout << "Attribute location " << name << " was not found in program with program ID " << id << "." << std::endl; 
		return -1;
	}
}



//
// LoadShaderFile
// Gets a shader file ready for compilation.
//
const Nixin::ShaderProgram::Error Nixin::ShaderProgram::LoadShaderFile( ShaderFile& shaderFile )
{
	// This string will hold the contents of the shader. We will use the helper method in Nixin::Utility
	// to read the file.
	std::string				 fileContents = Utility::GetFileText( shaderFile.fileLocation );		 
	unsigned int			 fileSize	  = fileContents.size();

	// Get the contents as a C string, so opengl can read it. We need a pointer to this pointer
	// so we can't use the .c_str method directly.
	const char*				 rawContents  = fileContents.c_str();

	// Create the shader, and give opengl the source.
    shaderFile.id = gl->glCreateShader( shaderFile.type == ShaderFile::Type::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER );
    gl->glShaderSource( shaderFile.id, 1, ( const GLchar** )&rawContents, ( const int* )&fileSize );

	return Error::NONE;
}



//
// CompileGLSLShader
// Compiles the GLSL shader. Returns any errors.
//
const Nixin::ShaderProgram::Error Nixin::ShaderProgram::CompileGLSLShader( ShaderFile& shaderFile )
{
	int						shaderStatus		= 0;												// The status of the shader after compilation.

    gl->glCompileShader( shaderFile.id );
    gl->glGetShaderiv( shaderFile.id, GL_COMPILE_STATUS, &shaderStatus );								// Compile and get status.

	if( !shaderStatus )
	{
		shaderFile.compiled = false;
		ReadCompilationError( shaderFile.id );
		return Error::COMPILATION_ERROR;															// Return 1 if compilation failed.
	}
	else
	{
		// Flag our success.
		shaderFile.compiled = true;
		return Error::NONE;																			// Return 0 for success.
	}
}



//
// GenerateFinalStructArrayName
//
std::string Nixin::ShaderProgram::GenerateFinalStructArrayName( const std::string& name, const std::string& member, const int index ) const
{
	return name + ( index != -1 ? std::string( "[" ) + std::to_string( index ) + std::string( "]" ) : std::string( "" ) ) + member;
}
