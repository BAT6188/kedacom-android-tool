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

    screenDockWidget = new ScreenDockWidget(this);
    phoneDockWidget = new PhoneDockWidget(this);

    ADBProcess process;
    process.exec("version");
    ui->statusBar->showMessage(process.readAll());

    addDockWidget(Qt::RightDockWidgetArea,screenDockWidget);
    addDockWidget(Qt::LeftDockWidgetArea,phoneDockWidget);
    createActions();
    ui->mainToolBar->addAction(phoneAction);

    connect(&phonethread,SIGNAL(connectionChanged(int,QString)),phoneDockWidget,SLOT(slotConnectionChanged(int,QString)));
    phonethread.start();
}

void MainWindow::createActions()
{
    phoneAction = new QAction(QIcon(":/icons/images/mainwindow.jpg"),tr("My Phone"),this);
}

MainWindow::~MainWindow()
{
    if(phonethread.isRunning())
    {
        phonethread.terminate();
    }
    delete ui;
}
