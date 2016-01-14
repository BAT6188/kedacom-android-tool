#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <ksetting.h>
#include <adbprocess.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //screenDockWidget = new ScreenDockWidget(this);
    phoneDockWidget = new PhoneDockWidget(this);

    ADBProcess process;
    process.exec("version");
    ui->statusBar->showMessage(process.readAll());
    process.exec("devices");

    //addDockWidget(Qt::RightDockWidgetArea,screenDockWidget);
    addDockWidget(Qt::LeftDockWidgetArea,phoneDockWidget);
    createActions();
    ui->mainToolBar->addAction(phoneAction);

    connect(&phonethread,SIGNAL(connectionChanged(int,QString)),phoneDockWidget,SLOT(slotConnectionChanged(int,QString)));
    connect(phoneDockWidget,SIGNAL(newPhone(QString)),this,SLOT(createScreenWidget(QString)));
    phonethread.start();
}

void MainWindow::createScreenWidget(QString serialNum)
{
    serialNum.remove('[');
    serialNum.remove(']');
    serialNum.remove(' ');
    serialNum.remove("\r\r\n");

    qDebug() << "MainWindow:" + serialNum;

    screenDockWidget = new ScreenDockWidget(this,serialNum);
    addDockWidget(Qt::LeftDockWidgetArea,screenDockWidget);
}

void MainWindow::createActions()
{
    phoneAction = new QAction(QIcon(":/icons/images/mainwindow.jpg"),tr("My Phone"),this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
