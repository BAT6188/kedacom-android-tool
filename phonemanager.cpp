#include "phonemanager.h"

PhoneManager::PhoneManager(QObject *parent) : QObject(parent)
{

}

void PhoneManager::AddPhone(Phone *p)
{
    phoneMap.insert(count++,p);
}

void PhoneManager::RemovePhone(Phone *p = 0)
{
    phoneMap.last()->deleteLater();
    phoneMap.remove(--count);
}

