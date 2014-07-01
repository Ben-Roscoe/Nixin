#ifndef _NIXIN_MATRIX_H_
#define _NIXIN_MATRIX_H_


#include <string>
#include <array>
#include <initializer_list>

namespace Nixin
{

	class Point;

	class Matrix
	{



	public:
	


		static	Matrix							Multiply( const Matrix& a, const Matrix& b );																// Multiply two NEMatrixs' together.
		static	bool							Add( const Matrix& a, const Matrix& b, Matrix& result );													// Add two NEMatrixs' together.
		static	bool							Subtract( const Matrix& a, const Matrix& b, Matrix& result );												// Subtract two NEMatrixs' together.

		static	Matrix							CreateXRotationMatrix( const float degrees );																// Creates a rotation matrix with the desired degrees.
		static	Matrix							CreateYRotationMatrix( const float degrees );
		static	Matrix							CreateZRotationMatrix( const float degrees );
		static	Matrix							CreateXYZRotationMatrix( const float degreesX, const float degreesY, const float degreesZ );
		static	Matrix							CreateScaleMatrix( const Point scale );																		// Creates a scale matrix with the desired scales.
		static	Matrix							CreateTranslationMatrix( const Point& translation );														// Creates a translation matrix with the desired translation amounts.
		static  Matrix							CreateOthroMatrix( const float depthNear, const float depthFar, const float left, const float right, const float top, const float bottom );
		static  Matrix							CreatePerspectiveMatrix( const float fov, const float aspect, const float depthNear, const float depthFar );
		static  Matrix							CreateLookAtMatrix( const Point& eye, const Point& up, const Point& look );
		static  Matrix							NDCToUVMatrix();

		Matrix();																																			// Creates an empty matrix with width 0, and height 0.
		Matrix( std::initializer_list<float> initialData );						 																			// Creates a matrix with determined width, height and data.
		Matrix( const Matrix& other );																														// Copy constructor. New data must be assigned when this is called.
		~Matrix();																																			// Clear any memory the NEMatrix will hold.

		void									LoadIdentity();																								// Gives this matrix the value of the identity matrix.
		void									Transpose();
		void									Print( const std::string& messageTitle ) const;																		

		Matrix									operator* ( const Matrix& other ) const;
        Matrix&                                 operator=( const Matrix& other );


		int										GetRows() const;																							// Gets the amount of rows.
		int										GetColumns() const;																							// Gets the amount of columns.
		float									GetDataAt( const int row, const int column ) const;															// Gets the element at a specific row and column.
		const float*							GetData() const;
		void									SetDataAt( const int row, const int column, const float newData );											// Replaces an element.


		//Operators:


																		


	private:



		static const int						rows			= 4;																							// The amount of data entries across.
		static const int						columns			= 4;																							// The amount of data entries down.
		std::array<float, 16>					data;																											// The actual data.



	};

}

#endif

