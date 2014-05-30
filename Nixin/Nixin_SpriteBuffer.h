#ifndef _NIXIN_SPRITEBUFFER_H_
#define _NIXIN_SPRITEBUFFER_H_


#include "Nixin_Rectangle.h"
#include "Nixin_GLBuffer.h"
#include "Nixin_Texture.h"
#include "Nixin_ShaderProgram.h"
#include "Nixin_Types.h"

#include <QOpenGLFunctions_4_3_Core>

namespace Nixin
{	



	//
	// SpriteObject
	// Holds information about a sprite.
	//
	struct SpriteObject
	{
		unsigned int						texture;
		int									index;


		inline SpriteObject( unsigned int textureID, int spriteIndex )
		{
			texture = textureID;
			index	= spriteIndex; 
		}
	};



	//
	// SpriteDrawingMode
	// Defines how the sprites are drawn once they have been sorted.
	//
	enum class SpriteDrawingMode
	{
		NO_DEPTH,
		DEPTH_TESTED,
	};



	//
	// SpriteSortMode
	// Defines how the sprite buffer is sorted.
	//
	enum class SpriteSortMode
	{
		TEXTURE,
		NO_SORTING,
	};



	class SpriteBuffer
	{
			


	public:


		SpriteBuffer( const unsigned int initialMaxSpriteCount = 1024 );

		void								Begin( ShaderProgram& spriteShader );
		void								End( Canvas& canvas );


		void								Grow( const float multiplier );
		void								OrderIndices();
		void								SortSprites();
		void								BufferSprite( const Texture& texture, const Rectangle& spriteBounds, const Point& scale, const float rotation, const Colour& tint, const Rectangle& sourceBounds, const Point& origin, const bool matrix, const Matrix& inModelView = Matrix() );
		bool								CheckSpriteBufferSize();

		SpriteDrawingMode					GetSpriteDrawingMode() const
		{ 
			return drawingMode; 
        };
		void								SetSpriteDrawingMode( const SpriteDrawingMode newDrawinMode )
		{ 
			drawingMode = newDrawinMode; 
        };



	private:



		static const int					verticesPerSprite					= 4;
		static const int					indicesPerSprite					= 6;
		static const int					initialSpriteBufferSize				= 2048;



        OpenGLFunctions*                    gl                                  = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
		ShaderProgram*						shader;
        GLBuffer                            spriteIndexBuffer;
        GLBuffer                            spriteDataBuffer;
		float*								mappedData;

		int									maxSpriteCount;
		std::vector<SpriteObject>			sprites;
		Matrix								modelView;							// This will hold each sprites model view matrices, one at a time.

		bool								growNextEnd;						// Flags if the buffer needs to grow the next time EndSpriteDrawing is called.
		SpriteDrawingMode					drawingMode;
		SpriteSortMode						spriteSortMode;						// Determines the way the sprites are sorted.

		bool								hasBegun;



	};

}


#endif
