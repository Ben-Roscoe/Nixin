#ifndef _NIXIN_SOUNDFILE_H_
#define _NIXIN_SOUNDFILE_H_



#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdint.h>



typedef unsigned int	ALuint;
typedef int				ALenum;



namespace Nixin
{
	class SoundFile
	{



	public:



		enum class Type
		{
			NONE,
			WAVE,
			OGG,
		};

		SoundFile();
		SoundFile( const SoundFile& other );
		SoundFile( SoundFile&& other );
		SoundFile( const std::string& fileName );
		~SoundFile();

		SoundFile&				operator=( SoundFile Other );


		const unsigned int		GetFormatID() const;
		const unsigned int		GetFrequency() const;
		const unsigned int		GetDataByteSize() const;
		const Type				GetType() const;
		const void*				GetRawData() const;



	private:



		class WaveFile
		{



		public:



			// Describes what type of compression is used on the data chunck.
			enum class CompressionCode
			{
				UNKOWN				= 0x0000,
				PCM_UNCOMPRESSED	= 0x0001,
				MICROSOFT_ADPCM		= 0x0002,
				ITU_G711_A_LAW		= 0x0006,
				ITU_G711_AU_LAW		= 0x0007,
				IMA_ADPCM			= 0x0011,
				ITU_G723_ADPCM		= 0x0016,
				GSM610				= 0x0031,
				ITU_G721_ADPCM		= 0x0040,
				MPEG				= 0x0050,
				EXPERIMENTAL		= 0xffff,
			};


			// Describes a RIFF header.
			struct Header
			{
				uint32_t					id;
				uint32_t					size;
				uint32_t					format;
			};


			// Describes a chunk.
			struct Chunk
			{
				uint32_t					id;
				uint32_t					size;
				std::vector<uint8_t>		data;
			};



			// Describes a format chunk.
			struct FormatChunk
			{
				uint16_t			compressionCode;
				uint16_t			channelCount;
				uint32_t			sampleRate;
				uint32_t			averageBytesPerSecond;
				uint16_t			blockAlign;
				uint16_t			bitsPerSample;
				uint16_t			extraFormatSize;
			};


			// Each file will have 1 header and an unspecified amount of misc chunks.
			Header							header;
			std::vector<Chunk>					chunks;


			// Returns a chunk with the desired id.
			const Chunk*					GetChunk( const unsigned int id ) const
			{
				for( auto& chunk : chunks )
				{
					if( chunk.id == id )
					{
						return &chunk;
					}
				}
				return nullptr;
			}
		};



		class OGGFile
		{



		public:

			static const unsigned  short int	frequency = 44100;

			struct Page
			{
				unsigned int		syncCode;
				unsigned char		version;
				unsigned char		headerType;
				int64_t		     	granulePosition;
				unsigned int		bitstreamSerial;
				unsigned int		pageSequence;
				unsigned int		checksum;
				unsigned char		pageSegment;

				unsigned int		segmentTablePosition;
			};

			std::vector<Page>		pages;
			unsigned char*			data;


			OGGFile()
			{
				data = nullptr;
			}

			void					Dispose()
			{
				if( pages.size() > 0 )
				{
					delete[]		data;
				}
			}


			void					Clone( OGGFile& other, const unsigned int dataSize )
			{
				other.pages			= pages;
				other.data			= data;


				if( data != nullptr )
				{
					//other.data		= new unsigned char[dataSize];
					//std::copy( std::begin( data ), std::end( data ), std::begin( other.data ) );
				}
			}
		};



		Type					type;
		void*					fileContents;
		ALenum					format;
		unsigned int			frequency;
		unsigned int			dataByteSize;



		void					LoadWaveFile( const std::string& fileName );
		void					LoadOGGFile( const std::string& fileName );
		void					GenerateFormatID( const unsigned char channels, const unsigned int bitrate );


	};
}



#endif