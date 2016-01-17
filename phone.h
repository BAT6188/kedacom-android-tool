#ifndef PHONE_H
#define PHONE_H

#include <QObject>
#include <QMap>
#include <adbprocess.h>

class Phone : public QObject
{
    Q_OBJECT
public:
    explicit Phone(QObject *parent = 0);
    QString getProperty(QString property);
    ~Phone();
    QString getID();
    QList<QByteArray> getCurFreq();
    QMap<QString,int> getMemInfo();
    long getMemTotal();

private:
    void parseProperty();
    long getTotalMem();
    QString serialNum;
    QMap<QString,QString> propertyMap;
    ADBProcess process;
    QMap<QString,int> meminfo;
    long totalMem;
};

#endif // PHONE_H
