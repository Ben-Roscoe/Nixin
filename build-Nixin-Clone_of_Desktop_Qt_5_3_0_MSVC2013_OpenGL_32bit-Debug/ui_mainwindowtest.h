/********************************************************************************
** Form generated from reading UI file 'mainwindowtest.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWTEST_H
#define UI_MAINWINDOWTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowTest
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *OpenGLLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowTest)
    {
        if (MainWindowTest->objectName().isEmpty())
            MainWindowTest->setObjectName(QStringLiteral("MainWindowTest"));
        MainWindowTest->resize(800, 600);
        centralwidget = new QWidget(MainWindowTest);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        OpenGLLayout = new QVBoxLayout();
        OpenGLLayout->setObjectName(QStringLiteral("OpenGLLayout"));

        verticalLayout->addLayout(OpenGLLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindowTest->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowTest);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindowTest->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowTest);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowTest->setStatusBar(statusbar);

        retranslateUi(MainWindowTest);

        QMetaObject::connectSlotsByName(MainWindowTest);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowTest)
    {
        MainWindowTest->setWindowTitle(QApplication::translate("MainWindowTest", "MainWindow", 0));
        pushButton_2->setText(QApplication::translate("MainWindowTest", "Move", 0));
        pushButton->setText(QApplication::translate("MainWindowTest", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowTest: public Ui_MainWindowTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWTEST_H
