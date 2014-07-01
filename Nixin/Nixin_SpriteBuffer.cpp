#include <cmath>
#include <algorithm>

#include "Nixin_SpriteBuffer.h"
#include "Nixin_Canvas.h"
#include "Nixin_Math.h"




//
// SpriteBuffer
//
Nixin::SpriteBuffer::SpriteBuffer( const unsigned int initialMaxSpriteCount ) : spriteIndexBuffer( GL_ELEMENT_ARRAY_BUFFER, GL_STREAM_COPY, sizeof( unsigned int ) * 6 * initialMaxSpriteCount ), spriteDataBuffer( GL_ARRAY_BUFFER, GL_STREAM_COPY, sizeof( float ) * 36 * initialMaxSpriteCount )
{
	maxSpriteCount = initialMaxSpriteCount;
	growNextEnd = false;
	hasBegun	= false;
	modelView = Matrix();
	modelView.LoadIdentity();
	drawingMode = SpriteDrawingMode::NO_DEPTH;
	spriteSortMode = SpriteSortMode::NO_SORTING;
	
    // Set up the index buffer. Since all sprites are two triangles, we can buffer the index data now.
	std::vector<unsigned int>				indexData;
	indexData.reserve( maxSpriteCount * indicesPerSprite );

	// Work out the index data.
	for( int i = 0; i < maxSpriteCount; i++ )
	{
		indexData.push_back( i * verticesPerSprite );
		indexData.push_back( i * verticesPerSprite + 3 );
		indexData.push_back( i * verticesPerSprite + 2 );
		indexData.push_back( i * verticesPerSprite );
		indexData.push_back( i * verticesPerSprite + 1 );
		indexData.push_back( i * verticesPerSprite + 3 );
	}
	
	// Give the data to opengl.
    spriteIndexBuffer.SetData( GL_ELEMENT_ARRAY_BUFFER, maxSpriteCount * indicesPerSprite * sizeof( unsigned int ), indexData.data() );
}



//
// Grow
//
void Nixin::SpriteBuffer::Grow( const float multiplier )
{
	maxSpriteCount *= multiplier;

	std::vector<unsigned int>				indexData;
	indexData.reserve( maxSpriteCount * indicesPerSprite );

	// Work out the index data.
	for( int i = 0; i < maxSpriteCount; i++ )
	{
		indexData.push_back( i * verticesPerSprite );
		indexData.push_back( i * verticesPerSprite + 3 );
		indexData.push_back( i * verticesPerSprite + 2 );
		indexData.push_back( i * verticesPerSprite );
		indexData.push_back( i * verticesPerSprite + 1 );
		indexData.push_back( i * verticesPerSprite + 3 );
	}

	// Give the data to opengl.
    spriteIndexBuffer.Bind( GL_ELEMENT_ARRAY_BUFFER );
    spriteIndexBuffer.SetData( GL_ELEMENT_ARRAY_BUFFER, maxSpriteCount * indicesPerSprite * sizeof( unsigned int ), indexData.data() );
    spriteDataBuffer.SetData( GL_ARRAY_BUFFER, sizeof( float ) * 36 * maxSpriteCount );
}



//
// SortSprites
// Sorts the sprites based on the sprite buffer's sort mode.
//
void Nixin::SpriteBuffer::SortSprites()
{
	switch( spriteSortMode )
	{
		case SpriteSortMode::TEXTURE:
		{
			std::sort( sprites.begin(), sprites.end(), []( const SpriteObject& a, const SpriteObject& b ) -> bool { return a.texture > b.texture; } );
		}
	}
}



//
// OrderIndices
// Reorder indices after the sprite buffer has been sorted.
//
void Nixin::SpriteBuffer::OrderIndices()
{
	std::vector<unsigned int>		newIndices;
	newIndices.reserve( sprites.size() * indicesPerSprite );

	// Order the indices so that they match up to our sprite object vector. This simplifies drawing later.
	for( unsigned int i = 0; i < sprites.size(); i++ )
	{
		newIndices.push_back( sprites[i].index * verticesPerSprite );
		newIndices.push_back( sprites[i].index * verticesPerSprite + 2 );
		newIndices.push_back( sprites[i].index * verticesPerSprite + 3 );
		newIndices.push_back( sprites[i].index * verticesPerSprite );
		newIndices.push_back( sprites[i].index * verticesPerSprite + 3 );
		newIndices.push_back( sprites[i].index * verticesPerSprite + 1 );
	}
	
	// Rebuffer to buffer object.
    spriteIndexBuffer.SetData( GL_ELEMENT_ARRAY_BUFFER, sprites.size() * indicesPerSprite * sizeof( unsigned int ), newIndices.data() );
}



//
// BufferSprite
// Transforms a sprite, and defines the texture source. Once this is done, the sprite is buffered and is ready for drawing.
//
void Nixin::SpriteBuffer::BufferSprite( const Texture& texture, const Rectangle& spriteBounds, const Point& scale, const float rotation, const Colour& tint, const Rectangle& sourceBounds, const Point& origin, const bool matrix, const Matrix& inModelView )
{
	Point v1;
	Point v2;
	Point v3;
	Point v4;

	if( !hasBegun )
	{
		Debug::FatalError( "Begin must be called before drawing a sprite." );
	}

	// Check if we have reached the current sprite max. If so, wait for the end of the frame to draw them.
	// This is a compromise. We can't increase the sprite max mid-frame as that would clear all the currently
	// buffered sprites, so we just avoid drawing them until next frame.
	if( CheckSpriteBufferSize() )
	{
		if( !matrix )
		{
			float							cosz			= cos( ToRadians( rotation ) );
			float							sinz			= sin( ToRadians( rotation ) );
			modelView.SetDataAt( 0, 0, cosz * scale.x );
			modelView.SetDataAt( 0, 1, -sinz * scale.x );
			modelView.SetDataAt( 0, 3, spriteBounds.x );

			modelView.SetDataAt( 1, 0, sinz * scale.y );
			modelView.SetDataAt( 1, 1, cosz * scale.y );
			modelView.SetDataAt( 1, 3, spriteBounds.y );
			
			modelView.SetDataAt( 2, 0, 0 );
			modelView.SetDataAt( 2, 1, 0 );
			modelView.SetDataAt( 2, 3, 1.0f );

			v1 = Point::Multiply( Point( -origin.x, -origin.y, 1.0f ), modelView );
			v2 = Point::Multiply( Point( spriteBounds.width - origin.x, -origin.y, 1.0f ), modelView );
			v3 = Point::Multiply( Point( -origin.x, spriteBounds.height - origin.y, 1.0f ), modelView );
			v4 = Point::Multiply( Point( spriteBounds.width - origin.x, spriteBounds.height - origin.y, 1.0f ), modelView );
		}
		else
		{
			v1 = Point::Multiply( Point( -origin.x, -origin.y, origin.z ), inModelView );
			v2 = Point::Multiply( Point( spriteBounds.width - origin.x, -origin.y, origin.z ), inModelView );
			v3 = Point::Multiply( Point( -origin.x, spriteBounds.height -origin.y, origin.z ), inModelView );
			v4 = Point::Multiply( Point( spriteBounds.width - origin.x, spriteBounds.height - origin.y, origin.z ), inModelView );
		}

		// Copy the vertex data into it's location in the mapped data pointer.
		int				offset = sprites.size() * 12;
		mappedData[offset] = v1.x + origin.x;
		mappedData[offset + 1] = v1.y + origin.y;
		mappedData[offset + 2] = v1.z + origin.z;
		mappedData[offset + 3] = v2.x + origin.x;
		mappedData[offset + 4] = v2.y + origin.y;
		mappedData[offset + 5] = v2.z + origin.z;
		mappedData[offset + 6] = v3.x + origin.x;																				
		mappedData[offset + 7] = v3.y + origin.y;
		mappedData[offset + 8] = v3.z + origin.z;
		mappedData[offset + 9] = v4.x + origin.x;
		mappedData[offset + 10] = v4.y + origin.y;
		mappedData[offset + 11] = v4.z + origin.z;

		// Do the same for the texture coordinates. Here we add the max sprite count * 8, because the texture coordinate
		// data is stored after all the vertex data.
		offset = sprites.size() * 8 + ( maxSpriteCount ) * 12;
		mappedData[offset] =	  sourceBounds.x / texture.GetWidth();					
		mappedData[offset + 1] = ( sourceBounds.height + sourceBounds.y ) / texture.GetHeight();
		mappedData[offset + 2] = ( sourceBounds.width + sourceBounds.x ) / texture.GetWidth(); 
		mappedData[offset + 3] = ( sourceBounds.height + sourceBounds.y ) / texture.GetHeight();
		mappedData[offset + 4] = sourceBounds.x / texture.GetWidth(); 						// Texture coordinates are defined by the triangle( srcPosition, srcSize )
		mappedData[offset + 5] = sourceBounds.y / texture.GetHeight();
		mappedData[offset + 6] = ( sourceBounds.width + sourceBounds.x ) / texture.GetWidth();
		mappedData[offset + 7] = sourceBounds.y / texture.GetHeight();

		// Save the sprite's colour.
		offset = sprites.size() * 16 + ( maxSpriteCount ) * 20;
		mappedData[offset]		= tint.r;
		mappedData[offset + 1]	= tint.g;
		mappedData[offset + 2]	= tint.b;
		mappedData[offset + 3]	= tint.a;
		mappedData[offset + 4]	= tint.r;
		mappedData[offset + 5]	= tint.g;
		mappedData[offset + 6]	= tint.b;
		mappedData[offset + 7]	= tint.a;
		mappedData[offset + 8]	= tint.r;
		mappedData[offset + 9]	= tint.g;
		mappedData[offset + 10]	= tint.b;
		mappedData[offset + 11]	= tint.a;
		mappedData[offset + 12]	= tint.r;
		mappedData[offset + 13]	= tint.g;
		mappedData[offset + 14]	= tint.b;
		mappedData[offset + 15]	= tint.a;

		// Add the sprite object.
		sprites.emplace_back( texture.GetID(), sprites.size() );
	}
}



//
// CheckSpriteBufferSize
// Check if we need to grow the sprite buffer. If so, return false to indicate that no more sprites can be added to
// the buffer this frame, and will have to wait until the next frame to be drawn.
//
bool Nixin::SpriteBuffer::CheckSpriteBufferSize()
{
	// If we've reached the sprite limit, then flag that we need to grow the buffer at then end of the frame.
	// Also, don't draw any sprite between now and the end of the frame.
	if( sprites.size() >= maxSpriteCount - 1 )
	{
		growNextEnd = true;
		return false;
	}
	return true;
}




//
// Begin
// Sets up the buffer for drawing.
//
void Nixin::SpriteBuffer::Begin( ShaderProgram& spriteShader )
{
	// Check that two begins have not been called without an end.
	if( hasBegun )
	{
		Debug::FatalError( "Begin was called twice before an end." );
	}
	hasBegun = true;
	shader = &spriteShader;

    spriteDataBuffer.Bind( GL_ARRAY_BUFFER );
    spriteIndexBuffer.Bind( GL_ELEMENT_ARRAY_BUFFER );

	// Bind the sprite buffer.
    mappedData = static_cast<float*>( spriteDataBuffer.Map( GL_ARRAY_BUFFER, GL_READ_WRITE ) );
}



//
// End
//
void Nixin::SpriteBuffer::End( Canvas& canvas )
{
	// Check for validity of end call.
	if( !hasBegun )
	{
		Debug::FatalError( "End was called before begin." );
	}


	// Unmap the buffer data pointer, because we're about to draw with it.
    spriteDataBuffer.Unmap( GL_ARRAY_BUFFER );

	// Use custom shader.
    gl->glUseProgram( shader->GetID() );

	// Set the projection matrix, and vertex attributes in the shader.
    shader->SetUniform( "projection", UniformMatrix( canvas.camera.GetProjectionMatrix() ) );
    shader->SetAttribute( "vertexPosition", 3, GL_FALSE, GL_FLOAT, 0, 0 );
    shader->SetAttribute( "texCoords", 2, GL_FALSE, GL_FLOAT, 0, 12 * maxSpriteCount * sizeof( float ) );
    shader->SetAttribute( "tint", 4, GL_FALSE, GL_FLOAT, 0, 20 * maxSpriteCount * sizeof( float ) );

	// Sort sprites.
	if( spriteSortMode != SpriteSortMode::NO_SORTING )
	{
		// Prepared for drawing.
		SortSprites();
		OrderIndices();
	}

	if( drawingMode == SpriteDrawingMode::DEPTH_TESTED )
	{
		canvas.EnableDepthTesting();
	}

	// This will be the total number of sprites draw.
	int	count = 0;
	// While we haven't drawn all the sprites.
	while( count < sprites.size() )			
	{
		// We assume that at least one sprite is going to be drawn this loop.
		int				drawCount = 1;					

		// Set the texture sampler.
        shader->SetUniform<UniformSampler2D>( "spriteTexture", UniformSampler2D( sprites[count].texture, GL_TEXTURE0, false ) );

		// We step through the buffer, looking for a change in texture. If we find one, then take all the sprites that are next to each, that also have the same texture.
		for( int i = count + 1; i < sprites.size(); i++ )
		{
			if( sprites[count].texture == sprites[i].texture )
			{
				drawCount++;
			}
			else
			{
				break;
			}
		}

		// Finally, draw this group of sprites.
        gl->glDrawRangeElements( GL_TRIANGLES, NULL + count  * indicesPerSprite * sizeof( unsigned int ), NULL + count  * indicesPerSprite * sizeof( unsigned int ) + indicesPerSprite * drawCount, indicesPerSprite * drawCount, GL_UNSIGNED_INT, ( GLvoid* )( NULL + count  * indicesPerSprite * sizeof( unsigned int ) ) );

		// Increase the number of sprites drawn.
		count += drawCount;
	} 
	if( drawingMode == SpriteDrawingMode::DEPTH_TESTED )
	{
		canvas.DisableDepthTesting();
	}

	// Check if the sprite buffer needs to grow.
	if( growNextEnd )
	{
		Grow( 2.0f );

		// Set this to false, as the growing is complete.
		growNextEnd = false;
	}
	else
	{
		//glInvalidateBufferData( spriteBuffer->spriteDataBufferLocation );
        spriteDataBuffer.SetData( GL_ARRAY_BUFFER, sizeof( float ) * 36 * maxSpriteCount );
	}

	// Clear the sprite list.
	sprites.clear();

	// No longer drawing.
	hasBegun = false;
}
