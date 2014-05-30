#ifndef _NIXIN_SOUNDENGINE_H_
#define _NIXIN_SOUNDENGINE_H_


// Forward declare stuff so this file can be linked to without dependencies.
struct ALCdevice_struct;
struct ALCcontext_struct;

typedef ALCdevice_struct ALCdevice;
typedef ALCcontext_struct ALCcontext;



namespace Nixin
{
	class SoundEngine
	{



	public:



		SoundEngine();
        SoundEngine( ALCdevice* soundDevice );
		~SoundEngine();

		void					Dispose();
		const ALCcontext*		GetContext() const;
		const ALCdevice*		GetDevice() const;



	private:




        ALCdevice*              device;
		ALCcontext*				context;




	};
}



#endif
