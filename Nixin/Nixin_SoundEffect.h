#ifndef _NIXIN_SOUNDEFFECT_H_
#define _NIXIN_SOUNDEFFECT_H_


#include <string>
#include <memory>

#include <AL/al.h>
#include "Nixin_SoundFile.h"

namespace Nixin
{
	class SoundEffect
	{




	public:



		enum class Type
		{
			BUFFER,
			STREAM,
		};


		SoundEffect();
		SoundEffect( const std::string& fileName, const Type storageType );
		SoundEffect( const SoundFile& file );
		SoundEffect( const SoundEffect& other );
		// SoundEffect( const SoundStream& stream );
		~SoundEffect();

		void				Play( const bool looped ) const;
		void				Stop() const;
		void				Restart() const;


		void				ClearInstance();
		SoundEffect&		operator=( const SoundEffect& other );


	private:



		std::shared_ptr<ALuint>			id;
		unsigned int					playTime;
		Type							type;



	};
}


#endif