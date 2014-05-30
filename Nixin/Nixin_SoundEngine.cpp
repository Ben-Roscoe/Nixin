#include "Nixin_SoundEngine.h"
#include "Nixin_Debug.h"

#include <AL/alc.h>



// Public:



//
// SoundEngine
// Initialises the sound engine with a device.
//
Nixin::SoundEngine::SoundEngine( ALCdevice* soundDevice )
{
	// Check if the device pointer is valid. If it is, assign it.
    Debug::Assert( soundDevice != nullptr, "Bad device when creating sound engine." );
	device = soundDevice;

	// Create the context.
	context = alcCreateContext( device, nullptr );

	// Check if context creation succeeded.
	Debug::Assert( context != nullptr, "Context creation failed." );

	// If so, make it current for this thread.
	alcMakeContextCurrent( context );
}



//
// SoundEngine
// Uninitialised engine.
//
Nixin::SoundEngine::SoundEngine()
{
	device = nullptr;
	context = nullptr;
}



//
// ~Engine
//
Nixin::SoundEngine::~SoundEngine()
{

}




//
// Dispose
//
void Nixin::SoundEngine::Dispose()
{
	alcDestroyContext( context );
	context = nullptr;
	device = nullptr;
}



//
// GetContext
//
const ALCcontext* Nixin::SoundEngine::GetContext() const
{
	return context;
}



//
// GetDevice
//
const ALCdevice* Nixin::SoundEngine::GetDevice() const
{
	return device;
}
