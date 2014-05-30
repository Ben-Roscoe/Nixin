#include "Nixin_Canvas.h"
#include "Nixin_FrameBuffer.h"
#include "Nixin_Utility.h"
#include "Nixin_Math.h"
#include "Nixin_Debug.h"

#include <algorithm>
#include <exception>
#include <iostream>




// Public:



//
// Canvas
//
Nixin::Canvas::Canvas( const Rectangle& viewportBounds, const Point& windowDimensions, const float totalDepth, const Camera::ProjectionType initialProjectionType ) : camera( Point( 0, 0, 0 ), 60.0f, 0.1f, totalDepth, ( float )viewportBounds.width / ( float )viewportBounds.height, initialProjectionType, viewportBounds ), spriteBuffer{}
{
	bounds = Rectangle( viewportBounds );
	windowSize = windowDimensions;
	projectionType = initialProjectionType;


    gl->glViewport( ( int )bounds.x, ( int )bounds.y, ( GLsizei )bounds.width, ( GLsizei )bounds.height );

	// Default buffer clearing and masking.
	clearColour = Colour();
	clearDepth = 0.0;
	clearStencil = 0;
	maskColour = Colour();
	maskDepth = false;
	maskStencil = 0;

    gl->glEnable( GL_SCISSOR_TEST );
}



//
// ~Canvas
//
Nixin::Canvas::~Canvas()
{
}



//
// SetUpView
//
void Nixin::Canvas::SetUpView()
{
	// Make sure we're only drawing to this viewport.

	// Set up projection matrix.
	camera.GetProjectionMatrixStack().top().LoadIdentity();
	// Set up the projection based on the projection type of this canvas.
	projectionType == Camera::ProjectionType::PERSPECTIVE ? camera.SetPerspectiveProjection() : camera.SetOrthoProjection( bounds );

	// Set up model view matrix.
	camera.ModelLoadIdentity();
	camera.ViewLoadIdentity();
	// Set up the model view based on the type of projection.

	if( projectionType == Camera::ProjectionType::PERSPECTIVE )
	{
        camera.SetView();
    }
}



//
// BeginSpriteDrawing
// Normal sprite setup, however with a custom shader. This method relies on the user writing a shader
// which is a superset of the deafult.
//
void Nixin::Canvas::BeginSpriteDrawing( ShaderProgram& customShader )
{
	spriteBuffer.Begin( customShader );

    gl->glViewport( ( int )bounds.x, ( int )bounds.y, ( int )bounds.width, ( int )bounds.height );
}



//
// BeginSpriteDrawing
//
void Nixin::Canvas::BeginSpriteDrawing()
{
	spriteBuffer.Begin( Utility::GetNixinSpriteShader() );

    gl->glViewport( ( int )bounds.x, ( int )bounds.y, ( int )bounds.width, ( int )bounds.height );
}



//
// DrawSprite
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Point& position, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, Rectangle( position.x, position.y, texture.GetWidth(), texture.GetHeight() ), Point( 1, 1 ), 0, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), Point( 0, 0 ), false );
}



//
// DrawSprite
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, spriteBounds, Point( 1, 1 ), 0, tint, sourceBounds, Point( 0, 0 ), false );
}



//
// DrawSprite
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Point& position, const Colour& tint, const float rotation, const Point& scale, const Point& origin )
{
	spriteBuffer.BufferSprite( texture, Rectangle( position.x, position.y, texture.GetWidth(), texture.GetHeight() ), scale, rotation, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), origin, false );
}



//
// DrawSprite
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, spriteBounds, Point( 1, 1 ), 0, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), Point( 0, 0 ), false );
}



//
// DrawSprite
// Buffers a sprite that is first multiplied by modelView. A source sub-image can be defined.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Matrix& modelView, const Rectangle& sourceBounds, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, Rectangle( 0, 0, sourceBounds.width, sourceBounds.height ), Point( 1, 1 ), 0, tint, sourceBounds, Point( 0, 0 ), true, modelView );
}



//
// DrawSprite
// Buffers a sprite that is first multiplied by modelViw. A source sub-image and origin can be defined.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Matrix& modelView, const Rectangle& sourceBounds, const Point& origin, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, Rectangle( 0, 0, sourceBounds.width, sourceBounds.height ), Point( 1, 1 ), 0, tint, sourceBounds, origin, true, modelView );
}


//
// DrawSprite
// Draws a sprite that is first multiplied by modelView.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Matrix& modelView, const Colour& tint )
{
	spriteBuffer.BufferSprite( texture, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), Point( 1, 1 ), 0, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), Point( 0, 0 ), true, modelView );
}



//
// DrawSprite
// Draws a sprite at texture size. Draws the entire texture.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Point& position, const Colour& tint, const float rotation, const Point& origin )
{
	spriteBuffer.BufferSprite( texture, Rectangle( position, texture.GetWidth(), texture.GetHeight() ), Point( 1, 1 ), rotation, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), origin, false );
}



//
// DrawSprite
// Draws a sprite which can be scaled in both the x and y axis.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint, const float rotation, const Point& origin )
{
	spriteBuffer.BufferSprite( texture, spriteBounds, Point( 1, 1 ), rotation, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), origin, false );
}



//
// DrawSprite
// Draws a sprite that can be scaled, and a sorce rectangle can define the texture coordinates area.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint, const float rotation, const Point& origin )
{
	spriteBuffer.BufferSprite( texture, spriteBounds, Point( 1, 1 ), rotation, tint, sourceBounds, origin, false );
}



//
// DrawSprite
// Buffers a sprite with a scale.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint, const float rotation, const Point& scale, const Point& origin)
{
	spriteBuffer.BufferSprite( texture, spriteBounds, scale, rotation, tint, Rectangle( 0, 0, texture.GetWidth(), texture.GetHeight() ), origin, false );
}



//
// DrawSprite
// Buffers a sprite with a scale. A source rectangle can define texture coordinates.
//
void Nixin::Canvas::DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint, const float rotation, const Point& scale, const Point& origin )
{
	spriteBuffer.BufferSprite( texture, spriteBounds, scale, rotation, tint, sourceBounds, origin, false );
}



//
// DrawString
// Draws a string from an Font at position.
//
void Nixin::Canvas::DrawString( const Font& font, const Point& position, const std::string& text, const Colour& tint )
{
	// Store the current position of the character on the screen.
	Point										currentPosition = position;

	// For each character in the given string.
	for( char character : text )
	{
		Rectangle								characterBounds = font.GetCharacterBounds( character );				// Get the character bounds.

		// If it's a space, we just increase the current position along the x axis.
		if( character == ' ' )
		{
			currentPosition.x += font.GetSpacing().x;
			currentPosition.x += font.GetCharacterPadding().x;
		}
		// If it's a new line, we reset the current x position, and decrease the y position by the font spacing.
		else if( character == '\n' )					
		{
			currentPosition.y -= characterBounds.height;
			currentPosition.y -= font.GetSpacing().x;
			currentPosition.y -= font.GetCharacterPadding().y;
			currentPosition.x = position.x;
		}
		// If it's just a normal character, we draw it like any other sprite and add spacing and it's dimensions to the current width.
		else											
		{
			spriteBuffer.BufferSprite( font.GetCharacterBitmap(), Rectangle( currentPosition, characterBounds.width, characterBounds.height ), Point( 1, 1 ), 0, tint, characterBounds, Point( 0, 0 ), false );
			currentPosition.x += characterBounds.width;
			currentPosition.x += font.GetCharacterPadding().x;
		}
	}
}



//
// EndSpriteDrawing
// Takes all the buffered sprites and draws them.
//
void Nixin::Canvas::EndSpriteDrawing()
{
    gl->glScissor( bounds.x, bounds.y, bounds.width, bounds.height );

	spriteBuffer.End( *this );
}



//
// GetBounds
// Gets the canvas bounds.
//
const Nixin::Rectangle Nixin::Canvas::GetBounds() const
{
	return bounds;
}



//
// SetBounds
// Sets the new canvas bounds, and also sets a new glViewport.
//
void Nixin::Canvas::SetBounds( const Rectangle& newBounds )
{
	if( newBounds.width < 0 || newBounds.height < 0 )
	{
		bounds = Rectangle( newBounds.x, newBounds.y, 0, 0 );
        gl->glViewport( ( GLsizei )newBounds.x, ( GLsizei )newBounds.y, 0, 0 );
	}
	else
	{
		bounds = newBounds;
        gl->glViewport( ( GLsizei )newBounds.x, ( GLsizei )newBounds.y, ( GLsizei )newBounds.width, ( GLsizei )newBounds.height );
	}
}



//
// GetProjectionType
//
Nixin::Camera::ProjectionType Nixin::Canvas::GetProjectionType() const
{
	return projectionType;
}



//
// SetProjectionType
//
void Nixin::Canvas::SetProjectionType( const Camera::ProjectionType newProjectionType )
{
	if( projectionType == newProjectionType )
	{
		return;
	}
	projectionType = newProjectionType;

	camera.GetProjectionMatrixStack().top().LoadIdentity();

	if( projectionType == Camera::ProjectionType::PERSPECTIVE )
	{
		camera.SetPerspectiveProjection();
	}
	else
	{
		camera.SetOrthoProjection( bounds );
	}

	// Set up model view matrix.
	camera.ModelLoadIdentity();
	camera.ViewLoadIdentity();

	camera.SetView();
}



//
// EnableDepthTesting
//
void Nixin::Canvas::EnableDepthTesting()
{
    gl->glEnable( GL_DEPTH_TEST );
}



//
// DisableDepthTesting
//
void Nixin::Canvas::DisableDepthTesting()
{
    gl->glDisable( GL_DEPTH_TEST );
}



//
// EnableBackFaceCulling
//
void Nixin::Canvas::EnableBackFaceCulling( const bool clockWise )
{
    gl->glFrontFace( clockWise ? GL_CW : GL_CCW );
    gl->glEnable( GL_CULL_FACE );
}



//
// DisableBackFaceCulling
//
void Nixin::Canvas::DisableBackFaceCulling()
{
    gl->glDisable( GL_CULL_FACE );
}



//
// GetSpriteDrawingMode
//
Nixin::SpriteDrawingMode Nixin::Canvas::GetSpriteDrawingMode() const
{
	return spriteBuffer.GetSpriteDrawingMode();
}



//
// SetSpriteDrawingMode
//
void Nixin::Canvas::SetSpriteDrawingMode( const SpriteDrawingMode newDrawingMode )
{
	spriteBuffer.SetSpriteDrawingMode( newDrawingMode );
}



// Private:



//
// ClearBuffer
// Clears the screen buffer.
void Nixin::Canvas::ClearBuffer( const bool colour, const bool depth, const bool stencil )
{
    gl->glScissor( bounds.x, bounds.y, bounds.width, bounds.height );
    gl->glClear( GL_COLOR_BUFFER_BIT * ( colour ? 1 : 0 ) | GL_DEPTH_BUFFER_BIT * ( depth ? 1 : 0 ) | GL_STENCIL_BUFFER_BIT * ( stencil ? 1 : 0 ) );
    gl->glScissor( 0, 0, windowSize.x, windowSize.y );
}



//
// SetClearColourValue
// Sets the "clear" value of the colour buffer.
//
void Nixin::Canvas::SetClearColourValue( const Colour& value )
{
    gl->glClearColor( value.r, value.g, value.b, value.a );
	clearColour = value;
}



//
// SetClearDepthValue
// Sets the "clear" value of the depth buffer. 
//
void Nixin::Canvas::SetClearDepthValue( const double value )
{
    gl->glClearDepthf( value );
	clearDepth = value;
}



//
// SetClearStencilValue
// Sets the "clear" value for the stencil buffer.
//
void Nixin::Canvas::SetClearStencilValue( const int value )
{
    gl->glClearStencil( value );
	clearStencil = value;
}




//
// GetClearColourValue
//
const Nixin::Colour& Nixin::Canvas::GetClearColourValue() const
{
	return clearColour;
}



//
// GetClearDepthValue
//
const double Nixin::Canvas::GetClearDepthValue() const
{
	return clearDepth;
}



//
// GetClearStencilValue
//
const int Nixin::Canvas::GetClearStencilValue() const
{
	return clearStencil;
}



//
// SetColourMaskValue
//
void Nixin::Canvas::SetColourMaskValue( const Colour& value )
{
    gl->glColorMask( value.r < 0.1f, value.g < 0.1f, value.b < 0.1f, value.a < 0.1f );
	maskColour = value;
}



//
// SetDepthMaskValue
//
void Nixin::Canvas::SetDepthMaskValue( const bool value )
{
    gl->glDepthMask( value );
	maskDepth = value;
}



//
// SetStencilMaskValue
//
void Nixin::Canvas::SetStencilMaskValue( const unsigned int value )
{
    gl->glStencilMask( value );
	maskStencil = value;
}



//
// GetColourMaskValue
//
const Nixin::Colour& Nixin::Canvas::GetColourMaskValue() const
{
	return maskColour;
}



//
// GetDepthMaskValue
//
const bool Nixin::Canvas::GetDepthMaskValue() const
{
	return maskDepth;
}



//
// GetStencilMaskValue
//
const unsigned int Nixin::Canvas::GetStencilMaskValue() const
{
	return maskStencil;
}



//
// EnableAlphaTesting
//
void Nixin::Canvas::EnableAlphaBlending()
{
    gl->glEnable( GL_BLEND );
    gl->glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}



//
// DisableAlphaTesting
//
void Nixin::Canvas::DisableAlphaBlending()
{
    gl->glDisable( GL_BLEND );
}

