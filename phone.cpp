#include "phone.h"
#include <QDebug>
#include <QDebug>

Phone::Phone(QObject *parent) : QObject(parent)
{
    parseProperty();
    totalMem = getTotalMem();
    getCpuGovernor();
    getStorageInfo();
}

float Phone::calPercent(QString used, QString size)
{
    double _size,_used;
    if(used.contains("M") || size.contains("M"))
    {
        _used = used.remove("M").toDouble() * 1000 * 1000;
        _size = size.remove("M").toDouble() * 1000 * 1000;
    }
    if(used.contains("K") || size.contains("K"))
    {
        _used = used.remove("K").toDouble() * 1000;
        _size = size.remove("K").toDouble() * 1000;
    }
    if(used.contains("G") || size.contains("G"))
    {
        _used = used.remove("G").toDouble() * 1000 * 1000 * 1000;
        _size = size.remove("G").toDouble() * 1000 * 1000 * 1000;
    }
    if(_size > 0) {
        return _used/_size;
    }
    return -1;
}

void Phone::getStorageInfo()
{
    QString data,tmp="1";
    QStringList list;
    process.exec("shell df");
    QString used,size;
    tmp.clear();
    while (true)
    {
        data=process.readLine();
        if (data.isEmpty())
            break;
        tmp.append(data);
    }
    list=tmp.split("\n");
    QStringList parts;
    int FileID,UsedID,FreeID,SizeID;
    tmp = list.takeFirst();
    parts=tmp.split(QRegExp("\\s+"));
    for(int i = 0; i < parts.size(); i++) {
        if(parts.at(i) == "Filesystem") {
            FileID = i;
        }

        if(parts.at(i) == "Used") {
            UsedID = i;
        }

        if(parts.at(i) == "Free") {
            FreeID = i;
        }

        if(parts.at(i) == "Size") {
            SizeID = i;
        }
    }

    while (list.count()>0)
    {
        tmp=list.takeFirst();
        parts=tmp.split(QRegExp("\\s+"));
        if (parts.size()>2)
        {
            if(parts.at(FileID)=="/data")
            {
                used = parts.at(UsedID);
                size = parts.at(SizeID);
                //qDebug() << "data:";
                dataPercent = calPercent(used,size);
            }
            if(parts.at(FileID) == ("/system"))
            {
                used = parts.at(UsedID);
                size = parts.at(SizeID);
                //qDebug() << "system:" + used + size;
                systemPercent = calPercent(used,size);
            }
            if(parts.at(FileID) == ("/cache"))
            {
                used = parts.at(UsedID);
                size = parts.at(SizeID);
                //qDebug() << "cache:";
                cachePercent = calPercent(used,size);
            }
        }
    }
}

float Phone::getDataPercent()
{
    return dataPercent;
}

float Phone::getSystemPercent()
{
    return systemPercent;
}

float Phone::getCachePercent()
{
    return cachePercent;
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

void Phone::setCpuGovernor(QString governor)
{
    QString cmd = "shell echo " + governor + " > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
    qDebug() << cmd;
    process.exec(cmd);
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

QStringList Phone::getCpuGovernorList()
{
    return this->governorList;
}

void Phone::getCpuGovernor()
{
    process.exec("shell cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors");
    QString temp = process.readAll();
    this->governorList = temp.split(" ");
    this->governorList.removeAt(governorList.length() -1);
    qDebug() << governorList;
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

void Phone::exec_shell(QString cmd)
{
    process.exec("shell " +cmd);
}



