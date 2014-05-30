#ifndef _NIXIN_VERTEX_H_
#define _NIXIN_VERTEX_H_

#include "Nixin_Point.h"
#include "Nixin_Colour.h"


namespace Nixin
{

	struct VertexPosition
	{

		VertexPosition()
		{
		}
		VertexPosition( const Point& spacePosition )
		{
			position = spacePosition;
		}


		Point						position		= Point( 0, 0, 0 );
	};
	struct VertexPositionColour : VertexPosition
	{
		VertexPositionColour()
		{
		}
		VertexPositionColour( const Point& spacePosition, const Colour& vertexColour ) : VertexPosition( spacePosition )
		{
			colour = vertexColour;
		}

		Colour						colour			= Colour( 1.0f, 1.0f, 1.0f, 1.0f );
	};
	struct VertexPositionTexCoord : VertexPosition
	{
		VertexPositionTexCoord()
		{
		}
		VertexPositionTexCoord( const Point& spacePosition, const Point& vertexTexCoord ) : VertexPosition( spacePosition )
		{
			texCoord = vertexTexCoord;
		}

		Point						texCoord		= Point( 0, 0 );
	};

}



#endif