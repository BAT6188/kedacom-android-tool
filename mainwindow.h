#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <screenshotthread.h>
#include <screenshot.h>
#include <QAction>
#include <screendockwidget.h>
#include <phonedockwidget.h>
#include <phoneconnectthread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ScreenShot *screenShotWidget;
    ScreenDockWidget *screenDockWidget;
    PhoneDockWidget *phoneDockWidget;
    QAction *phoneAction;
    PhoneConnectThread phonethread;
    void createActions();
};

#endif // MAINWINDOW_H
