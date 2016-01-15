#include "mainwindow.h"
#include <QApplication>
#include <ksetting.h>
#include <phonemanager.h>
#include <QFile>


KSetting *KSetting::ksetting = NULL;
PhoneManager *PhoneManager::phoneManager = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Kedacom");
    QCoreApplication::setApplicationName("Keda-Android-Tool");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setOrganizationDomain("http://kedacom.com");

    QFile file(":/qss/pagefold.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);

    KSetting::getSetting();
    PhoneManager::getInstanse();

    MainWindow w;
    w.show();

    return a.exec();
}
