#ifndef SCREENDOCKWIDGET_H
#define SCREENDOCKWIDGET_H

#include <QDockWidget>
#include <screenshotthread.h>
#include <QTimer>
#include "ui_screenform.h"

namespace Ui {
class ScreenDockWidget;
}

class ScreenDockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenDockWidget(QWidget *parent = 0,QString serialNum="");
    ~ScreenDockWidget();
    void closeEvent(QCloseEvent *event);

private:
    Ui::ScreenForm *ui;
    int widthScreen, heightScreen,rotation;
    ThreadScreenshot threadScreenshot;
    QPixmap screenshot;
    QTimer *timer;

private slots:
    void takeScreenshot();
    void showScreenshot(QImage, int, int);
    void startTimer();
    void stopTimer(bool checked);
};

#endif // SCREENDOCKWIDGET_H
