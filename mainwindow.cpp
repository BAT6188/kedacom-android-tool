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

    screenShotWidget = new ScreenShot(ui->stackedWidget);
    ADBProcess process;
    process.exec("version");
    ui->statusBar->showMessage(process.readAll());

    process.exec("devices");
    ui->pushButton->setText(process.readAll());

    ui->stackedWidget->addWidget(screenShotWidget);
    ui->stackedWidget->setCurrentWidget(screenShotWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
