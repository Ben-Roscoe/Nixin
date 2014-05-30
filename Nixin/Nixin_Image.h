#ifndef _NIXIN_IMAGE_H_
#define _NIXIN_IMAGE_H_



#include <string>

#include "Nixin_Point.h"
#include "Nixin_Colour.h"
#include "Nixin_Rectangle.h"


struct FIBITMAP;

namespace Nixin
{
	class Image
	{



	public:




		//
		// ImageType
		// Defines an image type for converting to or from.
		//
		enum class ImageType
		{
			IMAGE_TYPE_UNKNOWN	= 0,
			IMAGE_TYPE_BITMAP	= 1,
			IMAGE_TYPE_UINT16	= 2,
			IMAGE_TYPE_INT16	= 3,
			IMAGE_TYPE_UINT32	= 4,
			IMAGE_TYPE_INT32	= 5,
			IMAGE_TYPE_FLOAT	= 6,
			IMAGE_TYPE_DOUBLE	= 7,
			IMAGE_TYPE_COMPLEX	= 8,
			IMAGE_TYPE_RGB16	= 9,
			IMAGE_TYPE_RGBA16	= 10,
			IMAGE_TYPE_RGBF		= 11,
			IMAGE_TYPE_RGBAF	= 12,
		};



		//
		// FileFormat
		//
		enum class FileFormat
		{
			UNKNOWN				= -1,
			BMP					=  0,
			ICO					=  1,
			JPEG				=  2,
			JNG					=  3,
			KOALA				=  4,
			LBM					=  5,
			IFF					=  LBM,
			MNG					=  6,
			PBM					=  7,
			PBMRAW				=  8,
			PCD					=  9,
			PCX					=  10,
			PGM					=  11,
			PGMRAW				=  12,
			PNG					=  13,
			PPM					=  14,
			PPMRAW				=  15,
			RAS					=  16,
			TARGA				=  17,
			TIFF				=  18,
			WBMP				=  19,
			PSD					=  20,
			CUT					=  21,
			XBM					=  22,
			XPM					=  23,
			DDS					=  24,
			GIF					=  25,
			HDR					=  26,
			FAXG3				=  27,
			SGI					=  28,
			EXR					=  29,
			J2K					=  30,
			JP2					=  31,
			PFM					=  32,
			PICT				=  33,
			RAW					=  34,
		};

		

		// Construct the object with image data, a file path, or a sub-image of another image.
		explicit Image( const std::string& fileName );
		Image( const void* const data, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int imagePitch, const unsigned int bytesPerPixel );
		Image( const Image& otherImage, const Rectangle& bounds );

		// Copy the image, move the image and destruct the image.
		Image( const Image& other );
		Image( Image&& other );
		Image& operator=( Image other );
		void swap( Image& a, Image& b );
		~Image();


		// Convert this image to different formats.
		void								ConvertToType( ImageType type );
		void								ConvertTo4Bits();
		void								ConvertTo8Bits();
		void								ConvertTo16Bits555();
		void								ConvertTo16Bits565();
		void								ConvertTo24Bits();
		void								ConvertTo32Bits();
		void								ConvertToGreyscale();

		// Return a new copy of this image in different formats.
		Image								GetAsNewType( ImageType type ) const;
		Image								GetAs4Bits() const;
		Image								GetAs8Bits() const;
		Image								GetAs16Bits555() const;
		Image								GetAs16Bits565() const;
		Image								GetAs24Bits() const;
		Image								GetAs32Bits() const;
		Image								GetAsGreyscale() const;

		// Save to hard drive.
		void								Save( const Image::FileFormat& fileFormat, const std::string& fileName ) const;

		// Get the pixel array.
		template<typename T>
		const T*							GetPixels() const
		{
			return ( T* )InternalGetPixels();
		}

		// Get a single pixel.
		template<typename T>
		const T								GetPixel( const unsigned int x, const unsigned int y ) const
		{
			return GetPixels<T>()[x + ( y * width )];
		}

		// Set a single pixel.
		template<typename T>
		void								SetPixel( const unsigned int x, const unsigned int y, const T& value )
		{

		}
	

		// Get parameters.
		const unsigned int					GetWidth() const;
		const unsigned int					GetHeight() const;
		const unsigned int					GetPitch() const;
		const unsigned int					GetBitsPerPixel() const;
		const ImageType						GetPixelType() const;

		const unsigned int					GetRedMask() const;
		const unsigned int					GetGreenMask() const;
		const unsigned int					GetBlueMask() const;
		const unsigned int					GetTransparencyCount() const;



	private:



		FIBITMAP*							image						= nullptr;

		unsigned int						width						= 0;
		unsigned int						height						= 0;
		unsigned int						pitch						= 0;	
		unsigned int						bitsPerPixel				= 0;
		ImageType							pixelType					= ImageType::IMAGE_TYPE_UNKNOWN;

		unsigned int						redMask						= 0;
		unsigned int						greenMask					= 0;
		unsigned int						blueMask					= 0;
		unsigned int						transparencyCount			= 0;


		// This helps us copy the image as different types in the "GetAs" methods. We need the default constructor
		// only in this class, just to get around the way Free Image works.
		Image();

		// Helper functions.
		void								LoadFromFile( const std::string& fileName );
		void								LoadFromData( const void* const data, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int imagePitch, const unsigned int bytesPerPixel );
		void								LoadSubImage( const Image& otherImage, const Rectangle& bounds );
		void								GetImageParameters();
		const void*							InternalGetPixels() const;					// Just to help keep FreeImage out of the .h.


	};

}


#endif

