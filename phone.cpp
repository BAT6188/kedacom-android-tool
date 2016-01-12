#include "phone.h"
#include <QDebug>
#include <QDebug>

Phone::Phone(QObject *parent) : QObject(parent)
{
    parseProperty();
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

