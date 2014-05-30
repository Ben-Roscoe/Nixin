#include <stdlib.h>
#include <math.h>


#include "Nixin_Matrix.h"
#include "Nixin_Point.h"
#include "Nixin_Math.h"
#include "Nixin_Debug_Output.h"



// Public:



// Static:



//
// Multiply
//
Nixin::Matrix Nixin::Matrix::Multiply( const Matrix& a, const Matrix& b )
{
	Matrix			result;

    // Apply matrix multiplcation on the two Matrixs'.
	for( int i = 0; i < a.rows; i++ )
	{	
		for( int j = 0; j < b.columns; j++ )
		{
			result.data[( i * b.columns ) + j] = 0;
			for( int k = 0; k < a.columns; k++ )
			{
				result.data[( i * b.columns ) + j] = result.data[( i * b.columns ) + j] + ( a.GetDataAt( i, k ) * b.GetDataAt( k, j ) );
			}
		}
	}

	return result;
}



//
// Add
//
bool Nixin::Matrix::Add( const Matrix& a, const Matrix& b, Matrix& result )
{

	if( ( a.columns != b.columns ) || ( a.rows != b.rows ) )
	{
		return false;																						// Return an empty matrix if not compatible.
	}
	
	for( int r = 0; r < a.rows; r++ )
	{
		for( int c = 0; c < a.columns; c++ )
		{
			result.SetDataAt( r, c, a.GetDataAt( r, c ) + b.GetDataAt( r, c ) );							// Just add each element together from a and b.
		}
	}

	return true;
}




//
// Subtract
//
bool Nixin::Matrix::Subtract( const Matrix& a, const Matrix& b, Matrix& result )
{

	if( ( a.columns != b.columns ) || ( a.rows != b.rows ) )
	{
		return false;																						// Return an empty matrix if not compatible.
	}

	for( int r = 0; r < a.rows; r++ )
	{
		for( int c = 0; c < a.columns; c++ )
		{
			result.SetDataAt( r, c, a.GetDataAt( r, c ) - b.GetDataAt( r, c ) );												// This time subtract.
		}
	}

	return true;
}



//
// RotationMatrix
// Returns an matrix for rotating about the x-axis.
//
Nixin::Matrix Nixin::Matrix::CreateXRotationMatrix( const float degrees )
{
	Matrix							finalMatrix;
	float							cosx			= cos( ToRadians( degrees ) );
	float							sinx			= sin( ToRadians( degrees ) );

	// Create x rotation matrix.							
	// Set up rotation about the x axis.
	finalMatrix.data[0] = 1;
	finalMatrix.data[1] = 0;
	finalMatrix.data[2] = 0;
	finalMatrix.data[3] = 0;

	finalMatrix.data[4] = 0;
	finalMatrix.data[5] = cosx;
	finalMatrix.data[6] = -sinx;
	finalMatrix.data[7] = 0;

	finalMatrix.data[8] = 0;
	finalMatrix.data[9] = sinx;
	finalMatrix.data[10] = cosx;
	finalMatrix.data[11] = 0;

	finalMatrix.data[12] = 0;
	finalMatrix.data[13] = 0;
	finalMatrix.data[14] = 0;
	finalMatrix.data[15] = 1;

	return finalMatrix;
}



//
// RotationMatrix
// Returns an matrix for rotating about the y-axis.
//
Nixin::Matrix Nixin::Matrix::CreateYRotationMatrix( const float degrees )
{
	Matrix		    				finalMatrix;
	float							cosy			= cos( ToRadians( degrees ) );
	float							siny			= sin( ToRadians( degrees ) );

	// Create y rotation. matrix
	// Set up rotation about the y axis.
	finalMatrix.data[0] = cosy;
	finalMatrix.data[1] = 0;
	finalMatrix.data[2] = siny;
	finalMatrix.data[3] = 0;

	finalMatrix.data[4] = 0;
	finalMatrix.data[5] = 1;
	finalMatrix.data[6] = 0;
	finalMatrix.data[7] = 0;

	finalMatrix.data[8] = -siny;
	finalMatrix.data[9] = 0;
	finalMatrix.data[10] = cosy;
	finalMatrix.data[11] = 0;

	finalMatrix.data[12] = 0;
	finalMatrix.data[13] = 0;
	finalMatrix.data[14] = 0;
	finalMatrix.data[15] = 1;

	return finalMatrix;
}



//
// RotationMatrix
// Returns an matrix for rotating about the z-axis.
//
Nixin::Matrix Nixin::Matrix::CreateZRotationMatrix( const float degrees )
{
	Matrix							finalMatrix;
	float							cosz			= cos( ToRadians( degrees ) );
	float							sinz			= sin( ToRadians( degrees ) );

	// Create z rotation matrix.
	// Set up rotation about the z axis.
	finalMatrix.data[0] = cosz;
	finalMatrix.data[1] = -sinz;
	finalMatrix.data[2] = 0;
	finalMatrix.data[3] = 0;

	finalMatrix.data[4] = sinz;
	finalMatrix.data[5] = cosz;
	finalMatrix.data[6] = 0;
	finalMatrix.data[7] = 0;

	finalMatrix.data[8] = 0;
	finalMatrix.data[9] = 0;
	finalMatrix.data[10] = 1;
	finalMatrix.data[11] = 0;

	finalMatrix.data[12] = 0;
	finalMatrix.data[13] = 0;
	finalMatrix.data[14] = 0;
	finalMatrix.data[15] = 1;


	return finalMatrix;
}




//
// CreateXYZRotationMatrix
// Creates a matrix for rotating about all points.
//
Nixin::Matrix Nixin::Matrix::CreateXYZRotationMatrix( const float degreesX, const float degreesY, const float degreesZ )
{
	Matrix							finalMatrix;

	float							cosx			= cos( ToRadians( degreesX ) );
	float							sinx			= sin( ToRadians( degreesX ) );

	
	float							cosy			= cos( ToRadians( degreesY ) );
	float							siny			= sin( ToRadians( degreesY ) );
	
	float							cosz			= cos( ToRadians( degreesZ ) );
	float							sinz			= sin( ToRadians( degreesZ ) );

	finalMatrix.data[0] = cosy * cosz;
	finalMatrix.data[1] = -cosy * sinz;
	finalMatrix.data[2] = siny;
	finalMatrix.data[3] = 0;

	finalMatrix.data[4] = cosx * sinz + sinx * siny * cosz;
	finalMatrix.data[5] = cosx * cosz - sinx * siny * sinz;
	finalMatrix.data[6] = -sinx * cosy;
	finalMatrix.data[7] = 0;

	finalMatrix.data[8] = sinx * sinz - cosx * siny * cosz;
	finalMatrix.data[9] = sinx * cosz + cosx * siny * sinz;
	finalMatrix.data[10] = cosx * cosy;
	finalMatrix.data[11] = 0;

	finalMatrix.data[12] = 0;
	finalMatrix.data[13] = 0;
	finalMatrix.data[14] = 0;
	finalMatrix.data[15] = 1;

	return finalMatrix;
}



//
// ScaleMatrix
// Returns a scale matrix based on the scales given.
//
Nixin::Matrix Nixin::Matrix::CreateScaleMatrix( const Point scale )
{
	Matrix							outMatrix;

	outMatrix.data[0] = scale.x;
	outMatrix.data[1] = 0;
	outMatrix.data[2] = 0;
	outMatrix.data[3] = 0;

	outMatrix.data[4] = 0;
	outMatrix.data[5] = scale.y;
	outMatrix.data[6] = 0;
	outMatrix.data[7] = 0;

	outMatrix.data[8] = 0;
	outMatrix.data[9] = 0;
	outMatrix.data[10] = scale.z;
	outMatrix.data[11] = 0;

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = 0;
	outMatrix.data[15] = 1;

	return outMatrix;
}



//
// TranslationMatrix
// Returns a translationMatrix based on the translation 
// coordinates given.
//
Nixin::Matrix Nixin::Matrix::CreateTranslationMatrix( const Point& translation )
{
	Matrix							outMatrix;

	outMatrix.data[0] = 1;
	outMatrix.data[1] = 0;
	outMatrix.data[2] = 0;
	outMatrix.data[3] = translation.x;

	outMatrix.data[4] = 0;
	outMatrix.data[5] = 1;
	outMatrix.data[6] = 0;
	outMatrix.data[7] = translation.y;

	outMatrix.data[8] = 0;
	outMatrix.data[9] = 0;
	outMatrix.data[10] = 1;
	outMatrix.data[11] = translation.z;

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = 0;
	outMatrix.data[15] = 1;

	return outMatrix;
}



//
// CreateOrthoMatrix
//
Nixin::Matrix Nixin::Matrix::CreateOthroMatrix( const float depthNear, const float depthFar, const float left, const float right, const float top, const float bottom )
{
	Matrix						outMatrix;

	outMatrix.data[0] = 2.0f / ( right - left );
	outMatrix.data[1] = 0;
	outMatrix.data[2] = 0;
	outMatrix.data[3] = ( right + left ) / -( right - left );

	outMatrix.data[4] = 0;
	outMatrix.data[5] = 2.0f / ( top - bottom );
	outMatrix.data[6] = 0;
	outMatrix.data[7] = ( top + bottom ) / -( top - bottom );

	outMatrix.data[8] = 0;
	outMatrix.data[9] = 0;
	outMatrix.data[10] = -2.0f / ( depthFar - depthNear );
	outMatrix.data[11] = -( depthFar + depthNear ) / -( depthFar - depthNear);

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = 0;
	outMatrix.data[15] = 1;

	return outMatrix;
}



//
// CreatePerspectiveMatrix
//
Nixin::Matrix Nixin::Matrix::CreatePerspectiveMatrix( const float fov, const float aspect, const float depthNear, const float depthFar )
{
	Matrix							outMatrix;
	float							angle					= ToRadians( fov );
	float							d						= 1.0f / tan( angle * 0.5f );

	outMatrix.data[0] = d / aspect;
	outMatrix.data[1] = 0;
	outMatrix.data[2] = 0;
	outMatrix.data[3] = 0;

	outMatrix.data[4] = 0;
	outMatrix.data[5] = d;
	outMatrix.data[6] = 0;
	outMatrix.data[7] = 0;

	outMatrix.data[8] = 0;
	outMatrix.data[9] = 0;
	outMatrix.data[10] = ( depthNear + depthFar ) / ( depthNear - depthFar );
	outMatrix.data[11] = ( 2.0f * depthFar * depthNear ) / ( depthNear - depthFar );

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = -1.0f;
	outMatrix.data[15] = 0;

	return outMatrix;
}



//
// LookAt
//
Nixin::Matrix Nixin::Matrix::CreateLookAtMatrix( const Point& eye, const Point& up, const Point& look )
{
	Point						 right		= Point::Cross( up, look );
	Matrix						 outMatrix;

	outMatrix.data[0] = right.x;
	outMatrix.data[1] = up.x;
	outMatrix.data[2] = look.x;
	outMatrix.data[3] = eye.x;

	outMatrix.data[4] = right.y;
	outMatrix.data[5] = up.y;
	outMatrix.data[6] = look.y;
	outMatrix.data[7] = eye.y;

	outMatrix.data[8] = right.z;
	outMatrix.data[9] = up.z;
	outMatrix.data[10] = look.z;
	outMatrix.data[11] = eye.z;

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = 0;
	outMatrix.data[15] = 1;

	return outMatrix;
}



//
// NDCToUVMatrix
// A matrix which converts normalised device coordinates to texture uv coordinates.
//
Nixin::Matrix Nixin::Matrix::NDCToUVMatrix()
{
	Matrix							outMatrix;

	outMatrix.data[0] = 0.5f;
	outMatrix.data[1] = 0;
	outMatrix.data[2] = 0;
	outMatrix.data[3] = 0.5f;

	outMatrix.data[4] = 0;
	outMatrix.data[5] = 0.5f;
	outMatrix.data[6] = 0;
	outMatrix.data[7] = 0.5f;

	outMatrix.data[8] = 0;
	outMatrix.data[9] = 0;
	outMatrix.data[10] = 0.5f;
	outMatrix.data[11] = 0.5f;

	outMatrix.data[12] = 0;
	outMatrix.data[13] = 0;
	outMatrix.data[14] = 0;
	outMatrix.data[15] = 1.0f;

	return outMatrix;
}


// Constructors / Destructors



//
// Matrix
// Creates an empty matrix.
//
Nixin::Matrix::Matrix()
{
	//LoadIdentity();
}



//
// Matrix
// Creates a Matrix with initialised width, height and data.
//
Nixin::Matrix::Matrix( std::initializer_list<float> initialData )
{
	std::copy( initialData.begin(), initialData.end(), data.begin() );
}



//
// Matrix
//
Nixin::Matrix::Matrix( const Matrix& other )
{
	data = other.data;
}



//
// ~Matrix
// Clear the data in the Matrix.
//
Nixin::Matrix::~Matrix()
{
}



// Main Methods:



//
// LoadIdentity
// Gives this matrix the identity value.
//
void Nixin::Matrix::LoadIdentity()
{
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	
	data[4] = 0;
	data[5] = 1;
	data[6] = 0;
	data[7] = 0;
	
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = 0;
	
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
}



//
// Transpose
// Transposes the matrix object.
//
void Nixin::Matrix::Transpose()
{
	std::array<float, 16>  newData;

	for( int i = 0; i < rows * columns; i++ )
	{
		newData[i] = data[( ( i % rows ) * columns ) + ( i / rows )];
	}

	data = newData;
}



//
// Print
//
void Nixin::Matrix::Print( const std::string& messageTitle ) const
{
	std::string								finalString;

	for( int y = 0; y < rows; y++ )
	{
		for( int x = 0; x < columns; x++ )
		{
			finalString += std::to_string( GetDataAt( y, x ) );
			finalString += ",";
		}
		finalString += "\n";
	}
    Debug::Write( "%s: %s", messageTitle.c_str(), finalString.c_str() );
}




// Operators



//
// operator*
//
Nixin::Matrix Nixin::Matrix::operator*( const Matrix& other ) const
{
	return Matrix::Multiply( *this, other );
}



// Getters and Setters



//
// GetWidth
// 
int Nixin::Matrix::GetRows() const
{
	return rows;
}



//
// GetHeight
//
int Nixin::Matrix::GetColumns() const
{
	return columns;
}



//
// GetDataAt
//
float Nixin::Matrix::GetDataAt( const int row, const int column ) const
{
	//if( row <= rows && row >= 0 && column <= columns && row >= 0 )						// Check the bounds.
	//{
		return data[column + ( row * columns )];										// And return the value.
	//}
	//return 0.0f;
}



//
// GetData
//
const float* Nixin::Matrix::GetData() const
{
	return data.data();
}



//
// SetDataAt
//
void Nixin::Matrix::SetDataAt( const int row, const int column, const float newData )
{
	//if( row <= rows && row >= 0 && column <= columns && row >= 0 )						// Check the bounds.
	//{
		data[column + ( row * columns )] = newData;										// And set the value.
	//}
}
