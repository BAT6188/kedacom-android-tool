#include "phone.h"
#include <QDebug>
#include <QDebug>

Phone::Phone(QObject *parent) : QObject(parent)
{
    parseProperty();
    //cpu = new CPU(this);
}

void Phone::parseProperty()
{
    process.exec("shell getprop");
    QString tmp = "0";
    while (!tmp.isEmpty())
    {
        process.waitForReadyRead(-1);
        tmp=process.readLine();
        QStringList tl = tmp.split(":");
        if(tl.length() >= 2)
        {
            propertyMap[tl.at(0)]=tl.at(1);
        }
    }
    qDebug() << propertyMap["[ro.product.name]"];
}

QString Phone::getProperty(QString property)
{
    return propertyMap[property];
}

Phone::~Phone()
{
    qDebug() << "~Phone";
}

QString Phone::getID()
{
    QString serialNum = this->getProperty("[ro.boot.serialno]");
    serialNum.remove('[');
    serialNum.remove(']');
    serialNum.remove(' ');
    serialNum.remove("\r\r\n");
    return serialNum;
}

QList<QByteArray> Phone::getCurFreq()
{
    QList<QByteArray> list;
    process.exec("shell cat /sys/devices/system/cpu/cpu*/cpufreq/cpuinfo_cur_freq");
    list = process.readAll().replace("\r\r","").split('\n');
    return list;
}



