#include "Nixin_Camera.h"
#include "Nixin_Math.h"
#include "Nixin_Canvas.h"
#include "Nixin_Matrix.h"
#include "Nixin_ShaderProgram.h"
#include "Nixin_Quaternion.h"


// Public:



//
// Camera
//
Nixin::Camera::Camera( const Point initialPosition, const float initialFieldOfView, const float initialDepthNear, const float initialDepthFar, const float initialAspect, const Camera::ProjectionType initialProjectionType, const Rectangle& viewportBounds )
{
	SetPosition( initialPosition );
	fieldOfView = initialFieldOfView;
	depthNear = initialDepthNear;
	depthFar = initialDepthFar;
	aspect = initialAspect;
	projectionType = ProjectionType::PERSPECTIVE;

	if( initialProjectionType == ProjectionType::PERSPECTIVE )
	{
		projectionMatrixStack.push( Matrix::CreatePerspectiveMatrix( 60.0f, initialAspect, 0.01f, 10000 ) );
	}
	else
	{
		projectionMatrixStack.push( Matrix::CreateOthroMatrix( depthNear, depthFar, 0, viewportBounds.width, viewportBounds.height, 0 ) );
	}
	modelMatrixStack.push( Matrix() );
	modelMatrixStack.top().LoadIdentity();
	viewMatrixStack.push( Matrix() );
	viewMatrixStack.top().LoadIdentity();
}



//
// ~Camera
//
Nixin::Camera::~Camera()
{
}



//
// SetOrthoProjection
//
void Nixin::Camera::SetPerspectiveProjection()
{
	projectionMatrixStack.top() = Matrix::CreatePerspectiveMatrix( fieldOfView, aspect, depthNear, depthFar );
}



//
// SetOrthoProjection
//
void Nixin::Camera::SetOrthoProjection( const Rectangle& viewportBounds )
{
	projectionMatrixStack.top() = Matrix::CreateOthroMatrix( depthNear, depthFar, 0, viewportBounds.width, viewportBounds.height, 0 );
}



//
// Set3DView
//
void Nixin::Camera::SetView()
{
	viewMatrixStack.top() = viewMatrixStack.top() * GetRotation().ToMatrix();
	viewMatrixStack.top() = Matrix::Multiply( viewMatrixStack.top(), Matrix::CreateTranslationMatrix( Point( -GetPosition().x, -GetPosition().y, -GetPosition().z ) ) );
}



//
// GetFieldOfView
//
float Nixin::Camera::GetFieldOfView() const
{
	return fieldOfView;
}



//
// SetFieldOfView
//
void Nixin::Camera::SetFieldOfView( const float newFieldOfView )
{
	fieldOfView = newFieldOfView;
}



//
// GetDepthNear
//
float Nixin::Camera::GetDepthNear() const
{
	return depthNear;
}



//
// SetDepthNear
//
void Nixin::Camera::SetDepthNear( const float newDepthNear )
{
	depthNear = newDepthNear;
}



//
// GetDepthFar
//
float Nixin::Camera::GetDepthFar() const
{
	return depthFar;
}



//
// SetDepthFar
//
void Nixin::Camera::SetDepthFar( const float newDepthFar )
{
	depthFar = newDepthFar;
}



//
// GetAspect
//
float Nixin::Camera::GetAspect() const
{
	return aspect;
}



//
// SetAspect
//
void Nixin::Camera::SetAspect( const float newAspect )
{
	aspect = newAspect;
}



//
// GetProjectionMatrix
//
std::stack<Nixin::Matrix>& Nixin::Camera::GetProjectionMatrixStack()
{
	return projectionMatrixStack;
}



//
// GetViewMatrix
//
std::stack<Nixin::Matrix>& Nixin::Camera::GetModelMatrixStack()
{
	return modelMatrixStack;
}



//
// GetViewMatrixStack
//
std::stack<Nixin::Matrix>& Nixin::Camera::GetViewMatrixStack()
{
	return viewMatrixStack;
}




//
// PushModelView
//
void Nixin::Camera::PushModel()
{
	GetModelMatrixStack().push( GetModelMatrixStack().top() );
}



//
// PopModelView
//
void Nixin::Camera::PopModel()
{
	GetModelMatrixStack().pop();
}



//
// PushProjection
//
void Nixin::Camera::PushProjection()
{
	GetProjectionMatrixStack().push( GetProjectionMatrixStack().top() );
}



//
// PopProjection
//
void Nixin::Camera::PopProjection()
{
	GetProjectionMatrixStack().pop();
}



//
// PushView
//
void Nixin::Camera::PushView()
{
	GetViewMatrixStack().push( GetViewMatrixStack().top() );
}



//
// PopView
//
void Nixin::Camera::PopView()
{
	GetViewMatrixStack().pop();
}



//
// MultiplyModelView
//
void Nixin::Camera::MultiplyModel( const Matrix& matrix )
{
	GetModelMatrixStack().top() = GetModelMatrixStack().top() * matrix;
}



//
// MultiplyProjection
//
void Nixin::Camera::MultiplyProjection( const Matrix& matrix )
{
	GetProjectionMatrixStack().top() = GetProjectionMatrixStack().top() * matrix;
}



//
// MultiplyView
//
void Nixin::Camera::MultiplyView( const Matrix& matrix )
{
	GetViewMatrixStack().top() = GetViewMatrixStack().top() * matrix;
}



//
// ModelViewLoadIdentity
//
void Nixin::Camera::ModelLoadIdentity()
{
	GetModelMatrixStack().top().LoadIdentity();
}



//
// ProjectionLoadIdentity
//
void Nixin::Camera::ProjectionLoadIdentity()
{
	GetProjectionMatrixStack().top().LoadIdentity();
}



//
// ViewLoadIdentity
//
void Nixin::Camera::ViewLoadIdentity()
{
	GetViewMatrixStack().top().LoadIdentity();
}



//
// GetModelMatrix
//
const Nixin::Matrix& Nixin::Camera::GetModelMatrix() const
{
	return modelMatrixStack.top();
}



//
// GetModelMatrix
//
const Nixin::Matrix& Nixin::Camera::GetViewMatrix() const
{
	return viewMatrixStack.top();
}



//
// GetModelMatrix
//
const Nixin::Matrix& Nixin::Camera::GetProjectionMatrix() const
{
	return projectionMatrixStack.top();
}
