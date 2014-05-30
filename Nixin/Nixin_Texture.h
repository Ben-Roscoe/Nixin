#ifndef _NIXIN_TEXTURE_H_
#define _NIXIN_TEXTURE_H_


#include "Nixin_Colour.h"
#include "Nixin_Point.h"
#include "Nixin_Image.h"
#include "Nixin_Types.h"

#include <string>
#include <vector>
#include <memory>
#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{

	class Texture
	{



	public: // non-static:



		//
		// SizeFormat
		//
		enum class ToFormat
		{
			DEPTH_COMPONENT16 = 0x81A5,
			DEPTH_COMPONENT24 = 0x81A6,
			DEPTH_COMPONENT32 = 0x81A7,
			COLOUR_ATTACHMENT0 = 0x8CE0,

			RED = 0x1903,
			RG = 0x8227,
			RGB = 0x1907,
			RGBA = 0x1908,
			R8 = 0x8229,
			R8_SNORM = 0x8F94,
			R16 = 0x822A,
			R16_SNORM = 0x8F98,
			RG8 = 0x822B,
			RG8_SNORM = 0x8F95,
			RG16 = 0x822C,
			RG16_SNORM = 0x8F99,
			R3_G3_B2 = 0x2A10,
			RGB4 = 0x804F,
			RGB5 = 0x8050,
			RGB8 = 0x8051,
			RGB8_SNORM = 0x8F96,
			RGB10 = 0x8052,
			RGB12 = 0x8053,
			RGB16_SNORM = 0x8F9A,
			RGBA2 = 0x8055,
			RGBA4 = 0x8056,
			RGB5_A1 = 0x8057,
			RGBA8 = 0x8058,
			RGBA8_SNORM = 0x8F97,
			RGB10_A2 = 0x8059,
			RGB10_A2UI = 0x906F,
			RGBA12 = 0x805A,
			RGBA16 = 0x805B,
			SRGB8 = 0x8C41,
			SRGB8_ALPHA8 = 0x8C43,
			R16F = 0x822D,
			RG16F = 0x822F,
			RGB16F = 0x881B,
			RGBA16F = 0x881A,
			R32F = 0x822E,
			RG32F = 0x8230,
			RGB32F = 0x8815,
			RGBA32F = 0x8814,
			R11F_G11F_B10F = 0x8C3A,
			RGB9_E5 = 0x8C3D,
			R8I = 0x8231,
			R8UI = 0x8232,
			R16I = 0x8233,
			R16UI = 0x8234,
			R32I = 0x8235,
			R32UI = 0x8236,
			RG8I = 0x8237,
			RG8UI = 0x8238,
			RG16I = 0x8239,
			RG16UI = 0x823A,
			RG32I = 0x823B,
			RG32UI = 0x823C,
			RGB8I = 0x8D8F,
			RGB8UI = 0x8D7D,
			RGB16I = 0x8D89,
			RGB16UI = 0x8D77,
			RGB32I = 0x8D83,
			RGB32UI = 0x8D71,
			RGBA8I = 0x8D8E,
			RGBA8UI = 0x8D7C,
			RGBA16I = 0x8D88,
			RGBA16UI = 0x8D76,
			RGBA32I = 0x8D82,
			RGBA32UI = 0x8D70,

			COMPRESSED_RED = 0x8225,
			COMPRESSED_RG = 0x8226,
			COMPRESSED_RGB = 0x84ED,
			COMPRESSED_RGBA = 0x84EE,
			COMPRESSED_SRGB = 0x8C48,
			COMPRESSED_SRGB_ALPHA = 0x8C49,
			COMPRSSED_RED_RGTC1 = 0x8DBB,
			COMPRESSED_SIGNED_RED_RGTC1 = 0x8DBC,
			COMPRESSED_RG_RGTC2 = 0x8DBD,
			COMPRESSED_SIGNED_RG_RGTC2 = 0x8DBE,
			COMPRESSED_RGBA_BPTC_UNORM = 0x8E8C,
			COMPRESSED_SRGB_ALPHA_BPTC_UNORM = 0x8E8D,
			COMPRESSED_RGB_BPTC_SIGNED_FLOAT = 0x8E8E,
			COMPRESSED_RGB_UNSIGNED_FLOAT = 0x8E8F,

			UNSUPPORTED = 0x0000,
		};
	
	
	
		//
		// Format
		//
		enum class FromFormat
		{
			DEPTH_COMPONENT = 0x1902,
			DEPTH_STENCIL = 0x84f9,
			COLOUR_ATTACHMENT = 0x1907,
			RED = 0x1903,
			RG = 0x8227,
			RGB = 0x1907,
			RGBA = 0x1908,
		};
	

	
		//
		// DataType
		//
		enum class DataType
		{
			UNKNOWN = 0x0000,
			UNSIGNED_BYTE = 0x1401,
			BYTE = 0x1400,
			UNSIGNED_SHORT = 0x1403,
			SHORT = 0x1402,
			UNSIGNED_INTEGER = 0x1405,
			INTEGER = 0x1404,
			FLOAT = 0x1406,
			UNSIGNED_BYTE_3_3_2 = 0x8032,
			UNSIGNED_BYTE_2_3_3 = 0x8362,
			UNSIGNED_SHORT_5_6_5 = 0x8363,
			UNSIGNED_SHORT_4_4_4_4 = 0x8033,
			UNSIGNED_SHORT_5_5_5_1 = 0x8034,
			UNSIGNED_SHORT_1_5_5_5 = 0x8366,
			UNSIGNED_INTEGER_8_8_8_8 = 0x8035,
			UNSIGNED_INTEGER_10_10_10_2 = 0x8036,
			UNSIGNED_INTEGER_2_10_10_10 = 0x8368,
		};
	
	
		//
		// TextureType
		//
		enum class Type
		{
			TEXTURE_2D = 0x0DE1,
			CUBE_TEXTURE = 0x8513,
		};
	
	
	
		//
		// TextureWrapMode
		//
		enum class WrapMode
		{
			REPEAT = 0x2901,
			CLAMP  = 0x2900,
			CLAMP_TO_EDGE = 0x812F,
		};
	
	
	
		//
		// TextureMagFilterMode
		//
		enum class MagFilterMode
		{
			MAG_LINEAR = 0x2600,
			MAG_NEAREST = 0x2601,
		};
	
	
	
		//
		// TextureMinFilterMode
		//
		enum class MinFilterMode
		{
			MIN_LINEAR = 0x2600,
			MIN_NEAREST = 0x2601,
			LINEAR_MIPMAP_LINEAR = 0x2703,
			LINEAR_MIPMAP_NEAREST = 0x2701,
			NEAREST_MIPMAP_LINEAR = 0x2702,
			NEAREST_MIPMAP_NEAREST = 0x2700,
		};



		static const Texture::DataType			GetDataTypeFromImage( const Image& image );



		
		
		// Constructors and destructos.
		Texture( const Image& image );
		Texture( const Image& image, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax );
		Texture( const std::string& fileName );
		Texture( const std::string& fileName, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax );
		Texture( const void* const pixels, const Point& dimensions );
		Texture( const std::vector<void*>& textures, const std::vector<Rectangle>& dimensions );
		Texture( const int textureWidth, const int textureHeight, const ToFormat toFormat, const FromFormat fromFormat, const DataType dataType, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax );

		Texture( const Texture& other );
		Texture( Texture&& other );
		Texture& operator=( Texture other );
		~Texture();

		void swap( Texture& a, Texture& b );

		// Explicit allocation, deallocation and copying.
		const unsigned int							GetID() const;
		void										Copy( const Texture& other );
		void										Dispose();

		void										LoadTextureFromFile( const std::string& fileName );
		void										FromData( const void* const pixels, const Point& dimensions );
		void										FromDataArray( const std::vector<void*>& textures, const std::vector<Rectangle>& dimensions );
		void										FromImage( const Image& image );
		void										CreateTexture( const int textureWidth, const int textureHeight, const ToFormat toFormat, const FromFormat fromFormat, const DataType dataType, const WrapMode initialWrapMode, const MinFilterMode initialMinFilterMode, const MagFilterMode initialMagFilterMode, const bool isMipmapped, const float initialAnisotropyMax );

		// Utilities.
        const Colour								GetSinglePixel( const unsigned int x, const unsigned int y );
		const float*								GetAllPixels() const;
		void										SetSinglePixel( const int unsigned x, const unsigned int y, const Colour colour );
		void										SetAreaPixel( const unsigned int x, const unsigned int y, const unsigned int frameBufferWidth, const unsigned int frameBufferHeight, const Colour colour );

		// Parameters.
		const int									GetWidth() const;
		const int									GetHeight() const;
		const int									GetFormat() const;

		const Texture::WrapMode						GetWrapMode() const;
		void										SetWrapMode( const WrapMode newWrapMode );
		const Texture::MinFilterMode				GetMinFilterMode() const;
		void										SetMinFilterMode( const MinFilterMode newMinFilterMode );
		const Texture::MagFilterMode				GetMagFilterMode() const;
		void										SetMagFilterMode( const MagFilterMode newMagFilterMode );
		const float									GetAnisotropyMax() const;
		void										SetAnisotropyMax( const float newAnisotropyMax );
		const bool									GetIsMipmapped() const;
	
		Point										Middle() const;



	private:



        OpenGLFunctions*                            gl                      = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
		unsigned int								id						= 0;

		int											width					= 0;
		int											height					= 0;
		int											format					= 0;

		WrapMode									wrapMode				= WrapMode::REPEAT;
		MinFilterMode								minFilterMode			= MinFilterMode::MIN_LINEAR;
		MagFilterMode								magFilterMode			= MagFilterMode::MAG_LINEAR;
		bool										mipmapped				= false;
		float										anisotropyMax			= 0.0f;



	};

}



#endif

