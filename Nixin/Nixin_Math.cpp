#include "Nixin_Math.h"



//
// ToRadians
// Converts degress to radians.
//
float ToRadians( const float degrees )
{
	return ( degrees / 180 ) * ( float )PI;
}



//
// ToDegrees
// Converts radians to degrees.
//
float ToDegrees( const float radians )
{
	return ( radians / ( float )PI ) * 180;
}