#include "Nixin_Mouse.h"
#include "Nixin_GameWindow.h"

#include <QApplication>

bool				Nixin::Mouse::isVisible = true;
int                 Nixin::Mouse::shape     = 0;


// Public static:



//
// IsButtonDown
// Checks if a button is down.
//
//bool Nixin::Mouse::IsButtonDown( const Mouse::Button button, const OSManager::NixinWindow& window )
//{
//#ifdef _WIN32

//	switch( button )
//	{
//	case Mouse::Button::LEFT_MOUSE_BUTTON:
//		return GetKeyState( VK_LBUTTON ) < 0;
//	case Mouse::Button::MIDDLE_MOUSE_BUTTON:
//		return GetKeyState( VK_MBUTTON ) < 0;
//	case Mouse::Button::RIGHT_MOUSE_BUTTON:
//		return GetKeyState( VK_RBUTTON ) < 0;
//	}

//#endif
//#ifdef __linux

//    // Unfortunately, we have to query the entire pointer state just to get the button masks...
//    int                 x;
//    int                 y;
//    int                 rootX;
//    int                 rootY;
//    Window              rootWindow;
//    Window              childWindow;
//    unsigned int        masks;

//    XQueryPointer( window.display, window.handle, &rootWindow, &childWindow, &rootX, &rootY, &x, &y, &masks );

//    switch( button )
//    {
//    case Mouse::Button::LEFT_MOUSE_BUTTON:
//        return masks & Button1Mask;
//    case Mouse::Button::RIGHT_MOUSE_BUTTON:
//        return masks & Button3Mask;
//    case Mouse::Button::MIDDLE_MOUSE_BUTTON:
//        return masks & Button2Mask;
//    }

//#endif
//	return false;
//}



////
//// IsButtonUp
//// Checks if a button is up.
////
//bool Nixin::Mouse::IsButtonUp( const Mouse::Button button, const OSManager::NixinWindow& window )
//{
//    return !IsButtonDown( button, window );
//}




//
// IsVisible
//
void Nixin::Mouse::IsVisible( const bool visible )
{
    isVisible = visible;

    if( !visible )
    {
        QApplication::setOverrideCursor( QCursor( Qt::BlankCursor ) );
    }
    else
    {
        QApplication::setOverrideCursor( QCursor( static_cast<Qt::CursorShape>( shape ) ) );
    }
}



//
// SetShape
// Sets the shape of the cursor through Qt.
//
void Nixin::Mouse::SetShape( int QtShapeValue )
{
    QApplication::setOverrideCursor( QCursor( QCursor( static_cast<Qt::CursorShape>( QtShapeValue ) ) ) );
    shape = QtShapeValue;
}



//
// GetMouseScreenPosition
//
const Nixin::Point Nixin::Mouse::GetMouseScreenPosition()
{
    return Point( QCursor::pos().x(), QCursor::pos().y() );
}




//
// GetMouseWindowPosition
//
const Nixin::Point Nixin::Mouse::GetMouseWindowPosition( const GameWindow& window )
{
    Point           position{ static_cast<float>( QCursor::pos().x() ) + window.x(), static_cast<float>( QCursor::pos().y() ) + window.y() };
    position.y = ( ( position.y - window.height() ) * -1 );
    return position;
}



//
// GetMouseCanvasPosition
//
const Nixin::Point Nixin::Mouse::GetMouseCanvasPosition( const GameWindow& window, const Canvas& canvas )
{
    Point           position{ static_cast<float>( QCursor::pos().x() ) + window.x(), static_cast<float>( QCursor::pos().y() ) + window.y() };
    position.x -= canvas.GetBounds().x;
    position.y = ( ( position.y - window.height() ) * -1 ) - canvas.GetBounds().y;
    return position;
}




// Private:
