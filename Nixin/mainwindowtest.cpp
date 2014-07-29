#include "mainwindowtest.h"
#include "ui_mainwindowtest.h"

#include <QWidget>
#include "Nixin_Point.h"

MainWindowTest::MainWindowTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowTest)
{

    ui->setupUi(this);
    ui->centralwidget->setMouseTracking( true );
    show();
    gameWindowContainer = QWidget::createWindowContainer( &gameWindow, this );

    ui->OpenGLLayout->addWidget( gameWindowContainer );
    gameWindowContainer->show();
    gameWindowContainer->setMouseTracking( true );

    gameWindow.StartGameLoop();

}

MainWindowTest::~MainWindowTest()
{
    gameWindow.StopGameLoop();
    delete ui;
}

void MainWindowTest::on_pushButton_clicked()
{
    close();
}

void MainWindowTest::on_pushButton_2_clicked()
{
}

void MainWindowTest::mouseMoveEvent(QMouseEvent *ev)
{
    gameWindow.MoveBrick( Nixin::Point( ev->x(), ev->y() ) );
}
