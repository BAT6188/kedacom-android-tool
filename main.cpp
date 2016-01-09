#include "mainwindow.h"
#include <QApplication>
#include "ksetting.h"


KSetting *KSetting::ksetting = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Kedacom");
    QCoreApplication::setApplicationName("Keda-Android-Tool");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setOrganizationDomain("http://kedacom.com");

    KSetting::getSetting();
    MainWindow w;
    w.show();

    return a.exec();
}
