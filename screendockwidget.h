#ifndef SCREENDOCKWIDGET_H
#define SCREENDOCKWIDGET_H

#include <QDockWidget>
#include <screenshotthread.h>
#include <QTimer>

namespace Ui {
class ScreenDockWidget;
}

class ScreenDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ScreenDockWidget(QWidget *parent = 0,QString serialNum="");
    ~ScreenDockWidget();

private:
    Ui::ScreenDockWidget *ui;
    int widthScreen, heightScreen,rotation;
    ThreadScreenshot threadScreenshot;
    QPixmap screenshot;

private slots:
    void takeScreenshot();
    void showScreenshot(QImage, int, int);
};

#endif // SCREENDOCKWIDGET_H
