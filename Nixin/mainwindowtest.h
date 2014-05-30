#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QMainWindow>
#include "Nixin_GameWindow.h"

namespace Ui {
class MainWindowTest;
}

class MainWindowTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowTest(QWidget *parent = 0);
    ~MainWindowTest();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    void                      mouseMoveEvent( QMouseEvent* ev ) override;


    Ui::MainWindowTest *ui;
    Nixin::GameWindow         gameWindow;
    QWidget*                  gameWindowContainer       = nullptr;
};

#endif // MAINWINDOWTEST_H
