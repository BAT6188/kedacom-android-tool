#ifndef SCREENSHOTTHREAD_H
#define SCREENSHOTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QImage>

QImage noScreenshotImage(int, int);

class ThreadScreenshot : public QThread
{
    Q_OBJECT
public:
    void run();
    int widthScreen, heightScreen;
    void setSerialNum(QString serialNum);
signals:
    void gotScreenshot(QImage, int, int);

private:
    QString serialNumber;
};
#endif // SCREENSHOTTHREAD_H
