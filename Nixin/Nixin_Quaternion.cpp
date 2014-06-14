#include <cmath>

#include "Nixin_Quaternion.h"
#include "Nixin_Math.h"



//
// Multiply
// Multiplies two quaternions together and returns the result.
//
Nixin::Quaternion Nixin::Quaternion::Multiply( const Quaternion& a, const Quaternion& b )
{
	Nixin::Quaternion				result;

	result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	
	return result;
}



//
// Multiply
// Multiplies a quaternion by a NEPoint and returns the result.
//
Nixin::Point Nixin::Quaternion::Multiply( const Quaternion& q, const Point& p )
{
	Point						result = Point( p );
	Quaternion					quaternionResult;
	Quaternion					finalQuanternion;


	//result = result.GetNormal();
	quaternionResult.x = result.x;
	quaternionResult.y = result.y;
	quaternionResult.z = result.z;
	quaternionResult.w = 0.0f;

	
	finalQuanternion = Multiply( q.GetConjugate(), quaternionResult );
	finalQuanternion = Multiply( finalQuanternion, q );

	return( Point( finalQuanternion.x, finalQuanternion.y, finalQuanternion.z ) );
}



//
// Quaternion
// Creates a quaternion with a w of 1.
//
Nixin::Quaternion::Quaternion()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}




//
// Quaternion
//
Nixin::Quaternion::Quaternion( const float rotation, const Point& axis )
{
	w = std::cos( ToRadians( rotation ) / 2 );
	x = std::sin( ToRadians( rotation ) / 2 ) * axis.x;
	y = std::sin( ToRadians( rotation ) / 2 ) * axis.y;
	z = std::sin( ToRadians( rotation ) / 2 ) * axis.z;
}



//
// ~Quaternion
//
Nixin::Quaternion::~Quaternion()
{
}



//
// ToMatrix
// Creates a rotation matrix out of the quaternion.
//
Nixin::Matrix Nixin::Quaternion::ToMatrix()
{
	//Normalise();

	Matrix							result;

	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;
	return							Matrix( { 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
												2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
												2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
												0.0f, 0.0f, 0.0f, 1.0f } );
}



//
// Normalise
// Normalise the quaternion.
//
void Nixin::Quaternion::Normalise()
{
	float							length = std::sqrt( w * w + x * x + y * y + z * z );
	w /= length;
	x /= length;
	y /= length;
	z /= length;
}




//
// GetConjugate
// Returns the conjugate of the quaternion.
//
Nixin::Quaternion Nixin::Quaternion::GetConjugate() const
{
	Quaternion					result;
	Quaternion					other = Quaternion( *this );

	other.Normalise();

	result.x = -other.x;
	result.y = -other.y;
	result.z = -other.z;
	result.w = other.w;

	return result;
}



//
// GetForwardVector
//
Nixin::Point Nixin::Quaternion::GetForwardVector() const
{
	return Multiply( *this, Point( 0, 0, -1 ) );
}
