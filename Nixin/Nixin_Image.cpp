#include "Nixin_Image.h"
#include "Nixin_Debug.h"

#include <FreeImage.h>



// Public:




//
// Image
// Loads an image from a file.
//
Nixin::Image::Image( const std::string& fileName )
{
	LoadFromFile( fileName );
}



//
// Image
// Loads an image from a data lump.
//
Nixin::Image::Image( const void* const data, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int imagePitch, const unsigned int bytesPerPixel )
{
    LoadFromData( data, imageWidth, imageHeight, imagePitch, bytesPerPixel );
}



//
// Image
// Loads a sub image from the given image.
//
Nixin::Image::Image( const Image& otherImage, const Rectangle& bounds )
{
	if( bounds.width < 0 || bounds.height < 0 )
	{
		Debug::FatalError( "Sub bounds position was not valid." );
	}
	else if( ( bounds.width + bounds.x ) > otherImage.GetWidth() || ( bounds.height + bounds.y ) > otherImage.GetHeight() )
	{
		Debug::FatalError( "Sub bounds were too large for the source image." );
	}
	else
	{
		LoadSubImage( otherImage, bounds );
	}
}



//
// Copy Image
//
Nixin::Image::Image( const Image& other )
{
	image				= other.image;
	width				= other.width;
	height				= other.height;
	pitch				= other.pitch;
	bitsPerPixel		= other.bitsPerPixel;
	pixelType			= other.pixelType;
	redMask				= other.redMask;
	greenMask			= other.greenMask;
	blueMask			= other.blueMask;
	transparencyCount	= other.transparencyCount;

	// Deep copy the image.
	image = FreeImage_Clone( other.image );
}



//
// Move Image
//
Nixin::Image::Image( Image&& other )
{
	swap( *this, other );
}



//
// swap
//
void Nixin::Image::swap( Image& a, Image& b )
{
	// Use ADL
	using std::swap;


	// Swap all members.
	swap( a.image, b.image );
	swap( a.width, b.width );
	swap( a.height, b.height );
	swap( a.pitch, b.pitch );
	swap( a.bitsPerPixel, b.bitsPerPixel );
	swap( a.pixelType, b.pixelType );
	swap( a.redMask, b.redMask );
	swap( a.greenMask, b.greenMask );
	swap( a.blueMask, b.blueMask );
	swap( a.transparencyCount, b.transparencyCount );
}



//
// operator=
//
Nixin::Image& Nixin::Image::operator=( Image other )
{
	swap( *this, other );

	return			    *this;
}



//
// ~Image
//
Nixin::Image::~Image()
{
	if( image != nullptr )
	{
		FreeImage_Unload( image );
	}
}



//
// ConvertToType
// Converts to the new specified type.
//
void Nixin::Image::ConvertToType( ImageType type )
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertToType( image, ( FREE_IMAGE_TYPE )type );
	pixelType = ( ImageType )FreeImage_GetImageType( image );
}



//
// ConvertTo4Bits
//
void Nixin::Image::ConvertTo4Bits()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo4Bits( image );
	GetImageParameters();
}



//
// ConvertTo8Bits
//
void Nixin::Image::ConvertTo8Bits()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo8Bits( image );
	GetImageParameters();
}



//
// ConvertTo16Bits555
//
void Nixin::Image::ConvertTo16Bits555()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo16Bits555( image );
	GetImageParameters();
}



//
// ConvertTo16Bits565
//
void Nixin::Image::ConvertTo16Bits565()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo16Bits565( image );
	GetImageParameters();
}



//
// ConvertTo24Bits
//
void Nixin::Image::ConvertTo24Bits()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo24Bits( image );
	GetImageParameters();
}



//
// ConvertTo32Bits
//
void Nixin::Image::ConvertTo32Bits()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertTo32Bits( image );
	GetImageParameters();
}



//
// ConvertToGreyscale
//
void Nixin::Image::ConvertToGreyscale()
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to convert." );
	}
	image = FreeImage_ConvertToGreyscale( image );
	GetImageParameters();
}



//
// GetAsNewType
// Returns a new image that is this image with a converted type.
//
Nixin::Image Nixin::Image::GetAsNewType( ImageType type ) const
{
	Image		result;

	result.image = FreeImage_ConvertToType( image, ( FREE_IMAGE_TYPE )type );
	result.GetImageParameters();

	return result;
}



//
// GetAs4Bits
// Returns a new image  that is a 4 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs4Bits() const
{
	Image		result;

	result.image = FreeImage_ConvertTo4Bits( image );
	result.GetImageParameters();

	return result;
}



//
// GetAs8Bits
// Returns a new image that is a 8 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs8Bits() const
{
	Image		result;

	result.image = FreeImage_ConvertTo8Bits( image );
	result.GetImageParameters();

	return result;
}



//
// GetAs16Bits555
// Returns a new image that is a 16, 555 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs16Bits555() const
{
	Image		result;

	result.image = FreeImage_ConvertTo16Bits555( image );
	result.GetImageParameters();

	return result;
}



//
// GetAs16Bits565
// Returns a new image that is a 16, 565 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs16Bits565() const
{
	Image		result;

	result.image = FreeImage_ConvertTo16Bits565( image );
	result.GetImageParameters();

	return result;
}



//
// GetAs24Bits
// Returns a new image that is a 24 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs24Bits() const
{
	Image		result;

	result.image = FreeImage_ConvertTo24Bits( image );
	result.GetImageParameters();

	return result;
}



//
// GetAs32Bits
// Returns a new image that is a 32 bit version of this image.
//
Nixin::Image Nixin::Image::GetAs32Bits() const
{
	Image		result;

	result.image = FreeImage_ConvertTo32Bits( image );
	result.GetImageParameters();

	return result;
}



//
// GetAsGreyscale
// Returns a new image that is a greyscale version of this image.
//
Nixin::Image Nixin::Image::GetAsGreyscale() const
{
	Image		result;

	result.image = FreeImage_ConvertToGreyscale( image );
	result.GetImageParameters();

	return result;
}



//
// Save
//
void Nixin::Image::Save( const Image::FileFormat& fileFormat, const std::string& fileName ) const
{
	if( image == nullptr )
	{
		Debug::FatalError( "No image data to save." );
	}
	if( !FreeImage_Save( ( FREE_IMAGE_FORMAT )fileFormat, image, fileName.c_str() ) )
	{
		Debug::FatalError( "Image failed to save." );
	}
}



//
// GetWidth
//
const unsigned int Nixin::Image::GetWidth() const
{
	return width;
}



//
// GetHeight
//
const unsigned int Nixin::Image::GetHeight() const
{
	return height;
}



//
// GetPitch
//
const unsigned int Nixin::Image::GetPitch() const
{
	return pitch;
}



//
// GetBitsPerPixel
//
const unsigned int Nixin::Image::GetBitsPerPixel() const
{
	return bitsPerPixel;
}



//
// GetPixelType
//
const Nixin::Image::ImageType Nixin::Image::GetPixelType() const
{
	return pixelType;
}



//
// GetRedMask
//
const unsigned int Nixin::Image::GetRedMask() const
{
	return redMask;
}



//
// GetGreenMask
//
const unsigned int Nixin::Image::GetGreenMask() const
{
	return greenMask;
}



//
// GetBlueMask
//
const unsigned int Nixin::Image::GetBlueMask() const
{
	return blueMask;
}



//
// GetBlueMask
//
const unsigned int Nixin::Image::GetTransparencyCount() const
{
	return transparencyCount;
}




// Private:



//
// Image
//
Nixin::Image::Image()
{
}



//
// LoadFromFile
// Loads this image from a file. Also fills in all parameters.
//
void Nixin::Image::LoadFromFile( const std::string& fileName )
{
	image = FreeImage_Load( FreeImage_GetFileType( fileName.c_str() ), fileName.c_str() );
	FreeImage_FlipVertical( image );
	
	if( image == nullptr )
	{
		Debug::FatalError( "The specified image file could not be loaded." );
	}
	GetImageParameters();
}



//
// LoadFromData
// Loads an image of width and height from an array of floats.
//
void Nixin::Image::LoadFromData( const void* const data, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int imagePitch, const unsigned int bytesPerPixel )
{
	image = FreeImage_ConvertFromRawBits( ( BYTE* )data, width, height, 0, bytesPerPixel * 8, 0, 0, 0 );
	FreeImage_FlipVertical( image );
	if( image == nullptr )
	{
		Debug::FatalError( "Failed to load image from memory lump." );
	}
	GetImageParameters();
}



//
// LoadSubImage
//
void Nixin::Image::LoadSubImage( const Image& otherImage, const Rectangle& bounds )
{
	//std::unique_ptr<float>					subData			=		std::unique_ptr<float>( new float[( int )bounds.width * ( int )bounds.height] );
	//
	//// Read sub data.
	//for( int i = 0; i < bounds.height; i++ )
	//{
	//	std::memcpy( ( void* )( subData.get() + ( i * ( int )bounds.width ) * sizeof( float ) ), ( void* )( image.GetPixels() +  ( i * image.GetWidth() + ( int )bounds.y * image.GetWidth() ) * sizeof( float ) ), ( int )bounds.width * sizeof( float ) );
	//}
	//
	//// Load the lump using IL.
	//if( !ilLoadDataL( ( void* )image.GetPixels(), image.GetWidth() * image.GetHeight(), image.GetWidth(), image.GetHeight(), 1, sizeof( float ) ) )
	//{
	//	throw std::exception( "Failed to load sub image." );
	//}
	//FreeImage_ConvertToFloat( image.get() );
	//
	//// Load the image parameters.
	//GetImageParameters();
}



//
// GetImageParameters
// Gets the image parameters from FI.
//
void Nixin::Image::GetImageParameters()
{
	if( image !=nullptr )
	{
		width = FreeImage_GetWidth( image );
		height = FreeImage_GetHeight( image );
		pitch = FreeImage_GetPitch( image );
		bitsPerPixel = FreeImage_GetBPP( image );
		pixelType = ( ImageType )FreeImage_GetImageType( image );

		redMask = FreeImage_GetRedMask( image );
		greenMask = FreeImage_GetGreenMask( image );
		blueMask = FreeImage_GetBlueMask( image );
		transparencyCount = FreeImage_GetTransparencyCount( image );
	}
	else
	{
		width = 0;
		height = 0;
		pitch = 0;
		bitsPerPixel = 0;
		pixelType = ImageType::IMAGE_TYPE_UNKNOWN;

		redMask = 0;
		greenMask = 0;
		blueMask = 0;
		transparencyCount = 0;
	}
}




//
// InternalGetPixels
// Wraps FreeImage_GetBits, because the actual "GetPixels" method appears in the .h.
//
const void* Nixin::Image::InternalGetPixels() const
{
	return ( void* )FreeImage_GetBits( image );
}

