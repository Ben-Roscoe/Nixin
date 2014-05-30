#include "Nixin_SoundFile.h"
#include "Nixin_Debug_Output.h"
#include "Nixin_Memory_Utility.h"

#include <fstream>
#include <stdlib.h>
#include <AL/al.h>



// Public:



//
// SoundFile
//
Nixin::SoundFile::SoundFile()
{
	type = Type::NONE;
	frequency = 0;
	format = AL_FORMAT_MONO8;
}



//
// SoundFile
//
Nixin::SoundFile::SoundFile( const SoundFile& other )
{
	type					= other.type;
	format					= other.format;
	frequency				= other.frequency;
	dataByteSize			= other.dataByteSize;

	// Deep copy the file contents.
	if( other.fileContents != nullptr )
	{
		switch( type )
		{
			case Type::WAVE:
			{
				fileContents = new WaveFile();
				//std::copy( reinterpret_cast<WaveFile*>( other.fileContents ), reinterpret_cast<WaveFile*>( other.fileContents ) + 1, fileContents );
				//fileContents = other.fileContents;
				break;
			}
			case Type::OGG:
			{
				fileContents = new OGGFile();
				//std::copy( reinterpret_cast<OGGFile*>( other.fileContents ), reinterpret_cast<OGGFile*>( other.fileContents ) + 1, fileContents );
				break;
			}
		}
	}
}



//
// SoundFile
//
Nixin::SoundFile::SoundFile( SoundFile&& other )
{
	type					= other.type;
	format					= other.format;
	frequency				= other.frequency;
	dataByteSize			= other.dataByteSize;

	fileContents			= std::move( other.fileContents );
}



//
// operator =
//
Nixin::SoundFile& Nixin::SoundFile::operator=( SoundFile other )
{
	type					= other.type;
	format					= other.format;
	frequency				= other.frequency;
	dataByteSize			= other.dataByteSize;

	fileContents			= std::move( other.fileContents );

	return					*this;
}



//
// SoundFile
//
Nixin::SoundFile::SoundFile( const std::string& fileName )
{
	std::string				extension = fileName.substr( fileName.size() - 4 );

	type = Type::NONE;
	frequency = 0;
	format = AL_FORMAT_MONO8;

	if( extension == ".wav" )
	{
		LoadWaveFile( fileName );
	}
	else if( extension == ".ogg" )
	{
		LoadOGGFile( fileName );
	}
	else
	{
		Nixin::Debug::FatalError( "%s is not a recognised sound file.", fileName.c_str() );
	}
}



//
// ~SoundFile
//
Nixin::SoundFile::~SoundFile()
{
}



//
// GetFormatID
//
const unsigned int Nixin::SoundFile::GetFormatID() const
{
	return ( unsigned int )format;
}



//
// GetFrequency
//
const unsigned int Nixin::SoundFile::GetFrequency() const
{
	return frequency;
}



//
// GetDataByteSize
//
const unsigned int Nixin::SoundFile::GetDataByteSize() const
{
	return dataByteSize;
}



//
// GetType
//
const Nixin::SoundFile::Type Nixin::SoundFile::GetType() const
{
	return type;
}



//
// GetRawData
//
const void* Nixin::SoundFile::GetRawData() const
{
	if( fileContents == nullptr )
	{
		Nixin::Debug::FatalError( "Attempted to get data of uninitialised sound file." );
	}
	switch( type )
	{
		case Type::WAVE:
		{
			const WaveFile::Chunk*			chunk = reinterpret_cast<WaveFile*>( fileContents )->GetChunk( 'data' );
			if( chunk == nullptr )
			{
				Nixin::Debug::FatalError( "Attempted to get data of bad, or empty wave file. No data chunk found." );
			}
			return chunk->data.data();
			break;
		}
		case Type::OGG:
		{
			unsigned char*			 data = reinterpret_cast<OGGFile*>( fileContents )->data;
			if( data == nullptr )
			{
				Nixin::Debug::FatalError( "Attempted to get data of bad or empty ogg file." );
			}
			return data;
			break;
		}
		default:
		{
			return nullptr;
		}
	}
}




// Private:




//
// GenerateFormatID
// Helper method that works out the al format enum from a channel count and a bitrate.
//
void Nixin::SoundFile::GenerateFormatID( const unsigned char channels, const unsigned int bitrate )
{	
	if( channels == 2 )
	{
		format = bitrate == 16 ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
	}
	else
	{
		format = bitrate == 16 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
	}
}


//
// LoadWaveFile
// Loads a wave file from a file location and copies it to memory.
//
void Nixin::SoundFile::LoadWaveFile( const std::string& fileName )
{
	std::ifstream					file;

	// Try to open to file in binary.
	file.open( fileName, std::fstream::in | std::ios::binary );
	if( file.fail() )
	{
		// Throw if something went wrong.
		Nixin::Debug::FatalError( "Could not open %s for reading.", fileName.c_str() );
	}

	// Allocate the new sound file.
	fileContents = new WaveFile();

	WaveFile& waveFile = *reinterpret_cast<WaveFile*>( fileContents );

	// Read the header.
	file.read( reinterpret_cast<char*>( &waveFile.header.id ), sizeof( waveFile.header.id ) );
	file.read( reinterpret_cast<char*>( &waveFile.header.size ), sizeof( waveFile.header.size ) );
	file.read( reinterpret_cast<char*>( &waveFile.header.format ), sizeof( waveFile.header.format ) );

	// Swap IDs as they are big endian.
	MemoryUtility::SwapBytes( waveFile.header.id );
	MemoryUtility::SwapBytes( waveFile.header.format );

	if( waveFile.header.id != 'RIFF' || waveFile.header.format != 'WAVE' || waveFile.header.size < 4 )
	{
		// If the id, format or size is not right, throw an exception.
		Nixin::Debug::FatalError( "File is either empty or not in wave format" );
	}

	// We're going to start reading chunks now.
	while( file.tellg() < waveFile.header.size + 8 )
	{
		unsigned int alignedSize;

		// Create the chunk.
		waveFile.chunks.emplace_back();

		// Read the chunk header.
		file.read( reinterpret_cast<char*>( &waveFile.chunks.back().id ), sizeof( waveFile.chunks.back().id ) );
		file.read( reinterpret_cast<char*>( &waveFile.chunks.back().size ), sizeof( waveFile.chunks.back().size ) );
		MemoryUtility::SwapBytes( waveFile.chunks.back().id );

		alignedSize = waveFile.chunks.back().size;
		waveFile.chunks.back().size = MemoryUtility::GetAlignedSize( alignedSize, 2 );

		waveFile.chunks.back().data.resize( waveFile.chunks.back().size );
		file.read( reinterpret_cast<char*>( waveFile.chunks.back().data.data() ), waveFile.chunks.back().size );

		file.ignore( alignedSize - waveFile.chunks.back().size );
	}

	// Close the file.
	file.close();
	

	// Here we get the format chunk by it's id. A format chunk always has the id "fmt " in a wave file. We reinterpret data as
	// a format chunk, because that is where the format information begins. This requires the FormatChunk struct to be in the exact
	// same order as the file's format chunk. We also check if this file actually has a format chunk before continuing.
	const WaveFile::Chunk*					 chunk = waveFile.GetChunk( 'fmt ' );
	if( chunk == nullptr )
	{
		Nixin::Debug::FatalError( "Wave file from %s loaded correctly, but no format chunk was found. Bad wave file.", fileName.c_str() );
	}
	const WaveFile::FormatChunk*			 formatChunk = reinterpret_cast<const WaveFile::FormatChunk*>( chunk->data.data() );

	// From the format chunk we grab the frequency and format for later use.
	frequency = formatChunk->sampleRate;
	GenerateFormatID( formatChunk->channelCount, formatChunk->bitsPerSample );

	// Get data size in bytes.
	chunk = waveFile.GetChunk( 'data' );
	if( chunk == nullptr )
	{
		Nixin::Debug::FatalError( "Wave file from %s loaded correctly, but no data chunk was found. Bad or empty wave file.", fileName.c_str() );
	}
	dataByteSize = chunk->size;

	type = Type::WAVE;
}



//
// LoadOGGFile
//
void Nixin::SoundFile::LoadOGGFile( const std::string& fileName )
{
	std::ifstream					file;
	bool							last = false;
	unsigned int					currentSize = 0;

	// Try to open to file in binary.
	file.open( fileName, std::fstream::in | std::ios::binary );

	if( file.fail() )
	{
		// Throw if something went wrong.
		Nixin::Debug::FatalError( "Could not open %s for reading.", fileName.c_str() );
	}

	// Allocate the new sound file.
	fileContents = new OGGFile();

	OGGFile& oggFile = *reinterpret_cast<OGGFile*>( fileContents );
	OGGFile::Page		page;
	while( !last )
	{
		// Read the page header. We have to do this one variable at a time because struct members
		// are aligned to 
		file.read( reinterpret_cast<char*>( &page.syncCode ), 4 );
		file.read( reinterpret_cast<char*>( &page.version ), 1 );
		file.read( reinterpret_cast<char*>( &page.headerType ), 1 );
		file.read( reinterpret_cast<char*>( &page.granulePosition ), 8 );
		file.read( reinterpret_cast<char*>( &page.bitstreamSerial ), 4 );
		file.read( reinterpret_cast<char*>( &page.pageSequence ), 4 );
		file.read( reinterpret_cast<char*>( &page.checksum ), 4 );
		file.read( reinterpret_cast<char*>( &page.pageSegment ), 1 );

		// Remember where the segment table starts so we can seek back here later if we need to.
		page.segmentTablePosition = currentSize;
		int kkkk = ( int )page.granulePosition;
		// Swap bytes at syncCode, then check if the syncCode is equal to 'OggS', if not the file is either corrupted or not in ogg format.
		MemoryUtility::SwapBytes<unsigned int>( page.syncCode );
		if( page.syncCode != 'OggS' )
		{
			// If the sync code failed, output a warning and remove this incorrect page from the buffer so far.
			Debug::Warning( "Page number %d in ogg file %s, is not in ogg format.", oggFile.pages.size(), fileName.c_str() );

			// Move the file past this page.
			file.ignore( page.pageSegment );
			
			if( !( page.headerType & 0x04 ) )
			{
				oggFile.pages.pop_back();
				continue;
			}
			else
			{
				oggFile.pages.pop_back();
				break;
			}
		}

		// Check page flags.
		// The first segment on this page is a continuation of the last packet on the last page.
		if( !( page.headerType & 0x01 ) )
		{
			// If it's not a continuation, we finalise the packet and move onto the next.
			//oggFile.packets.Add( packet );
			//packet.segments.Clear( true );
		}

		// Last page. Flag last to exit the loop.
		if( page.headerType & 0x04 )
		{
			last = true;
		}



		// Read all segment lengths.
		unsigned char lengths[255];
		file.read( reinterpret_cast<char*>( lengths ), page.pageSegment );

		// Read the total length of the segment table.
		unsigned short int tableLength = 0;
		for( unsigned int i = 0; i < page.pageSegment; i++ )
		{
			tableLength += lengths[i];
		}

		if( page.granulePosition > 0 )
		{
			// Resize our data.
			if( currentSize > 0 )
			{
				oggFile.data = reinterpret_cast<unsigned char*>( realloc( oggFile.data, currentSize + tableLength ) );
			}
			else
			{
				oggFile.data = reinterpret_cast<unsigned char*>( malloc( tableLength ) );
			}


			// Finally read the table into our data array.
			file.read( reinterpret_cast<char*>( oggFile.data + currentSize ), tableLength );
			currentSize += tableLength;

		}
		else if( page.headerType & 0x02 )
		{
			unsigned char	channels;
			unsigned int	rate;
			unsigned int	bitrate;
			char			vorbisID[7];

			// Ignore the pack type.
			file.ignore( 1 );

			
			file.read( vorbisID, 6 );
			vorbisID[6] = '\0';
			if( std::strcmp( vorbisID, "vorbis" ) != 0 )
			{
				Debug::FatalError( "OGG information header unsupported." );
			}
			
			// Ignore the version.
			file.ignore( 4 );
			file.read( reinterpret_cast<char*>( &channels ), 1 );
			file.read( reinterpret_cast<char*>( &rate ), 4 );

			// file.ignore( 8 );
			file.read( reinterpret_cast<char*>( &bitrate ), 4 );

			// Ignore until the end of the page.
			file.ignore( 10 );

			// Work out the al format id.
			GenerateFormatID( channels, 8 );
			frequency = rate;
		}
		else
		{
			file.ignore( tableLength );
		}

		// Add the page to the list.
		oggFile.pages.push_back( page );
	}

	dataByteSize = currentSize;
	file.close();
	type = Type::OGG;
}
