#ifndef PHONECONNECTTHREAD_H
#define PHONECONNECTTHREAD_H

#include <QThread>
#include <QApplication>
#include <QTcpSocket>
#include <QObject>

class PhoneConnectThread : public QThread
{
    Q_OBJECT
private:
    void run();

signals:
    void connectionChanged(int,QString);
};

#endif // PHONECONNECTTHREAD_H
