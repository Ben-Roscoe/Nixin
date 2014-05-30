#ifndef _NIXIN_CANVAS_H_
#define _NIXIN_CANVAS_H_


#include "Nixin_Vertex.h"
#include "Nixin_Point.h"
#include "Nixin_Colour.h"
#include "Nixin_ShaderProgram.h"
#include "Nixin_Camera.h"
#include "Nixin_Rectangle.h"
#include "Nixin_Font.h"
#include "Nixin_GLBuffer.h"
#include "Nixin_SpriteBuffer.h"

#include <vector>
#include <stack>
#include <memory>
#include <QOpenGLFunctions>


namespace Nixin
{



	class FrameBuffer;

	class Canvas
	{
		

    public:







		Camera								camera;


		
		Canvas( const Rectangle& viewportBounds, const Point& windowDimensions, const float totalDepth, const Camera::ProjectionType initialProjectionType );
		~Canvas();

		// Drawing methods.
		void								SetUpView();

		const Rectangle						GetBounds() const;
		void								SetBounds( const Rectangle& newBounds );
		Camera::ProjectionType				GetProjectionType() const;
		void								SetProjectionType( const Camera::ProjectionType newProjectionType );																																		// Not const as lights should be pushed / popped.
		void								EnableDepthTesting();
		void								DisableDepthTesting();
		void								EnableBackFaceCulling( const bool clockWise );
		void								DisableBackFaceCulling();
		void								EnableAlphaBlending();
		void								DisableAlphaBlending();
	
		SpriteDrawingMode					GetSpriteDrawingMode() const;
		void								SetSpriteDrawingMode( const SpriteDrawingMode newDrawingMode );

		void								BeginSpriteDrawing();
		void								BeginSpriteDrawing( ShaderProgram& customShader );
		void								DrawSprite( const Texture& texture, const Point& position, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Matrix& modelView, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Matrix& modelView, const Rectangle& sourceBounds, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Matrix& modelView, const Rectangle& sourceBounds, const Point& origin, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Point& position, const Colour& tint, const float rotation, const Point& origin );
		void								DrawSprite( const Texture& texture, const Point& position, const Colour& tint, const float rotation, const Point& scale, const Point& origin );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint, const float rotation, const Point& origin );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint, const float rotation, const Point& origin );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Colour& tint, const float rotation, const Point& scale, const Point& origin );
		void								DrawSprite( const Texture& texture, const Rectangle& spriteBounds, const Rectangle& sourceBounds, const Colour& tint, const float rotation, const Point& scale, const Point& origin );

		void								DrawString( const Font& font, const Point& position, const std::string& text, const Colour& tint );

		void								EndSpriteDrawing();


		// Buffer clearing.
		void								ClearBuffer( const bool colour, const bool depth, const bool stencil );
		void								SetClearColourValue( const Colour& value );
		void								SetClearDepthValue( const double value );
		void								SetClearStencilValue( const int value );
		const Colour&						GetClearColourValue() const;
		const double						GetClearDepthValue() const;
		const int							GetClearStencilValue() const;


		// Buffer masking.
		void								SetColourMaskValue( const Colour& value );
		void								SetDepthMaskValue( const bool value );
		void								SetStencilMaskValue( const unsigned int value );
		const Colour&						GetColourMaskValue() const;
		const bool							GetDepthMaskValue() const;
		const unsigned int					GetStencilMaskValue() const;


		// Deleted Methods.
		Canvas( const Canvas& other )				= delete;			// Prevent copying.
		Canvas& operator=( const Canvas& other )	= delete;


	private:




        OpenGLFunctions*                    gl                                  = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();

		Camera::ProjectionType				projectionType						= Camera::ProjectionType::ORTHO;
		Rectangle							bounds								= Rectangle( 0, 0, 640, 480 );
		Point								windowSize							= Point( 640, 480 );
		SpriteBuffer						spriteBuffer;

		// Clear values.
		Colour								clearColour							= Colour( 1.0f, 1.0f, 1.0f, 1.0f );
		double								clearDepth							= 0.0f;
		int									clearStencil						= 0;

		// Mask values.
		Colour								maskColour							= Colour( 0.0f, 0.0f, 0.0f, 0.0f );
		bool								maskDepth							= false;
		unsigned int						maskStencil							= 0;



	};
}



#endif
