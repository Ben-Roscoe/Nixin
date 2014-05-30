#ifndef _NIXIN_CAMERA_H_
#define _NIXIN_CAMERA_H_

#include "Nixin_Point.h"
#include "Nixin_Quaternion.h"
#include "Nixin_WorldObject.h"
#include "Nixin_Rectangle.h"
#include <stack>


namespace Nixin
{
	class ShaderProgram;

	class Camera : public WorldObject
	{


	public:



		//
		// ProjectionType
		// Specifies a projection type.
		//
		enum class ProjectionType
		{
			PERSPECTIVE,
			ORTHO,
		};


		Camera( const Point initialPosition, const float initialFieldOfView, const float initialDepthNear, const float initialDepthFar, const float initialAspect, const ProjectionType initialProjectionType, const Rectangle& viewportBounds );
		~Camera();

		void								SetPerspectiveProjection();
		void								SetOrthoProjection( const Rectangle& viewportBounds );
		void								SetView();

		float								GetFieldOfView() const;
		void								SetFieldOfView( const float newFieldOfView );
		float								GetDepthNear() const;
		void								SetDepthNear( const float newDepthNear );
		float								GetDepthFar() const;
		void								SetDepthFar( const float newDepthFar );
		float								GetAspect() const;
		void								SetAspect( const float newAspect );

		std::stack<Matrix>&					GetProjectionMatrixStack();
		std::stack<Matrix>&					GetModelMatrixStack();
		std::stack<Matrix>&					GetViewMatrixStack();

		// Matrix stuff
		void								PushModel();
		void								PopModel();
		void								PushProjection();
		void								PopProjection();
		void								PushView();
		void								PopView();
		void								MultiplyModel( const Matrix& matrix );
		void								MultiplyProjection( const Matrix& matrix );
		void								MultiplyView( const Matrix& matrix );
		void								ModelLoadIdentity();
		void								ProjectionLoadIdentity();
		void								ViewLoadIdentity();

		const Matrix&						GetModelMatrix() const;
		const Matrix&						GetViewMatrix() const;
		const Matrix&						GetProjectionMatrix() const;


	private:



		std::stack<Matrix>  			modelMatrixStack;
		std::stack<Matrix>  			viewMatrixStack;
		std::stack<Matrix>  			projectionMatrixStack;
		ProjectionType					projectionType				= ProjectionType::ORTHO;
		float							fieldOfView					= 0.0f;
		float							depthNear					= 0.0f;
		float							depthFar					= 0.0f;
		float							aspect						= 0.0f;

		Point							pan							= Point( 0, 0 );
		Point							orthographicRotation		= Point( 0, 0 );



	};
}


#endif

