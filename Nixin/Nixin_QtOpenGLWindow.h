#ifndef NIXIN_QTOPENGLWINDOW_H
#define NIXIN_QTOPENGLWINDOW_H


#include "Nixin_Types.h"

#include <QWindow>
#include <QtGui>
#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{
    class QtOpenGLWindow : public QWindow, public OpenGLFunctions
    {

        Q_OBJECT

    public:


        QtOpenGLWindow( QtOpenGLWindow* share = 0, QWindow* parent = 0 );
        virtual ~QtOpenGLWindow();

        void                            SwapBuffers();


    protected:



        QOpenGLContext*                 openglContext           = nullptr;



    };
}



#endif // NIXIN_QTOPENGLWINDOW_H
