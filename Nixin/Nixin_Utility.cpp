

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
	std::vector<std::string>        tokens;									// The final tokens to return.
	std::string						currentToken;							// Current token being added to the vector.
	int								foundPosition = str.size() - 1;         // The current position of the nearest divider.
	int								lastPosition = 0;						// The position of the last divider.
	int								tempPosition = 0;						// This is used to find the closest divider out of all dividers.

	do
	{
		// Set found position to the largest value possible. This will be the position of the last divider, if one does not exist ( so the entire string will still be
		// read as a token ).
		foundPosition = str.size();

		// If we want to tokenise the string with dividers per char.
		if( tokenisePerChar )
		{
			// Loop through each divider and see which one is closest to the current position in the string.
			for( int unsigned i = 0; i < dividers.size(); i++ )
			{
				tempPosition = str.find( dividers[i], lastPosition );
				if( tempPosition < foundPosition && tempPosition != std::string::npos )
				{
					// Save the closest divider position.
					foundPosition = tempPosition;
				}
			}
		}
		// Otherwise treat the entire string as one divider.
		else
		{
			foundPosition = str.find( dividers, lastPosition );
		}

		// Take the substring from the previous position, to the next divider. Do not allow empty strings.
		currentToken = str.substr( lastPosition, foundPosition - lastPosition );
		if( currentToken != "" )
		{
			tokens.push_back( currentToken );
		}

		// If the user has chosen to keep dividers, they will be stored as their own token.
		if( !removeDividers )
		{
			if( foundPosition != str.size() )
			{
				// Get the substring from the current divider to the current divider + 1 ( must be the divider itself ).
				tokens.push_back( str.substr( foundPosition, 1 ) );
			}
		}

		if( tokenisePerChar )
		{
			// We're done with this divider, so move past it by 1 position.
			lastPosition = foundPosition + 1;
		}
		else
		{
			// We're done with this divider, and since it's a string, then increase position by its length.
			lastPosition = foundPosition + dividers.size();
		}

	// While the position of the next divider is within the string.
	} while( foundPosition != std::string::npos && foundPosition != str.size() );


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
	if( file.fail() )
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





