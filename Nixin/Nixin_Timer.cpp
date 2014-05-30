#include "Nixin_Timer.h"

#include <ctime>



//
// Timer
//
Nixin::Timer::Timer()
{
	paused = false;

	startHours = 0;
	startMinutes = 0;
	startSeconds = 0;
	startMilliseconds = 0;

	pauseHours = 0;
	pauseMinutes = 0;
	pauseSeconds = 0;
	pauseMilliseconds = 0;
	
}



//
// ~Timer
//
Nixin::Timer::~Timer()
{
	// Nothing to dispose of.
}



//
// Start
//
void Nixin::Timer::Start()
{
	startSeconds = ( float )clock() / ( float )CLOCKS_PER_SEC;
	startMilliseconds = startSeconds * 1000;
	startMinutes = startSeconds / 60;
	startHours = startSeconds / 3600;
}



//
// Restart
//
void Nixin::Timer::Restart()
{
	startSeconds = ( float )clock() / ( float )CLOCKS_PER_SEC;
	startMilliseconds = startSeconds * 1000;
	startMinutes = startSeconds / 60;
	startHours = startSeconds / 3600;
}



//
// Pause
//
void Nixin::Timer::Pause()
{
	pauseSeconds = ( float )clock() / CLOCKS_PER_SEC;
	pauseMilliseconds = pauseSeconds * 1000;
	pauseMinutes = pauseSeconds / 60;
	pauseHours = pauseSeconds / 3600;
}



//
// Unpause
//
void Nixin::Timer::Unpause()
{
	startSeconds += ( clock() / CLOCKS_PER_SEC ) - pauseSeconds;
	startMilliseconds = startSeconds * 1000;
	startMinutes = startSeconds / 60;
	startHours = startSeconds / 3600;
}



//
// GetSeconds
//
double Nixin::Timer::GetSeconds() const
{
	return ( double )( ( double )clock() / ( double )CLOCKS_PER_SEC ) - startSeconds;
}



//
// GetHours
//
double Nixin::Timer::GetHours() const
{
	return GetSeconds() / 3600;
}



//
// GetMinutes
//
double Nixin::Timer::GetMinutes() const
{
	return GetSeconds() / 60;
}



//
// GetMilliseconds
//
double Nixin::Timer::GetMilliseconds() const
{
	return GetSeconds() * 1000.0;
}



//
// GetIsRunning
//
bool Nixin::Timer::GetIsRunning() const
{
	return !paused;
}