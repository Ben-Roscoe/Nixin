#ifndef NIXIN_QTOPENGLWIDGET_H
#define NIXIN_QTOPENGLWIDGET_H

#include <QWidget>
#include "Nixin_GameWindow.h"


namespace Nixin
{
    class QtOpenGLWidget : public QWidget
    {
        Q_OBJECT


    public:
        explicit QtOpenGLWidget( QWidget *parent = 0 );


    signals:

    public slots:


    private:


        GameWindow*                  openglWindow;


    };
}

#endif // NIXIN_QTOPENGLWIDGET_H
