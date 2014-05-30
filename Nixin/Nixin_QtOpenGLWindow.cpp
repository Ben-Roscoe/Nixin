#include "Nixin_QtOpenGLWindow.h"
#include <QMessageBox>



//
// QtOpenGLWindow
//
Nixin::QtOpenGLWindow::QtOpenGLWindow( QtOpenGLWindow* share, QWindow* parent ) : QWindow( parent )
{
    // Set the QWindow surface.
    setSurfaceType( QSurface::OpenGLSurface );
    create();

    // Create the OpenGL context.
    openglContext = new QOpenGLContext( this );

    openglContext->create();

    if( share != nullptr )
    {
        openglContext->setShareContext( share->openglContext );
    }

    openglContext->makeCurrent( this );

    gl = openglContext->versionFunctions<OpenGLFunctions>();
    gl->initializeOpenGLFunctions();
}



//
// ~QtOpenGLWindow
//
Nixin::QtOpenGLWindow::~QtOpenGLWindow()
{
    delete openglContext;
}



//
// SwapBuffers
//
void Nixin::QtOpenGLWindow::SwapBuffers()
{
    openglContext->swapBuffers( this );
}
