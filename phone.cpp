#include "phone.h"
#include <QDebug>
#include <QDebug>

Phone::Phone(QObject *parent) : QObject(parent)
{
    parseProperty();
    totalMem = getTotalMem();
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

long Phone::getTotalMem()
{
    process.exec("shell cat /proc/meminfo");
    QString tmp = "0";
    bool ok;
    while (!tmp.isEmpty())
    {
        process.waitForReadyRead(-1);
        tmp=process.readLine();
        if(tmp.contains("MemTotal")) {
            QStringList tl = tmp.split(":");
            QString del = (QString)tl.at(1);
            del.remove(" ");
            del.remove("\r\r\n");
            del.remove("kB");
            long total = del.toLong(&ok,10);
            qDebug() << "total:"+ del;
            return total;
        }
    }
    return 0;
}

long Phone::getMemTotal()
{
    return totalMem;
}

QMap<QString,int> Phone::getMemInfo()
{
    process.exec("shell cat /proc/meminfo");
    QString tmp = "0";
    bool ok;
    while (!tmp.isEmpty())
    {
        process.waitForReadyRead(-1);
        tmp=process.readLine();
        QStringList tl = tmp.split(":");

        if(tl.length() >=2 ) {
            QString name = tl.at(0);
            if(name == "MemFree" || name == "Buffers" || name == "Cached") {
                QString del = (QString)tl.at(1);
                del.remove(" ");
                del.remove("\r\r\n");
                del.remove("kB");
                qDebug() << tl.at(0)+":"+ del;
                long a = del.toLong(&ok,10);
                meminfo[tl.at(0)] = a;
            }
        }
    }
    return meminfo;
}



