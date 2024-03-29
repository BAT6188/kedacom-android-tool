#include "adbprocess.h"
#include "ksetting.h"

ADBProcess::ADBProcess(): QProcess(qApp)
{
    setProcessChannelMode(QProcess::MergedChannels);
}

void ADBProcess::exec(QString cmd)
{
    start(KSetting::getSetting()->value("ADB_PATH").toString()+" " + cmd);
    waitForFinished(-1);
    return;
}

ADBProcess::~ADBProcess()
{

}

