#ifndef _NIXIN_POINT_H_
#define _NIXIN_POINT_H_

#include "Nixin_Matrix.h"


namespace Nixin
{

	class Canvas;

	class Point
	{



	public:



		float			x;																			// X component //<---->//
		float			y;																			// Y component //^	  //
		float			z;																			// Z component //.     //


		static float	Distance2D( const Point& a, const Point& b );								// Returns the distance between two points in 2-dimensional space.
		static Point	DistanceVector( const Point& a, const Point& b );
		static float	Distance3D( const Point& a, const Point& b );								// Returns the distance between two points in 3-dimensional space.
		static float    Dot( const Point a, const Point b );
		static Point	Multiply( const Point& a, const Matrix& b );
		static Point	MultiplyNormal( const Point& normal, const Matrix&b );
		static Point	Multiply( const Point& a, float scalar );
		static Point	Divide( const Point& a, float scalar );
		static Point	Subtract( const Point& a, float scalar );
		static Point	Add( const Point& a, float scalar );
		static Point	Cross( const Point& a, const Point& b );
		static Point	TranslateByNormal( const Point& a, const Point& b, const float length );
		static Point    NormalToFace( const Point& a, const Point& b, const Point& c );
        static Point    Lerp( const Point& a, const Point& b, float time );


		Point();																					// Initialise all components to 0.
		Point( const float X, const float Y );														// Initialise z component to 0.
		Point( const float X, const float Y, const float Z );										// Set all components.
		~Point();

		void			Transform( const Matrix* matrices, const int matrixCount );					// Transforms the 2 dimensional components of the point, by the matrices given.
		Point			GetNormal() const;
		float			GetLength() const;
		float			AngleBetweenRadians( const Point other ) const;
		float			AngleBetweenDegrees( const Point other ) const;

		void			operator +=( const Point& other );
		void			operator -=( const Point& other );
		void			operator ++();
		void			operator --();

		Point			operator+() const;
		Point			operator+( const Point& other ) const;
		Point			operator+( float scalar ) const;

		Point			operator-() const;
		Point			operator-( float scalar ) const;
		Point			operator-( const Point& other ) const;

		Point			operator*( const Matrix& matrix ) const;
		Point			operator*( float scalar ) const;

		Point			operator/( float scalar ) const;
		bool			operator==( const Point& other ) const;
		bool			operator!=( const Point& other ) const;

	

	private:







	};

}

#endif
