

#include <fstream>

#include "Nixin_Utility.h"
#include "Nixin_Debug.h"



std::map<std::thread::id, Nixin::ShaderProgram*> Nixin::Utility::NixinSpriteShader;
std::map<std::thread::id, Nixin::ShaderProgram*> Nixin::Utility::NixinPrimitiveShader;


//
// GetNixinSpriteShader
//
Nixin::ShaderProgram& Nixin::Utility::GetNixinSpriteShader()
{
	return *( NixinSpriteShader[std::this_thread::get_id()] );
}



//
// GetNixinPrimitiveShader
//
Nixin::ShaderProgram& Nixin::Utility::GetNixinPrimitiveShader()
{
	return *( NixinPrimitiveShader[std::this_thread::get_id()] );
}



//
// InitialiseNEShaders
// Initialise all the shaders that are a part of the NE.
//
void Nixin::Utility::InitialiseNEShaders()
{	
	// Set up the default 2D shader.
	NixinSpriteShader[std::this_thread::get_id()] = new ShaderProgram( ShaderFile( "spriteVertex.txt", ShaderFile::Type::VERTEX ), ShaderFile( "spriteFragment.txt", ShaderFile::Type::FRAGMENT ) );
	NixinSpriteShader[std::this_thread::get_id()]->AddAttribute( "vertexPosition" );
	NixinSpriteShader[std::this_thread::get_id()]->AddAttribute( "texCoords" );
	NixinSpriteShader[std::this_thread::get_id()]->AddAttribute( "tint" );
	NixinSpriteShader[std::this_thread::get_id()]->LinkProgram( true, true );

	NixinPrimitiveShader[std::this_thread::get_id()] = new ShaderProgram( ShaderFile( "primitiveVertex.txt", ShaderFile::Type::VERTEX ), ShaderFile( "PrimitiveFragment.txt", ShaderFile::Type::FRAGMENT ) );
	NixinPrimitiveShader[std::this_thread::get_id()]->AddAttribute( "position" );
	NixinPrimitiveShader[std::this_thread::get_id()]->AddAttribute( "colour" );
	NixinPrimitiveShader[std::this_thread::get_id()]->LinkProgram( true, true );
}



//
// UninitialiseNEShaders
//
void Nixin::Utility::UninitialiseNEShaders()
{
	delete NixinSpriteShader[std::this_thread::get_id()];
	NixinSpriteShader.erase( std::this_thread::get_id() );

	delete NixinPrimitiveShader[std::this_thread::get_id()];
	NixinPrimitiveShader.erase( std::this_thread::get_id() );
}



//
// TokeniseString
// Takes a string and returns an std::vector of strings. This vector contains the original string's
// substrings which are divided by certain characters.
//
std::vector<std::string> Nixin::Utility::TokeniseString( const std::string& str, const std::string& dividers, const bool tokenisePerChar, const bool removeDividers )
{
    std::vector<std::string>        tokens;
    size_t                          last = 0;

    for( size_t i = 1; i < str.size(); i++ )
    {
        if( dividers.find( str[i] ) )
        {
            if( i - last != 1 && !removeDividers )
            {
                tokens.push_back( str.substr( last, ( i - last ) ) );
            }
            last = i;
        }
    }
	return tokens;
}



//
// GetNextPowerOfTwo
// Gets the next power of two after x.
//
int Nixin::Utility::GetNextPowerOfTwo( const int x )
{
	int					next = 1;

	while( next < x )
	{
		next <<= 1;			// Shift by one bit. Increase by a power of 2 until we are larger than x.
	}
	return next;
}



//
// GetFileText
// Returns an std::string that contains the file in ASCII characters.
//
std::string Nixin::Utility::GetFileText( const std::string& fileName )
{
	// File stream.
	std::ifstream				file;
	std::string					contents;
	unsigned int				lineCount	= 0;


	// Open the file.
    file.open( fileName.c_str(), std::fstream::in );
    if( !file.is_open() )
	{
		// Throw if the file failed to open.
		Nixin::Debug::FatalError( "Could not open file for reading." );
	}

	// Obtain each character in the file and append it to contents.
	while( !file.eof() )
	{
		contents += file.get();
	}

	// Close the file and return the contents.
	file.close();
	return contents;
}





