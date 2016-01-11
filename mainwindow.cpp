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

    //screenShotWidget = new ScreenShot(ui->stackedWidget);
    screenDockWidget = new ScreenDockWidget(this);
    phoneDockWidget = new PhoneDockWidget(this);

    ADBProcess process;
    process.exec("version");
    ui->statusBar->showMessage(process.readAll());

    //ui->stackedWidget->addWidget(screenDockWidget);
    //ui->stackedWidget->setCurrentWidget(screenDockWidget);
    addDockWidget(Qt::RightDockWidgetArea,screenDockWidget);
    addDockWidget(Qt::LeftDockWidgetArea,phoneDockWidget);
    createActions();
    ui->mainToolBar->addAction(phoneAction);

    phonethread.start();
}

void MainWindow::createActions()
{
    phoneAction = new QAction(QIcon(":/icons/images/mainwindow.jpg"),tr("My Phone"),this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
