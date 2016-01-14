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

private:
    void parseProperty();
    QString serialNum;
    QMap<QString,QString> propertyMap;
    ADBProcess process;
};

#endif // PHONE_H
