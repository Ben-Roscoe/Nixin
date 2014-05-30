#ifndef _NIXIN_FONT_H_
#define _NIXIN_FONT_H_

#include "Nixin_Colour.h"
#include "Nixin_Point.h"
#include "Nixin_Texture.h"
#include "Nixin_Rectangle.h"

#include <memory>
#include <map>
#include <thread>
#include <array>

struct FT_LibraryRec_;
struct FT_FaceRec_;
typedef FT_LibraryRec_* FT_Library;
typedef FT_FaceRec_* FT_Face;



namespace Nixin
{

	class Font
	{



	public:



		static void										Initialise();
		static void										Uninitialise();

		
		Font( const std::string& fontName, const Point& size );
		Font( Font&& other );
		Font& operator=( Font&& other ); 
		~Font();

		void											DrawString( const std::string& text, const Point& position );
		const Rectangle&								GetCharacterBounds( const unsigned char character ) const;
		const Texture&								    GetCharacterBitmap() const;

		const Point&									GetCharacterPadding() const;
		void											SetCharacterPadding( const Point& newPadding );
		const Point&									GetCharacterPointSize() const;
		void											SetCharacterPointSize( const Point& newPointSize );
		const Point&									GetSpacing() const;
		void											SetSpacing( const Point& newSpacing );

		Font( const Font& other )						= delete;



	private:



        //
        // Counts the amount of GameWindows uses this library on this thread.
        //
        struct FontLibrary
        {
            FT_Library              library;
            unsigned int            uses;
        };
		

        static std::map<std::thread::id, FontLibrary>	ftLibrary;
		static const int								defaultPadding					= 3;
		static const int								defaultSpacing					= 9;
		static const int								freeTypeSizeCompensation		= 64;
		static const int								DPI								= 300;
		static const int								charactersPerRow				= 16;
		static const int								charactersPerColumn				= 8;
		static const int								charactersPerTexture			= 128;					// Each ASCII char.

		Point											characterSize					= Point( 0, 0 );
		Point											characterPadding				= Point( 0, 0 );
		Point											spacing							= Point( 0, 0 );
		FT_Face											fontFace						= {0};
		Texture											texture							= { 0, 0, Texture::ToFormat::RGBA, Texture::FromFormat::RGBA, Texture::DataType::FLOAT, Texture::WrapMode::REPEAT, Texture::MinFilterMode::MIN_LINEAR, Texture::MagFilterMode::MAG_LINEAR, false, 0.0f };
		std::array<Rectangle, charactersPerTexture>		characterBounds;
	

		void											CreateFontTexture();



	};
}



#endif
