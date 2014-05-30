#ifndef _NIXIN_GAMETIME_H_
#define _NIXIN_GAMETIME_H_


#include "Nixin_Timer.h"
#include <stdint.h>


namespace Nixin
{
	class GameTime
	{


	public:



		GameTime();
		~GameTime();

		void					Update();

		uint64_t				TotalFrames() const;
		double					DeltaTime()	  const;
		double					TotalTime()	  const;


	private:


		
		Timer					timer;
		double					lastFrameStart			= 0.0f;
		uint64_t				frames					= 0;



	};
}




#endif
