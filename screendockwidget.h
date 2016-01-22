#ifndef SCREENDOCKWIDGET_H
#define SCREENDOCKWIDGET_H

#include <QDockWidget>
#include <screenshotthread.h>
#include <QTimer>
#include "ui_screenform.h"
#include <phone.h>

namespace Ui {
class ScreenDockWidget;
}

class ScreenDockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenDockWidget(QWidget *parent = 0,Phone *p = 0);
    ~ScreenDockWidget();
    void closeEvent(QCloseEvent *event);

private:
    Ui::ScreenForm *ui;
    int widthScreen, heightScreen,rotation;
    ThreadScreenshot threadScreenshot;
    QPixmap screenshot;
    QTimer *timer;
    Phone *phone;

protected:
    void mousePressEvent(QMouseEvent *e=0);

private slots:
    void takeScreenshot();
    void showScreenshot(QImage, int, int);
    void startTimer();
    void stopTimer(bool checked);
    void back();
    void left();
    void right();
    void power();
    void menu();
};

#endif // SCREENDOCKWIDGET_H
