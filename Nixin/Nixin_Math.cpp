#include "Nixin_Math.h"



namespace Nixin
{



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



    //
    // Lerp
    //
    float Nixin::Lerp(float v0, float v1, float time)
    {
        return ( 1.0f - time ) * v0 + ( time * v1 );
    }


}
