#include "Nixin_Application.h"
#include "Nixin_Debug_Output.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <FreeImage.h>




namespace Nixin
{
    ALCdevice* Application::soundDevice;




    //
    // Start
    //
    void Application::Start()
    {
        soundDevice = alcOpenDevice( "" );
        if( soundDevice == nullptr )
        {
            Debug::Warning( "Sound device failed to open." );
        }

        FreeImage_Initialise();

    }



    //
    // GetSoundDevice
    //
    ALCdevice* Application::GetSoundDevice()
    {
        return soundDevice;
    }
}


