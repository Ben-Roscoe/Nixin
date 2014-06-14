#ifndef _NIXIN_MATH_H_
#define _NIXIN_MATH_H_


namespace Nixin
{

    // Pi.
    const long double					PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862;


    float								ToRadians( float degrees );
    float								ToDegrees( float radians );
    float                               Lerp( float v0, float v1, float time );
}

#endif
