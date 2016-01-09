#ifndef KSETTING_H
#define KSETTING_H


#include <QSettings>
#include <QDebug>

class KSetting : public QSettings
{
public:
    KSetting();
    ~KSetting();
    static KSetting* getSetting() {
        if(ksetting == NULL)
            ksetting = new KSetting();
         return ksetting;
    }

private:
    void initSetting();
    bool checkSDK(QString sdk);
    static KSetting *ksetting;
};

#endif // KSETTING_H
