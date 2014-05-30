#ifndef _NIXIN_WORLD_OBJECT_H_
#define _NIXIN_WORLD_OBJECT_H_


#include "Nixin_Point.h"
#include "Nixin_Quaternion.h"

namespace Nixin
{

	class WorldObject
	{



	public:



		WorldObject();
		~WorldObject();


		void							RotateGlobalX( const float angle );
		void							RotateGlobalY( const float angle );
		void							RotateGlobalZ( const float angle );

		void							RotateLocalX( const float angle );
		void							RotateLocalY( const float angle );
		void							RotateLocalZ( const float angle );

		void							MoveGlobalX( const float distance );
		void							MoveGlobalY( const float distance );
		void							MoveGlobalZ( const float distance );

		void							MoveForward( const float distance );
		void							MoveBackward( const float distance );
		void							MoveLeft( const float distance );
		void							MoveRight( const float distance );
		void							MoveUp( const float distance );
		void							MoveDown( const float distace );

		void							SetXRotation( const float newXRotation );
		void							SetYRotation( const float newYRotation );
		void							SetZRotation( const float newZRotation );
		void							SetXPosition( const float newXPosition );
		void							SetYPosition( const float newYPosition );
		void							SetZPosition( const float newZPosition );

		Point							GetPosition() const;
		void							SetPosition( const Point& newPosition );
		Quaternion						GetRotation() const;
		void							SetRotation( const Quaternion& newRotation );


	private:



		Point							position;
		Quaternion						rotation;



	};

}

#endif