#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

#include <thread>

#include "Nixin_Font.h"
#include "Nixin_Utility.h"
#include "Nixin_Debug.h"
#include "Nixin_Memory_Utility.h"



std::map<std::thread::id, Nixin::Font::FontLibrary> Nixin::Font::ftLibrary;



//
// Initialise
// Initialised the FreeType Library.
//
void Nixin::Font::Initialise()
{
    // Check if this thread has an FT library. If not, create one.
    if( ftLibrary.find( std::this_thread::get_id() ) != ftLibrary.end() )
    {
        FontLibrary             fontLibrary;
        ftLibrary[std::this_thread::get_id()] = fontLibrary;
        if( FT_Init_FreeType( &ftLibrary[std::this_thread::get_id()].library ) )
        {
            ftLibrary.erase( ftLibrary.find( std::this_thread::get_id() ) );
            Nixin::Debug::FatalError( "Could not create FreeType library for thread." );
        }
        ftLibrary[std::this_thread::get_id()].uses = 1;
    }
    else
    {
        ftLibrary[std::this_thread::get_id()].uses += 1;
    }
}



//
// Uninitialise
// Unititialises the FreeType Library.
//
void Nixin::Font::Uninitialise()
{
	if( ftLibrary.find( std::this_thread::get_id() ) != ftLibrary.end() )
	{
        ftLibrary[std::this_thread::get_id()].uses -= 1;
        if( ftLibrary[std::this_thread::get_id()].uses <= 0 )
        {
            FT_Done_FreeType( ftLibrary[std::this_thread::get_id()].library );
        }
	}
}



//
// Font
//
Nixin::Font::Font( const std::string& fontName, const Point& size )
{	
	if( ftLibrary.find( std::this_thread::get_id() ) != ftLibrary.end() && &ftLibrary[std::this_thread::get_id()] )
	{
		// Load the font face.
        if( FT_New_Face( ftLibrary[std::this_thread::get_id()].library, fontName.c_str(), 0, &fontFace ) == FT_Err_Unknown_File_Format )
		{
			Debug::FatalError( "The FreeType Library failed to recognise the true type font file." );
		}
	
		// Set spacing to default.
		characterPadding = Point( defaultPadding, defaultPadding );

		// Set the point size, and create the character bitmap.
		SetCharacterPointSize( size );

		// Set the spacing to default.
		spacing.x = defaultSpacing;
		spacing.y = defaultSpacing;
	}
	else
	{
		Debug::FatalError( "The FreeType Library was not initialised before use. This could be due to constructing the Nixin::Font with a different thread from which intialised the font library." );
	}
}



//
// Move Font
//
Nixin::Font::Font( Font&& other )
{
	characterSize		= other.characterSize;
	characterPadding	= other.characterPadding;
	spacing				= other.spacing;

	texture				= std::move( other.texture );
	fontFace			= other.fontFace;

	other.fontFace		= nullptr;
}



//
// operator=
//
Nixin::Font& Nixin::Font::operator=( Font&& other )
{
	characterSize		= other.characterSize;
	characterPadding	= other.characterPadding;
	spacing				= other.spacing;

	texture				= std::move( other.texture );
	fontFace			= other.fontFace;

	other.fontFace		= nullptr;

	return				*this;
}



//
// ~Font
//
Nixin::Font::~Font()
{
	if( fontFace != nullptr )
	{
		FT_Done_Face( fontFace );
	}
}



//
// GetCharacterBounds
// Gets the offset and dimensions of the given character in pixels.
//
const Nixin::Rectangle& Nixin::Font::GetCharacterBounds( const unsigned char character ) const
{
	return characterBounds[( unsigned int )character];
}



//
// GetChacterBitmap
//
const Nixin::Texture& Nixin::Font::GetCharacterBitmap() const
{
	return texture;
}



//
// GetCharacterPadding
// Gets the padding inbetween characters vertically and horizontally.
//
const Nixin::Point& Nixin::Font::GetCharacterPadding() const
{
	return characterPadding;
}



//
// SetCharacterPadding
// Sets the padding inbetween characters vertically and horizontally.
//
void Nixin::Font::SetCharacterPadding( const Point& newPadding )
{
	characterPadding = newPadding;
}



//
// GetCharacterPointSize
// Gets the size of the characters in points.
//
const Nixin::Point& Nixin::Font::GetCharacterPointSize() const
{
	return characterSize;
}



//
// SetCharacterPointSize
// Sets a new point size of the characters. This means a new bitmap must be generated.
//
void Nixin::Font::SetCharacterPointSize( const Point& newPointSize )
{
	if( FT_Set_Char_Size( fontFace, newPointSize.x * freeTypeSizeCompensation, newPointSize.y * freeTypeSizeCompensation, DPI, DPI ) )
	{
		Debug::FatalError( "Could not set character point size." );
	}
	characterSize = newPointSize;
	CreateFontTexture();
}



//
// GetSpacing
// Gets the vertical and horizontal spacing.
//
const Nixin::Point& Nixin::Font::GetSpacing() const
{
	return spacing;
}



//
// SetSpacing
// Sets the vertical and horizontal spacing.
//
void Nixin::Font::SetSpacing( const Point& newSpacing )
{
	spacing = newSpacing;
}



// Private:



//
// LoadNewCharacterBitmap
//
void Nixin::Font::CreateFontTexture()
{
	FT_BitmapGlyph								bitmapGlyph;									// The bitmapGlyph object.
	FT_Bitmap									characterBitmap;								// The final bitmap for a certain character.
	FT_Glyph									glyph;											// The glyph object for a character.
	std::array<void*, charactersPerTexture>		buffers;										// The character bitmap pixel data.
	int											paddedWidth;		
	int											paddedHeight;

	int											currentXOffset = 0;								// This is tracked so that we can remember the position of the character in texture coordinates later.
	int											currentYOffset = 0;
	int											deltaY		   = 0;

	
	// For each 8-bit character.
	for( int x = 0; x < charactersPerRow; x++ )
	{
		for( int y = 0; y < charactersPerColumn; y++ )
		{
			// Load the character.
			if( FT_Load_Char( fontFace, y + ( x * charactersPerColumn ), FT_LOAD_RENDER ) )
			{
				throw std::exception();
			}

			// Next we initialise the glyph for this character.
			if( FT_Get_Glyph( fontFace->glyph, &glyph ) )
			{
				throw std::exception();
			}

			// We then create the bitmap for this character.
			if( FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, true ) )
			{
				throw std::exception();
			}

			// Get the bitmap object.
			bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>( glyph );
			characterBitmap = bitmapGlyph->bitmap;

			// Expand the pixel data due to alpha channels.
			paddedWidth			 = characterBitmap.width;
			paddedHeight		 = characterBitmap.rows;

			GLubyte*			expandedData		 = new GLubyte[2 * paddedWidth * paddedHeight];

			for( int j = 0; j < paddedHeight; j++ )
			{
				for( int i = 0; i < paddedWidth; i++ )
				{
					expandedData[2 * ( i + j * paddedWidth )] = expandedData[2 * ( i + j * paddedWidth ) + 1] = ( i >= characterBitmap.width || j >= characterBitmap.rows ) ? 0 : characterBitmap.buffer[i + characterBitmap.width * j];
				}
			}

			// Add the data to our vectors.
			buffers[y + ( x * charactersPerColumn )] = expandedData;

			// Remember the offset / size of this character.
			characterBounds[y + ( x * charactersPerColumn )] = Rectangle( currentXOffset, currentYOffset, paddedWidth, paddedHeight );

			// Increase x offset.
			currentXOffset += paddedWidth;

			// Free the glyph object.
			FT_Done_Glyph( glyph );
		
			// Get the largest height of this row.
			deltaY = deltaY < paddedHeight ? paddedHeight : deltaY; 
		}
		currentYOffset += deltaY;
		currentXOffset = 0;
		deltaY = 0;
	}


	// Create the texture from our data arrays.
	texture.FromDataArray( std::vector<void*>( buffers.begin(), buffers.end() ), std::vector<Rectangle>( characterBounds.begin(), characterBounds.end() ) );

	// Delete all the pixel data as OpenGL now has it's own copy.
	for( unsigned int i = 0; i < buffers.size(); i++ )
	{
		delete buffers[i];
	}
}

