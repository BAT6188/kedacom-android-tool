#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <screenshotthread.h>

namespace Ui {
class ScreenShot;
}

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenShot(QWidget *parent = 0);
    ~ScreenShot();

private:
    Ui::ScreenShot *ui;
    int widthScreen, heightScreen,rotation;
    ThreadScreenshot threadScreenshot;
    QPixmap screenshot;

private slots:
    void takeScreenshot();
    void showScreenshot(QImage, int, int);
};

#endif // SCREENSHOT_H
