#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <screenshotthread.h>
#include <screenshot.h>

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
};

#endif // MAINWINDOW_H
