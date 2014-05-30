#ifndef _NIXIN_TIMER_H_
#define _NIXIN_TIMER_H_

#include <chrono>

namespace Nixin
{

	class Timer
	{




	public:




		Timer();
		~Timer();

		void							Start();
		void							Restart();
		void							Pause();
		void							Unpause();

		double							GetHours() const;
		double							GetMinutes() const;
		double							GetSeconds() const;
		double							GetMilliseconds() const;
		bool							GetIsRunning() const;



	private:



		double							startHours;
		double							startMinutes;
		double							startSeconds;
		double							startMilliseconds;

		double							pauseHours;
		double							pauseMinutes;
		double							pauseSeconds;
		double							pauseMilliseconds;

		bool							paused;

	};

}



#endif

