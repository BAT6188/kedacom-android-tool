#include "ksetting.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

KSetting::KSetting():QSettings("config.ini",QSettings::IniFormat,qApp)
{
    initSetting();
}

KSetting::~KSetting()
{

}

void KSetting::initSetting()
{
    QString sdk = this->value("SDKPATH","").toString();
    qDebug() << "### "+sdk;

    if(sdk.isEmpty())
    {
        qDebug() << "Please set the sdk path first!";
        QMessageBox box;
        box.setText(QObject::tr("Welcome!,please do some settings first."));
        box.exec();

        do
        {
            sdk = QFileDialog::getExistingDirectory(NULL,QObject::tr("Choose Andorid SDK PATH"),"/");
            if(!sdk.isEmpty())
            {
                qDebug() << sdk;
                if(checkSDK(sdk))
                {
                    this->setValue("SDKPATH",sdk);
                    break;
                }
            }
        } while(true);
    }
}

bool KSetting::checkSDK(QString sdk)
{
    QDir sdkDir(sdk);
    if(sdkDir.exists()) {
        foreach (QFileInfo file, sdkDir.entryInfoList()) {
            qDebug() << file.baseName();
            if(file.isFile()) {
                if(file.baseName() == "adb") {
                    this->setValue("ADB_PATH",file.absoluteFilePath());
                    return true;
                }
            }
        }
    }
    return false;
}



