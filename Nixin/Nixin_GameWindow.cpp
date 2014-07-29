#include "Nixin_GameWindow.h"
#include "Nixin_Application.h"
#include "Nixin_Font.h"
#include "Nixin_Utility.h"
#include "Nixin_Mouse.h"

namespace Nixin
{



    //
    // GameWindow
    //
    GameWindow::GameWindow( QtOpenGLWindow* share, QWindow *parent ) :
        QtOpenGLWindow( share, parent ), soundEngine( Application::GetSoundDevice() ), canvas( Rectangle( 0, 0, width(), height() ), Point( width(), height() ), 2000.0f, Camera::ProjectionType::ORTHO )
    {
        Utility::InitialiseNEShaders();
        Font::Initialise();

        canvas.SetClearColourValue( Colour::CornflowerBlue );
        canvas.EnableAlphaBlending();

        tex.SetMutableStorage( 0, GL_RGBA, "brick.png" );
    }



    //
    // ~GameWindow
    //
    GameWindow::~GameWindow()
    {
        Utility::UninitialiseNEShaders();
        Font::Uninitialise();
    }



    //
    // Initialise
    //
    void GameWindow::Initialise()
    {

    }



    //
    // LoadContent
    //
    void GameWindow::LoadContent()
    {

    }



    //
    // Update
    //
    void GameWindow::Update()
    {
        gameTime.Update();

        if( keyboard.IsKeyDown( Qt::Key_A ) )
        {
            pos.x--;
        }
        else if( keyboard.IsKeyDown( Qt::Key_D ) )
        {
            pos.x++;
        }
        if( keyboard.IsKeyDown( Qt::Key_S ) )
        {
            pos.y--;
        }
        else if( keyboard.IsKeyDown( Qt::Key_W ) )
        {
            pos.y++;
        }
    }



    //
    // Draw
    //
    void GameWindow::Draw()
    {
        canvas.ClearBuffer( true, false, false );

        canvas.BeginSpriteDrawing();
        canvas.DrawSprite( tex, Rectangle( pos, 200, 200 ), Colour::White );
        canvas.EndSpriteDrawing();
    }



    //
    // UnloadContent
    //
    void GameWindow::DisposeContent()
    {

    }



    //
    // GameLoop
    //
    void GameWindow::GameLoop()
    {
        InitialiseGameLoop();
        while( runningGameLoop )
        {
            RunFrame();
        }
        UninitialiseGameLoop();
    }



    //
    // StartGameLoop
    //
    void GameWindow::StartGameLoop()
    {
        timerId = startTimer( targetTimeStep );
    }



    //
    // StopGameLopp
    //
    void GameWindow::StopGameLoop()
    {
        killTimer( timerId );
    }



    //
    // InitialiseGameLoop
    //
    void GameWindow::InitialiseGameLoop()
    {
        Initialise();
        LoadContent();

        // Start the game time.
        gameTime      = GameTime();

        runningGameLoop                     = true;
        lastTime                    		= gameTime.TotalTime();
        timeBehind                          = 0.0;
    }



    //
    // UninitialseGameLoop
    //
    void GameWindow::UninitialiseGameLoop()
    {
        DisposeContent();
    }



    //
    // RunFrame
    //
    void GameWindow::RunFrame()
    {
        // Update the game time.
        gameTime.Update();
        timeBehind += gameTime.TotalTime() - lastTime;
        lastTime = gameTime.TotalTime();

        while( timeBehind >= targetTimeStep )
        {
            Update();
            timeBehind -= targetTimeStep;
        }

        Draw();
        SwapBuffers();
    }



    //
    // keyPressEvent
    //
    void GameWindow::keyPressEvent( QKeyEvent *e )
    {
        keyboard.SetKey( e );
    }



    //
    // keyReleaseEvent
    //
    void GameWindow::keyReleaseEvent( QKeyEvent *e )
    {
        keyboard.SetKey( e );
    }



    //
    // timerEvent
    //
    void GameWindow::timerEvent( QTimerEvent *e )
    {
        RunFrame();
    }




    //
    // resizeEvent
    //
    void GameWindow::resizeEvent( QResizeEvent *ev )
    {
        canvas.SetBounds( Rectangle( 0, 0, ev->size().width(), ev->size().height() ) );
        canvas.camera.SetOrthoProjection( Rectangle( 0, 0, ev->size().width(), ev->size().height() ) );
    }
}
