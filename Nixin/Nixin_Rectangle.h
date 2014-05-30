#ifndef _NIXIN_RECTANGLE_H_
#define _NIXIN_RECTANGLE_H_


#include "Nixin_Point.h"

namespace Nixin
{

	class Rectangle
	{



	public:



		float									x;
		float									y;
		float									width;
		float									height;



		Rectangle();
		Rectangle( const float X, const float Y, const float Width, const float Height );
		Rectangle( const Point& position, const float Width, const float Height );
		Rectangle( const float X, const float Y, const Point& size );
		Rectangle( const Point& position, const Point& size );
		~Rectangle();


		bool									Intersects( const Rectangle& other ) const;				     	// Checks if other intersects this.
		bool									IntersectsCircle( const Point& center, float radius ) const;
		bool									Contains( const Rectangle& other ) const;						// Checks if this completely contains other.
		Point									Position() const;												// Returns x adn y as a point.
		Point									Size() const;
		Point									Center()   const;
		Point									HalfSize() const;
		float									Top() const;
		float									Left() const;
		float									Bottom() const;
		float									Right() const;

		void									SetPosition( const Point& newPosition );
		void									SetSize( const Point& newSize );



	private:



	};

}

#endif