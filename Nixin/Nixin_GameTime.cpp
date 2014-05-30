#include "Nixin_GameTime.h"



//
// GameTime
//
Nixin::GameTime::GameTime()
{
	timer.Start();
}



//
// ~GameTime
//
Nixin::GameTime::~GameTime()
{

}



//
// Update
//
void Nixin::GameTime::Update()
{
	lastFrameStart = timer.GetMilliseconds();
	frames++;
}



//
//
//
uint64_t Nixin::GameTime::TotalFrames() const
{
	return frames;
}



//
// DeltaTime
//
double Nixin::GameTime::DeltaTime() const
{
	return timer.GetMilliseconds() - lastFrameStart;
}



//
// TotalTime
//
double Nixin::GameTime::TotalTime() const
{
	return timer.GetMilliseconds();
}