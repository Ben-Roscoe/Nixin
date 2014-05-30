#include "Nixin_Rectangle.h"


// Public:



//
// Rectangle
// Initialises a rectangle with all 0'd components.
//
Nixin::Rectangle::Rectangle()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}



//
// Rectangle
// Initialises all components to the given values.
//
Nixin::Rectangle::Rectangle( const float X, const float Y, const float Width, const float Height )
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
}



//
// Rectangle
// Initialises the components of the rectangle with a point and two floats for the size.
//
Nixin::Rectangle::Rectangle( const Point& position, const float Width, const float Height )
{
	x = position.x;
	y = position.y;
	width = Width;
	height = Height;
}



//
// Rectangle
//
Nixin::Rectangle::Rectangle( const float X, const float Y, const Point& size )
{
	x = X;
	y = Y;
	width = size.x;
	height = size.y;
}



//
// Rectangle
// Initialises the components of the rectangle with two points.
//
Nixin::Rectangle::Rectangle( const Point& position, const Point& size )
{
	x = position.x;
	y = position.y;
	width = size.x;
	height = size.y;
}



//
// ~Rectangle
//
Nixin::Rectangle::~Rectangle()
{
}



//
// Intersects
// Check if this rectangle intersects another.
//
bool Nixin::Rectangle::Intersects( const Rectangle& other ) const
{
	return ( Left() < other.Right() && Right() > other.Left() && Bottom() < other.Top() && Top() > other.Bottom() );
}



//
// IntersectsCircle
//
bool Nixin::Rectangle::IntersectsCircle( const Point& center, float radius ) const
{
	Point				distance		= Point::DistanceVector( center, Center() );

	if( distance.x > ( width / 2.0f + radius ) )
	{
		return false;
	}
	if( distance.y > ( height / 2.0f + radius ) )
	{
		return false;
	}

	if( distance.x <= ( width / 2.0f ) )
	{
		return true;
	}
	if( distance.y <= ( height / 2.0f ) )
	{
		return true;
	}


	float				cornerDistanceSq = ( distance.x - width / 2.0f ) * ( distance.x - width / 2.0f ) + ( distance.y - height / 2.0f ) * ( distance.y - height / 2.0f );
	return cornerDistanceSq <= ( radius * radius );
}



//
// Contains
// Checks if another rectangle is completely contained in this one.
//
bool Nixin::Rectangle::Contains( const Rectangle& other ) const
{
	return ( other.Left() > Left() && other.Right() < Right() && other.Bottom() > Bottom() && other.Top() < Top() );
}



//
// Position
// Gets the position of the rectangle as a point.
//
Nixin::Point Nixin::Rectangle::Position() const
{
	return Point( x, y );
}



//
// Size
// Gets the width and height of the rectangle as a point.
//
Nixin::Point Nixin::Rectangle::Size() const
{
	return Point( width, height );
}



//
// Center
//
Nixin::Point Nixin::Rectangle::Center() const
{
	return Point( x + ( width / 2.0f ), y + ( height / 2.0f ) );
}



//
// HalfSize
// Returns a point that is half the size of the rectangle.
//
Nixin::Point Nixin::Rectangle::HalfSize() const
{
	return Point( width / 2.0f, height / 2.0f );
}



//
// Top
//
float Nixin::Rectangle::Top() const
{
	return y + height;
}



//
// Left
//
float Nixin::Rectangle::Left() const
{
	return x;
}



//
// Bottom
//
float Nixin::Rectangle::Bottom() const
{
	return y;
}



//
// Right
//
float Nixin::Rectangle::Right() const
{
	return x + width;
}



//
// SetPosition
// Sets x and y with a point.
//
void Nixin::Rectangle::SetPosition( const Point& newPosition )
{
	x = newPosition.x;
	y = newPosition.y;
}



//
// SetSize
// Sets width and height with a point.
//
void Nixin::Rectangle::SetSize( const Point& newSize )
{
	width = newSize.x;
	height = newSize.y;
}



// Private: