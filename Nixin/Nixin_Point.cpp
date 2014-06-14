#include <cmath>
#include "Nixin_Point.h"
#include "Nixin_Colour.h"
#include "Nixin_Canvas.h"
#include "Nixin_Math.h"


// Public:

// Static:



//
// Multiply
// Multiplies a Point with an Matrix, and returns the resulting point
//
Nixin::Point Nixin::Point::Multiply( const Point& a, const Matrix& b )
{
	Point			 result			= Point();
	
	result.x = b.GetDataAt( 0, 0 ) * a.x + b.GetDataAt( 0, 1 ) * a.y + b.GetDataAt( 0, 2 ) * a.z +  b.GetDataAt( 0, 3 );
	result.y = b.GetDataAt( 1, 0 ) * a.x + b.GetDataAt( 1, 1 ) * a.y + b.GetDataAt( 1, 2 ) * a.z +  b.GetDataAt( 1, 3 );
	result.z = b.GetDataAt( 2, 0 ) * a.x + b.GetDataAt( 2, 1 ) * a.y + b.GetDataAt( 2, 2 ) * a.z +  b.GetDataAt( 2, 3 );
	
	return result;
}



//
// MultiplyNormal
//
Nixin::Point Nixin::Point::MultiplyNormal( const Point& normal, const Matrix&b )
{
	Point			 result			= Point();
	
	result.x = b.GetDataAt( 0, 0 ) * normal.x + b.GetDataAt( 0, 1 ) * normal.y + b.GetDataAt( 0, 2 ) * normal.z;
	result.y = b.GetDataAt( 1, 0 ) * normal.x + b.GetDataAt( 1, 1 ) * normal.y + b.GetDataAt( 1, 2 ) * normal.z;
	result.z = b.GetDataAt( 2, 0 ) * normal.x + b.GetDataAt( 2, 1 ) * normal.y + b.GetDataAt( 2, 2 ) * normal.z;
	
	return result;
}



//
// Multiply
//
Nixin::Point Nixin::Point::Multiply( const Point& a, float scalar )
{
	return Point( a.x * scalar, a.y * scalar, a.z * scalar );
}



//
// Divide
//
Nixin::Point Nixin::Point::Divide( const Point& a, float scalar )
{
	if( scalar != 0.0f )
	{
		return Point( a.x / scalar, a.y / scalar, a.z / scalar );
	}
	Nixin::Debug::FatalError( "Attempted to divide a point by 0." );
}



//
// Subtract
//
Nixin::Point Nixin::Point::Subtract( const Point& a, float scalar )
{
	return Point( a.x - scalar, a.y - scalar, a.z - scalar );
}



//
// Add
//
Nixin::Point Nixin::Point::Add( const Point& a, float scalar )
{
	return Point( a.x + scalar, a.y + scalar, a.z + scalar );
}



//
// DistanceVector
//
Nixin::Point Nixin::Point::DistanceVector( const Point& a, const Point& b )
{
	return Point( std::abs( a.x - b.x ), std::abs( a.y - b.y ) );
}



//
// Distance2D
// Gets the distance between two points in 2d space.
// using Pythagoras' theorem.
//
float Nixin::Point::Distance2D( const Point& a, const Point& b )
{
	return sqrt( pow( abs( a.x - b.x ), 2 ) + pow( abs( a.y - b.y ), 2 ) );
}



//
// Distance3D
// Gets the distance between two points in 3d space.
//
float Nixin::Point::Distance3D( const Point& a, const Point& b )
{
	return sqrt( pow( abs( a.x - b.x ), 2 ) + pow( abs( a.y - b.y ), 2 ) + pow( abs( a.z - b.z ), 2 ) );
}



//
// Dot
// Gets the dot product of the two points.
//
float Nixin::Point::Dot( const Point a, const Point b )
{
	return ( ( a.x * b.x ) + ( a.y * b.y ) + ( a.z * b.z ) );
}



//
// Cross
// Gets the cross product of two points.
//
Nixin::Point Nixin::Point::Cross( const Point& a, const Point& b )
{
	Point											result					= Point();
 
	result.x = ( a.y * b.z ) - ( a.z * b.y );
	result.y = ( a.z * b.x ) - ( a.x * b.z );
	result.z = ( a.x * b.y ) - ( a.y * b.x );

	return result;
}



//
// TranslateByNormal
//
Nixin::Point Nixin::Point::TranslateByNormal( const Point& a, const Point& b, const float length )
{
	float							deltaX;
	float							deltaY;
	float							deltaZ;
	Point							outPoint;

	deltaX = ( b.x - a.x ) * length / Distance3D( a, b );
	deltaY = ( b.y - a.y ) * length / Distance3D( a, b );
	deltaZ = ( b.z - a.z ) * length / Distance3D( a, b );

	outPoint.x += deltaX;
	outPoint.y += deltaY;
	outPoint.z += deltaZ;

	return outPoint;
}



//
// NormalToFace
//
Nixin::Point Nixin::Point::NormalToFace( const Point& a, const Point& b, const Point& c )
{
	Point							v1 = Point( b.x - a.x, b.y - a.y, b.z - a.z );
	Point							v2 = Point( b.x - c.x, b.y - c.y, b.z - c.z );
	v1 = v1.GetNormal();
	v2 = v2.GetNormal();
    return Cross( v1, v2 ).GetNormal();
}



//
// Lerp
//
Nixin::Point Nixin::Point::Lerp( const Nixin::Point& a, const Nixin::Point& b, float time )
{
    return Point( Nixin::Lerp( a.x, b.x, time ), Nixin::Lerp( a.y, b.y, time ), Nixin::Lerp( a.z, b.z, time ) );
}



//
// Point
// Initialises all components to 0.
//
Nixin::Point::Point()
{
	x = 0;
	y = 0;
	z = 0;
}



//
// Point
// Initialise z to 0, set x and y to parameters given.
//
Nixin::Point::Point( const float X, const float Y  )
{
	x = X;
	y = Y;
	z = 0;
}



//
// Point
// Set all components.
//
Nixin::Point::Point( const float X, const float Y, const float Z )
{
	x = X;
	y = Y;
	z = Z;
}



//
// ~Point
// Dispose of memeory.
//
Nixin::Point::~Point()
{
	// Nothing to dispose of.
}



// Main Methods



//
// Transform
// Multiplies each of the matrices given, with the point3.
//
void Nixin::Point::Transform( const Matrix* matrices, const int matrixCount )
{
	Point				newPoint		= Point( 0, 0, 0 );

	for( int i = 0; i < matrixCount; i++ )
	{
		newPoint = Point::Multiply( *this, matrices[i] );
		x = newPoint.x;
		y = newPoint.y;
		z = newPoint.z;
	}
}



//
// GetLength
//
float Nixin::Point::GetLength() const
{
	return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}



//
// GetNormal
//
Nixin::Point Nixin::Point::GetNormal() const
{
	float							length = GetLength();
	return Point( x / length, y / length, z / length );
}



//
// AngleBetweenRadians
// Returns the angle between this vector and another in radians.
//
float Nixin::Point::AngleBetweenRadians( const Point other ) const
{
	return acos( Point::Dot( *this, other ) );
}



//
// AngleBetweenDegrees
// Returns the angle between this vector and another in degrees.
//
float Nixin::Point::AngleBetweenDegrees( const Point other ) const
{
	return ToDegrees( acos( Point::Dot( *this, other ) ) );
}




// Operators



//
// operator +=
//
void Nixin::Point::operator+=( const Point& other )
{
	x += other.x;
	y += other.y;
	z += other.z;
}



//
// operator -=
//
void Nixin::Point::operator-=( const Point& other )
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}



//
// operator ++
//
void Nixin::Point::operator++()
{
	x++;
	y++;
	z++;
}



//
// operator --
//
void Nixin::Point::operator--()
{
	x--;
	y--;
	z--;
}



//
// operator -
// Returns the negation of this point.
//
Nixin::Point Nixin::Point::operator-() const
{
	return Point( -x, -y, -z );
}



//
// operator +
//
Nixin::Point Nixin::Point::operator+() const
{
	return Point( +x, +y, +z );
}



//
// operator +
// Addition.
//
Nixin::Point Nixin::Point::operator+( const Point& other ) const
{
	return Point( other.x + x, other.y + y, other.z + z );
}



//
// operator +
//
Nixin::Point Nixin::Point::operator+( float scalar ) const
{
	return Add( *this, scalar );
}



//
// operator -
// Subtraction.
//
Nixin::Point Nixin::Point::operator-( const Point& other ) const
{
	return Point( x - other.x, y - other.y, z - other.z );
}



//
// operator -
//
Nixin::Point Nixin::Point::operator-( float scalar  ) const
{
	return Subtract( *this, scalar );
}



//
// operator *
// Returns the product of this point and the given matrix.
//
Nixin::Point Nixin::Point::operator*( const Matrix& matrix ) const
{
	return Point::Multiply( *this, matrix );
}



//
// operator *
//
Nixin::Point Nixin::Point::operator*( float scalar ) const
{
	return Multiply( *this, scalar );
}



//
// operator
//
Nixin::Point Nixin::Point::operator/( float scalar ) const
{
	return Divide( *this, scalar );
}



//
// operator ==
//
bool Nixin::Point::operator==( const Point& other ) const
{
	return ( x == other.x && y == other.y && z == other.z );
}



//
// operator !=
//
bool Nixin::Point::operator!=( const Point& other ) const
{
	return ( x != other.x && y != other.y && z != other.z );
}
