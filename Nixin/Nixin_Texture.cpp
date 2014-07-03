#include <sstream>

#include "Nixin_Texture.h"
#include "Nixin_ShaderProgram.h"
#include "Nixin_Image.h"
#include "Nixin_Utility.h"


// Static:



//
// GetSizeFormatFromImage
//
const Nixin::Texture::DataType Nixin::Texture::GetDataTypeFromImage( const Image& image )
{
	switch( image.GetPixelType() )
	{
		case Image::ImageType::IMAGE_TYPE_BITMAP:
		{
			return DataType::UNSIGNED_BYTE;
		}
		case Image::ImageType::IMAGE_TYPE_DOUBLE:
		{
			return DataType::UNKNOWN;
		}
		case Image::ImageType::IMAGE_TYPE_FLOAT:
		{
			return DataType::FLOAT;
		}
		case Image::ImageType::IMAGE_TYPE_INT16:
		{
			return DataType::SHORT;
		}
		case Image::ImageType::IMAGE_TYPE_INT32:
		{
			return DataType::INTEGER;
		}
		case Image::ImageType::IMAGE_TYPE_UINT16:
		{
			return DataType::UNSIGNED_SHORT;
		}
		case Image::ImageType::IMAGE_TYPE_UINT32:
		{
			return DataType::UNSIGNED_INTEGER;
		}
		default:
		{
			return DataType::UNKNOWN;
		}
	}
}



// Public:



//
// Texture
// Creates a texture from a preloaded image.
//
Nixin::Texture::Texture( const Image& image )
{
	wrapMode = WrapMode::REPEAT;
	minFilterMode = MinFilterMode::MIN_LINEAR;
	magFilterMode = MagFilterMode::MAG_LINEAR;

	FromImage( image );
}



//
// Texture
// Texture from image with texture parameters.
//
Nixin::Texture::Texture( const Image& image, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax )
{
	wrapMode = initialWrapMode;
	minFilterMode = initialMinFilterMode;
	magFilterMode = initialMagFilterMode;
	mipmapped = isMipmapped;
	anisotropyMax = initialAnisotropyMax;

	FromImage( image );
}



//
// Texture
// Creates a texture from the file name given. Sets the wrap mode as repeat, the min and mag filter as linear,
// and the mipmapped as false with an anisotropy of 0.
//
Nixin::Texture::Texture( const std::string& fileName )
{
	wrapMode = WrapMode::REPEAT;
	minFilterMode = MinFilterMode::MIN_LINEAR;
	magFilterMode = MagFilterMode::MAG_LINEAR;

	LoadTextureFromFile( fileName );
}



//
// Texture
// Loads an image and creates a texture with it.
//
Nixin::Texture::Texture( const std::string& fileName, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax )
{
	wrapMode = initialWrapMode;
	minFilterMode = initialMinFilterMode;
	magFilterMode = initialMagFilterMode;
	mipmapped = isMipmapped;
	anisotropyMax = initialAnisotropyMax;

	LoadTextureFromFile( fileName );
}



//
// Texture
// Loads a texture from raw texture data.
//
Nixin::Texture::Texture( const void* const pixels, const Point& dimensions )
{
	wrapMode = WrapMode::CLAMP_TO_EDGE;
	minFilterMode = MinFilterMode::MIN_LINEAR;
	magFilterMode = MagFilterMode::MAG_LINEAR;

	FromData( pixels, dimensions );
}



//
// Texture
// Loads a texture from multiple raw data locations.
//
Nixin::Texture::Texture( const std::vector<void*>& textures, const std::vector<Rectangle>& dimensions )
{
	wrapMode = WrapMode::CLAMP_TO_EDGE;
	minFilterMode = MinFilterMode::MIN_LINEAR;
	magFilterMode = MagFilterMode::MAG_LINEAR;

	FromDataArray( textures, dimensions );
}



//
// Texture
// Creates new texture data with the specified parameters.
//
Nixin::Texture::Texture( const int textureWidth, const int textureHeight, const ToFormat toFormat, const FromFormat fromFormat, const DataType dataType, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax )
{
	CreateTexture( textureWidth, textureHeight, toFormat, fromFormat, dataType, initialWrapMode, initialMinFilterMode, initialMagFilterMode, isMipmapped, initialAnisotropyMax );
}



//
// Copy Texture
//
Nixin::Texture::Texture( const Texture& other )
{
	// Copy parameters.
	id					= other.id;
	width				= other.width;
	height				= other.height;
	format				= other.format;
	wrapMode			= other.wrapMode;
	minFilterMode		= other.minFilterMode;
	magFilterMode		= other.magFilterMode;
	mipmapped			= other.mipmapped;
	anisotropyMax		= other.anisotropyMax;

	// We only want to do this if a texture is actually loaded into other.
	if( other.id != 0 )
	{
		unsigned char* temp	= new unsigned char[width * height * 4];

		// Get other's texture data.
        gl->glBindTexture( GL_TEXTURE_2D, other.id );
        gl->glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp );

		// Gen and bind new texture id.
        gl->glGenTextures( 1, &id );
        gl->glBindTexture( GL_TEXTURE_2D, id );


		// Copy data and parameters.
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
        gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( float )wrapMode );
        gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ( float )wrapMode );
        gl->glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp );

		// Rebuild mipmaps if they are present in other.
		if( mipmapped )
		{
			//gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_BGRA, GL_UNSIGNED_BYTE, temp );
            gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyMax );
		}

		// Clean up temp.
		delete[] temp;
	}
}



//
// Move Texture
//
Nixin::Texture::Texture( Texture&& other )
{
	swap( *this, other );
}



//
// Swap
//
void Nixin::Texture::swap( Nixin::Texture& a, Nixin::Texture& b )
{
	// Enable ADL
	using				std::swap;

	// Swap all members.
	swap( a.id, b.id );
	swap( a.width, b.width );
	swap( a.height, b.height );
	swap( a.format, b.format );
	swap( a.wrapMode, b.wrapMode );
	swap( a.minFilterMode, b.minFilterMode );
	swap( a.magFilterMode, b.magFilterMode );
	swap( a.mipmapped, b.mipmapped );
	swap( a.anisotropyMax, b.anisotropyMax );
} 



//
// operator=
//
Nixin::Texture& Nixin::Texture::operator=( Texture other )
{
	swap( *this, other );

	return				*this;
}



//
// ~Texture
//
Nixin::Texture::~Texture()
{
	Dispose();
}



//
// GetID
// Gets the opengl id of this object.
//
const unsigned int Nixin::Texture::GetID() const
{
	return id;
}



//
// Dispose
//
void Nixin::Texture::Dispose()
{
	if( id != 0 )
	{
        gl->glDeleteTextures( 1, &id );
		id = 0;
	}
}



//
// LoadImage
// Loads an image with IL and creates a texture with it in
// openGL. It is then bound with this class.
//
void Nixin::Texture::LoadTextureFromFile( const std::string& fileName )
{
	// Create and load the image.
	Image					image( fileName );

	image.ConvertTo32Bits();
	
	FromImage( image );
}



//
// FromData
// Loads the texture from preloaded data.
//
void Nixin::Texture::FromData( const void* const pixels, const Point& dimensions )
{
    gl->glGenTextures( 1, &id );
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );

    gl->glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x, dimensions.y, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels );

	width = dimensions.x;
	height = dimensions.y;
}



//
// FromDataArray
//
void Nixin::Texture::FromDataArray( const std::vector<void*>& textures, const std::vector<Rectangle>& dimensions )
{
	// Get final texture width and height.
	width = 0;
	height = 0;
	for( unsigned int i = 0; i < dimensions.size(); i++ )
	{
		height = height < dimensions[i].y + dimensions[i].height ? dimensions[i].y + dimensions[i].height : height;
		width = width < dimensions[i].x + dimensions[i].width ? dimensions[i].x + dimensions[i].width : width;
	}
	
    gl->glGenTextures( 1, &id );
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );

    gl->glPixelStorei( GL_UNPACK_ALIGNMENT, 2 );
    gl->glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, NULL );

	for( int i = 0; i < textures.size(); i++ )
	{
        gl->glTexSubImage2D( GL_TEXTURE_2D, 0, dimensions[i].x, dimensions[i].y, dimensions[i].width, dimensions[i].height, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, textures[i] );
	}

}



//
// FromImage
// Loads a texture from a preloaded image.
//
void Nixin::Texture::FromImage( const Image& image )
{
	Image								image32( image.GetAs32Bits() );

    gl->glGenTextures( 1, &id );
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );

	width = image.GetWidth();
	height = image.GetHeight();
	
	if( mipmapped )
	{
		//gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_BGRA, GL_UNSIGNED_BYTE, ( GLvoid* )image32.GetPixels<float>() );
        gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyMax );
	}
	else
	{
        gl->glTexImage2D( GL_TEXTURE_2D, 0, ( int )ToFormat::RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, ( GLvoid* )image32.GetPixels<float>() );
	}
}



//
// CreateTexture
//
void Nixin::Texture::CreateTexture( const int textureWidth, const int textureHeight, const ToFormat toFormat, const FromFormat fromFormat, const DataType dataType, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax )
{
	float*					tempPixels;

	wrapMode = initialWrapMode;
	minFilterMode = initialMinFilterMode;
	magFilterMode = initialMagFilterMode;
	

    gl->glGenTextures( 1, &id );
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexImage2D( GL_TEXTURE_2D, 0, ( int )toFormat, textureWidth, textureHeight, 0, ( int )fromFormat, ( GLenum )dataType, NULL );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
    gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( float )wrapMode );
    gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ( float )wrapMode );

	if( isMipmapped )
	{
        gl->glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, tempPixels );
		//gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA8, GL_FLOAT, ( void* )tempPixels );  
        gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyMax );
	}

	width = textureWidth;
	height = textureHeight;
	mipmapped = isMipmapped;
	anisotropyMax = initialAnisotropyMax;
}



//
// SetPixel
// Changes a single pixel on the texture.
//
void Nixin::Texture::SetSinglePixel( const unsigned int x, const unsigned int y, const Colour colour )
{
	uint8_t							pixelColour[] = { ( unsigned char )colour.r, ( unsigned char )colour.g, ( unsigned char )colour.b, ( unsigned char )colour.a };							// The data that holds the colour.

    gl->glBindTexture( GL_TEXTURE_2D, id );																																	// Bind the texture.
    gl->glTexSubImage2D( GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &colour );																									// Set the pixel.
}



//
// SetAreaPixel
// Changes an area on the texture to a specified colour.
//
void Nixin::Texture::SetAreaPixel( const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h, const Colour colour )
{
	uint8_t							pixelColour[] = { ( unsigned char )colour.r, ( unsigned char )colour.g, ( unsigned char )colour.b, ( unsigned char )colour.a };							// The data that holds the colour.

    gl->glBindTexture( GL_TEXTURE_2D, id );																																	// Bind the texture.
    gl->glTexSubImage2D( GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, &colour );																									// Set the pixel area.
}



//
// GetSinglePixel
// Gets a single pixel at x and y on the bound texture. 
//
const Nixin::Colour Nixin::Texture::GetSinglePixel( const unsigned int x, const unsigned int y )
{
	GLfloat*						pixels				= nullptr;				
    Colour							pixelColour;                        // Holds our final pixel colour.

    gl->glBindTexture( GL_TEXTURE_2D, id );                              // Bind texture.
    gl->glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixels );    // Get the pixels.
	if( pixels != nullptr )
	{
        pixelColour = Colour( pixels[x + ( y * height )], pixels[x + ( y * height ) + 1], pixels[x + ( y * height ) + 2], pixels[x + ( y * height ) + 3] );			// Get the single colour from the pixels.
	}
	return pixelColour;			
}



//
// GetAllPixels
// Gets the entire pixel array of the bound texture.
//
const float* Nixin::Texture::GetAllPixels() const
{
	float*						pixels				= nullptr;


    gl->glBindTexture( GL_TEXTURE_2D, id );                              // Bind the texture.
    gl->glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixels );	// Get the pixels.


	return pixels;
}



//
// GetWrapMode
//
const Nixin::Texture::WrapMode Nixin::Texture::GetWrapMode() const
{
	return wrapMode;
}



//
// SetWrapMode
//
void Nixin::Texture::SetWrapMode( const WrapMode newWrapMode )
{
	wrapMode = newWrapMode;
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( int )wrapMode );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ( int )wrapMode );
}



//
// GetMinFilterMode
//
const Nixin::Texture::MinFilterMode Nixin::Texture::GetMinFilterMode() const
{
	return minFilterMode;
}



//
// SetMinFilterMode
//
void Nixin::Texture::SetMinFilterMode( const MinFilterMode newMinFilterMode )
{
	minFilterMode = newMinFilterMode;
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ( int )minFilterMode );
}



//
// GetMagFilterMode
//
const Nixin::Texture::MagFilterMode Nixin::Texture::GetMagFilterMode() const
{
	return magFilterMode;
}



//
// SetMagFilterMode
//
void Nixin::Texture::SetMagFilterMode( const MagFilterMode newMagFilterMode )
{
	magFilterMode = newMagFilterMode;
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ( int )magFilterMode );
}



//
// GetAnisotropyMax
//
const float Nixin::Texture::GetAnisotropyMax() const
{
	return anisotropyMax;
}



//
// SetAnisotropyMax
//
void Nixin::Texture::SetAnisotropyMax( const float newAnisotropyMax )
{
	anisotropyMax = newAnisotropyMax;
    gl->glBindTexture( GL_TEXTURE_2D, id );
    gl->glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyMax );
}



//
// GetIsMipmapped
//
const bool Nixin::Texture::GetIsMipmapped() const
{
	return mipmapped;
}



//
// GetWidth
//
const int Nixin::Texture::GetWidth() const
{
	return width;
}



//
// GetHeight
//
const int Nixin::Texture::GetHeight() const
{
	return height;
}



//
// Middle
// Gets the middle of the texture in pixels.
//
Nixin::Point Nixin::Texture::Middle() const
{
	return Point( width / 2, height / 2 );
}




// Private:





