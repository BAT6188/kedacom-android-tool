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
    QStringList getCpuGovernorList();
    void getStorageInfo();
    void setCpuGovernor(QString governor);
    float getDataPercent();
    float getSystemPercent();
    float getCachePercent();

private:
    float calPercent(QString used,QString size);
    void parseProperty();
    long getTotalMem();
    QString serialNum;
    QMap<QString,QString> propertyMap;
    ADBProcess process;
    QMap<QString,int> meminfo;
    long totalMem;
    QStringList governorList;
    void getCpuGovernor();
    float dataPercent,cachePercent,systemPercent;
};

#endif // PHONE_H
