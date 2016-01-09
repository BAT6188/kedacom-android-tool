#ifndef ADBPROCESS_H
#define ADBPROCESS_H

#include <QProcess>
#include <QApplication>

class ADBProcess : public QProcess
{
public:
    ADBProcess();
    ~ADBProcess();
    exec(QString cmd);

private:
    static ADBProcess *ADBcommand;
};

#endif // ADBPROCESS_H
