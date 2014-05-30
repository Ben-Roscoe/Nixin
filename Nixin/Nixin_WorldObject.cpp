#include "Nixin_WorldObject.h"



//
// NEWorldObject
// Initialises the world object.
//
Nixin::WorldObject::WorldObject()
{
	rotation = Quaternion();
	rotation.w = 1.0f;

	position = Point();
}



//
// ~NEWorldObject
//
Nixin::WorldObject::~WorldObject()
{
}



//
// MoveGlobalX
// Move along the global x-axis by distance.
//
void Nixin::WorldObject::MoveGlobalX( const float distance )
{
	position.x = position.x + distance;
}



//
// MoveGlobalY
// Move along the global y-axis by distance.
//
void Nixin::WorldObject::MoveGlobalY( const float distance )
{
	position.y = position.y + distance;
}



//
// MoveGlobalZ
// Move along the global z-axis by distance.
//
void Nixin::WorldObject::MoveGlobalZ( const float distance )
{
	position.z = position.z + distance;
}



//
// MoveForward
// Move the object forward by distance along its current orientation.
//
void Nixin::WorldObject::MoveForward( const float distance )
{
	position = position + Quaternion::Multiply( rotation, Point( 0.0f, 0.0f, -distance ) );
}



//
// MoveBackwards
// Move the object backwards by distance along its current orientation.
//
void Nixin::WorldObject::MoveBackward( const float distance )
{
	position = position - Quaternion::Multiply( rotation, Point( 0.0f, 0.0f, -distance ) );
}



//
// MoveUp
// Move the object up by distance along its current orientation.
//
void Nixin::WorldObject::MoveUp( const float distance )
{
	position = position - Quaternion::Multiply( rotation, Point( 0.0f, -distance, 0.0f ) );
}



//
// MoveDown
// Move the object down by distance along its current orientation.
//
void Nixin::WorldObject::MoveDown( const float distance )
{
	position = position + Quaternion::Multiply( rotation, Point( 0.0f, -distance, 0.0f ) );
}



//
// MoveRight
// Move the object right by distance along its current orientation.
//
void Nixin::WorldObject::MoveRight( const float distance )
{
	position = position - Quaternion::Multiply( rotation, Point( -distance, 0.0f, 0.0f ) );
}



//
// MoveLeft
// Move the object left by distance along its current orientation.
//
void Nixin::WorldObject::MoveLeft( const float distance )
{
	position = position + Quaternion::Multiply( rotation, Point( -distance, 0.0f, 0.0f ) );
}



//
// RotateLocalX
// increases the rotation about the local( object orientation ) x axis, by angle degrees.
//
void Nixin::WorldObject::RotateGlobalX( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 1.0f, 0.0f, 0.0f ) );
	rotation =  Quaternion::Multiply( rotation, q );
}



//
// RotateLocalY
// increases the rotation about the local( object orientation ) y axis, by angle degrees.
//
void Nixin::WorldObject::RotateGlobalY( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 0.0f, 1.0f, 0.0f ) );
	rotation =  Quaternion::Multiply( rotation, q );
}



//
// RotateLocalZ
// increases the rotation about the local( object orientation ) z axis, by angle degrees.
//
void Nixin::WorldObject::RotateGlobalZ( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 0.0f, 0.0f, 1.0f ) );
	rotation =  Quaternion::Multiply( rotation, q );
}



//
// RotateGlobalX
// Increases the rotation about the global x axis, by angle degrees.
//
void Nixin::WorldObject::RotateLocalX( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 1.0f, 0.0f, 0.0f ) );
	rotation =  Quaternion::Multiply( q, rotation );
}



//
// RotateGlobalY
// Increases the rotation about the global y axis, by angle degrees.
//
void Nixin::WorldObject::RotateLocalY( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 0.0f, 1.0f, 0.0f ) );
	rotation =  Quaternion::Multiply( q, rotation );
}



//
// RotateGlobalZ
// Increases the rotation about the global z axis, by angle degrees.
//
void Nixin::WorldObject::RotateLocalZ( const float angle )
{
	Quaternion q = Quaternion( angle, Point( 0.0f, 0.0f, 1.0f ) );
	rotation =  Quaternion::Multiply( q, rotation );
}



//
// GetPosition
//
Nixin::Point Nixin::WorldObject::GetPosition() const
{
	return position;
}



//
// SetPosition
//
void Nixin::WorldObject::SetPosition( const Point& newPosition )
{
	position = newPosition;
}



//
// GetRotation
//
Nixin::Quaternion Nixin::WorldObject::GetRotation() const
{
	return rotation;
}



//
// SetRotation
//
void Nixin::WorldObject::SetRotation( const Quaternion& newRotation )
{
	rotation = newRotation;
}