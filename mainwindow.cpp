#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <ksetting.h>
#include <adbprocess.h>
#include <phonemanager.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ADBProcess process;
    process.exec("version");
    ui->statusBar->showMessage(process.readAll());
    process.exec("devices");

    createActions();
    ui->mainToolBar->addAction(phoneAction);

    connect(&phonethread,SIGNAL(connectionChanged(int,QString)),this,SLOT(slotConnectionChanged(int,QString)));
    phonethread.start();
}

//ScreenDockWidget *MainWindow::createScreenWidget(Phone *phone)
//{
//    QString serialNum = phone->getID();

//    qDebug() << "MainWindow:" + serialNum;

//    ScreenDockWidget *screenDockWidget = new ScreenDockWidget(0,serialNum);
//    //addDockWidget(Qt::TopDockWidgetArea,screenDockWidget);
//    return screenDockWidget;
//}

void MainWindow::createActions()
{
    phoneAction = new QAction(QIcon(":/icons/images/mainwindow.jpg"),tr("My Phone"),this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotConnectionChanged(int flag,QString msg)
{
    qDebug() << "slotConnectionChanged:" + msg;
    if(flag == 1)
    {
        Phone *p = new Phone(this);
        PhoneManager::getInstanse()->AddPhone(p);
        PhoneDockWidget *phoneDockWidget = new PhoneDockWidget(this,p);
        addDockWidget(Qt::LeftDockWidgetArea,phoneDockWidget);
        phoneDockList.append(phoneDockWidget);
        connect(p,SIGNAL(destroyed(QObject*)),phoneDockWidget,SLOT(deleteLater()));
    }
    if(flag == 0)
    {
        if(phoneDockList.length() > 0) {
            qDebug() << "slotConnectionChanged: Remove the phone" + msg;
            PhoneManager::getInstanse()->RemovePhone(0);
            this->removeDockWidget(phoneDockList.last());
            phoneDockList.removeLast();
        }
    }
}

