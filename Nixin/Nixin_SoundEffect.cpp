#include "Nixin_SoundEffect.h"



//
// SoundEffect
//
Nixin::SoundEffect::SoundEffect()
{

}



//
// SoundEffect
// Loads a sound effect from a file location as either a buffer or a stream.
//
Nixin::SoundEffect::SoundEffect( const std::string& fileName, const Type storageType )
{
	type = storageType;
	playTime = 0;
}



//
// SoundEffect
// Loads a sound effect from a Nixin sound file.
//
Nixin::SoundEffect::SoundEffect( const SoundFile& file )
{
	type = Type::BUFFER;
	playTime = 0;


	// Allocate new AL id and buffer data.
	id = std::shared_ptr<ALuint>( new ALuint() );
	alGenBuffers( 1, id.get() );

	alBufferData( *id.get(), file.GetFormatID(), file.GetRawData(), file.GetDataByteSize(), file.GetFrequency() );
	//if( file.GetFormatID() == AL_FORMAT_STEREO16 )
	{
			ALenum d = alGetError();
	int k = 3;
	}
}



//
// SoundEffect
// Loads a sound effect from a Nixin sound stream.
//
//Nixin::SoundEffect::SoundEffect( const SoundStream& stream )
//{
	// type = Type::STREAM;
//}



//
// ~SoundEffect
//
Nixin::SoundEffect::~SoundEffect()
{
	ClearInstance();
}



//
// ClearInstance
//
void Nixin::SoundEffect::ClearInstance()
{
	if( id.get() != nullptr && id.unique() )
	{
		alDeleteBuffers( 1, id.get() );
	}
	id.reset();
}



//
// Copy constructor.
//
Nixin::SoundEffect::SoundEffect( const SoundEffect& other )
{
	ClearInstance();
	id = other.id;
	playTime = other.playTime;
	type = other.type;
}



//
// operator=
//
Nixin::SoundEffect& Nixin::SoundEffect::operator=( const SoundEffect& other )
{
	ClearInstance();
	id = other.id;
	playTime = other.playTime;
	type = other.type;

	return *this;
}



//
// Play
//
void Nixin::SoundEffect::Play( const bool looped ) const
{
	ALuint source;
	alGenSources( 1, &source );
	alSourcei( source, AL_LOOPING, looped );
	alSourcei( source, AL_BUFFER, *id.get() );
	alSourcePlay( source );
}