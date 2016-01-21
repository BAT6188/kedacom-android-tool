#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include <QObject>
#include <phone.h>
#include <QDebug>

class PhoneManager : public QObject
{
    Q_OBJECT
public:
    explicit PhoneManager(QObject *parent = 0);
    static PhoneManager* getInstanse() {
        if(phoneManager == NULL)
            phoneManager = new PhoneManager(qApp);
         return phoneManager;
    }

    void AddPhone(Phone *p);
    void RemovePhone(Phone *p);

private:
    QMap<int,Phone*> phoneMap;
    static PhoneManager *phoneManager;
    int count;

signals:

public slots:
};

#endif // PHONEMANAGER_H
