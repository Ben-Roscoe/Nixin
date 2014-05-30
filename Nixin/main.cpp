//#include "Nixin_Instance.h"
//#include "Nixin_Rectangle.h"
//#include "Nixin_Application.h"

//#ifdef _WIN32
//#include <Windows.h>
//#include "Nixin_GameWindow.h"



////
//// WndProc
////
//LRESULT WINAPI WndProc( HWND handle, UINT message, WPARAM wparam, LPARAM lparam )
//{

//	Nixin::OSManager::UpdateGUI( handle, message, wparam, lparam );
//	switch( message )
//	{
//	case WM_DESTROY:
//		break;
//	}

//	return DefWindowProc( handle, message, wparam, lparam );
//}



////
//// WinMain
//// Entry point. Creates the window and GL context. Message handling is also done here.
////
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
//{
//    MSG										message				= MSG();
//    Nixin::Instance<Nixin::GameBase>		instance;

//    Nixin::OSManager::Initialise( WndProc );

//    instance.SetUp( nullptr, Nixin::OSManager::CreateDefaultWindow( "Nixin Linux", Nixin::Rectangle( 100, 100, 800, 600 ), 32, 32 ) );

//    instance.Run();

//    // Handle other windows until the main canvas is destroyed.
//    while( !instance.Ended() )
//    {
//        GetMessageA( &message, nullptr, 0, 0 );
//        TranslateMessage( &message );
//        DispatchMessageA( &message );
//    }
	
//    return message.wParam;
//}



//#endif

//#ifdef __linux

//#include <X11/Xlib.h>

//int main()
//{

//    Nixin::Instance<Z1_Game>		instance;
//    XEvent                          event;

//	Nixin::OSManager::ConsoleWindow console;
//	Nixin::OSManager::CreateConsoleWindow( &console );

//	Nixin::OSManager::Initialise();
//    Nixin::OSManager::NixinWindow		window = Nixin::OSManager::CreateDefaultWindow( "Nixin Linux", Nixin::Rectangle( 100, 100, 800, 600 ), 32, 32 );
//	instance.SetUp( nullptr, window );
//	instance.Run();

//	// Nixin::OSManager::DestroyConsoleWindow( &console );
//    while( !instance.Ended() )
//    {
//        if( XPending( Nixin::OSManager::defaultWindowType.display ) )
//        {
//            XNextEvent( instance.GetWindow().display, reinterpret_cast<XEvent*>( &event ) );
//        }
//        Nixin::OSManager::UpdateGUI( Nixin::OSManager::defaultWindowType.display, event );
//	}
//	return 0;
//}


//#endif


#include "Nixin_Application.h"
#include "Nixin_GameWindow.h"
#include "Nixin_QtOpenGLWidget.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QtGui>
#include <QGroupBox>
#include <QLayout>
#include "mainwindowtest.h"



//
// main
//
int main( int argc, char* argv[] )
{
    QApplication a(argc, argv);

    Nixin::Application::Start();

//    Nixin::GameWindow           gw;
//    QWidget*                    ggw = QWidget::createWindowContainer( &gw );
//    ggw->show();

//    gw.Draw();

//    ggw->show();

//    QPushButton qpb{ ggw };
//    qpb.show();
//    qpb.setGeometry( 0, 0, 100, 100 );

//    QGridLayout layout( ggw );

//    ggw->setLayout( &layout );

//    ggw->layout()->addWidget( &qpb );

    MainWindowTest                  mainWindow;
  //  mainWindow.show();
//    Nixin::QtOpenGLWidget             mainWindow;


    return a.exec();
}

