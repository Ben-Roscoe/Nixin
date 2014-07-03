#ifndef NIXIN_GAMEWINDOW_H
#define NIXIN_GAMEWINDOW_H

#include "Nixin_QtOpenGLWindow.h"
#include "Nixin_GameTime.h"
#include "Nixin_SoundEngine.h"
#include "Nixin_Canvas.h"
#include "Nixin_Texture2D.h"

namespace Nixin
{
    class GameWindow : public QtOpenGLWindow
    {
        Q_OBJECT


    public:
        explicit GameWindow( QtOpenGLWindow* share = 0, QWindow *parent = 0 );
        virtual ~GameWindow();

        virtual void Initialise();
        virtual void LoadContent();
        virtual void DisposeContent();
        virtual void Update();
        virtual void Draw();

        virtual void GameLoop();
        virtual void InitialiseGameLoop();
        virtual void UninitialiseGameLoop();
        virtual void RunFrame();

        void         MoveBrick( Point newPosition )
        {
            pos = newPosition;
        }

    signals:


    public slots:



    protected:



        void                        resizeEvent( QResizeEvent* ev ) override;


        GameTime                    gameTime;
        SoundEngine                 soundEngine;
        double                      targetTimeStep          = 1000.0 / 60.0;
        bool                        runningGameLoop         = false;
        Canvas                      canvas;
        Texture2D                   tex;
        Point                       pos;


    private:



        double                      lastTime                = 0.0f;
        double                      timeBehind              = 0.0f;



    };
}

#endif // NIXIN_GAMEWINDOW_H
