#ifndef NIXIN_APPLICATION_H
#define NIXIN_APPLICATION_H



#include "Nixin_SoundEngine.h"


namespace Nixin
{

    class Application
    {



    public:



        Application();


        static void                        Start();
        static ALCdevice*                  GetSoundDevice();

    private:


        static ALCdevice*                   soundDevice;


    };

}

#endif // NIXIN_APPLICATION_H
