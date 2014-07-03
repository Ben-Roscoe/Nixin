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

        Image as( "brick.png" );
        //as.ConvertTo32Bits();
        Image image32( as );
        //tex.Bind();
        gl->glBindTexture( GL_TEXTURE_2D, tex.GetID() );
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        gl->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        tex.SetMutableStorage( 0, image32.GetWidth(), image32.GetHeight(), GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE, ( GLvoid* )image32.GetPixels<float>() );



        //tex.SetImmutableStorage( 1, image32.GetWidth(), image32.GetHeight(), GL_RGBA );
        //tex.SetData( 0, GL_BGRA, GL_UNSIGNED_BYTE, image32.GetWidth(), image32.GetHeight(), ( GLvoid* )image32.GetPixels<float>() );
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
    }



    //
    // Draw
    //
    void GameWindow::Draw()
    {
        canvas.ClearBuffer( true, false, false );

        canvas.BeginSpriteDrawing();
        canvas.DrawSprite( tex, Rectangle( 50, 50, 200, 200 ), Colour::White );
        canvas.EndSpriteDrawing();

        SwapBuffers();
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
    // resizeEvent
    //
    void GameWindow::resizeEvent( QResizeEvent *ev )
    {
        canvas.SetBounds( Rectangle( 0, 0, ev->size().width(), ev->size().height() ) );
        canvas.camera.SetOrthoProjection( Rectangle( 0, 0, ev->size().width(), ev->size().height() ) );
        Draw();
    }
}
