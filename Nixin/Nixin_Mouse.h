#ifndef _NIXIN_MOUSE_H_
#define _NIXIN_MOUSE_H_

#include "Nixin_Point.h"
#include "Nixin_Canvas.h"



namespace Nixin
{

    class GameWindow;

	class Mouse
	{



	public:



		//
		// Button
		//
		enum class Button
		{
			LEFT_MOUSE_BUTTON,				// The left mouse button.
			RIGHT_MOUSE_BUTTON,				// The right mouse button.
			MIDDLE_MOUSE_BUTTON,			// The middle mouse button.
		};


	
		// Initialise the mouse.
        static bool					IsButtonDown( const Mouse::Button button, const GameWindow& window );	// Checks if a certain button is down.
        static bool					IsButtonUp( const Mouse::Button button, const GameWindow& window );		// Checks if a certain button is up.
        static void					IsVisible( const bool visible );
        static void                 SetShape( int QtShapeValue );

        static const Point          GetMouseScreenPosition();
        static const Point			GetMouseWindowPosition( const GameWindow& window );
        static const Point			GetMouseCanvasPosition( const GameWindow& window, const Canvas& canvas );


	private:



		static bool					isVisible;
        static int                  shape;


	};

}



#endif

