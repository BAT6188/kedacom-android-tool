#include "phonedetailwidget.h"
#include "ui_phonedetailwidget.h"
#include <QDebug>
#include <adbprocess.h>
#include <QCloseEvent>
#include <QRadioButton>

PhoneDetailWidget::PhoneDetailWidget(QWidget *parent,Phone *p) :
    QWidget(parent),
    ui(new Ui::PhoneDetailWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    this->phone = p;

    connect(p,SIGNAL(destroyed(QObject*)),this,SLOT(deleteLater()));
    this->setWindowTitle(p->getID());
    timer = new QTimer(this);
    meminfoTimer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(showCPUInfo()));
    connect(meminfoTimer,SIGNAL(timeout()),this,SLOT(showMemInfo()));


    nameColor["Buffers"] = Qt::red;
    nameColor["Cached"] = Qt::blue;
    nameColor["MemFree"] = Qt::green;

    ui->freeLabel->setStyleSheet("background-color:#00FF00");
    ui->cacheLabel->setStyleSheet("background-color:#0000FF");
    ui->BuffersLabel->setStyleSheet("background-color:#FF0000");
    ui->othersLabel->setStyleSheet("background-color:#00FFFF");

    foreach (QString governor, p->getCpuGovernorList()) {
        QRadioButton *radio = new QRadioButton(governor,ui->groupBox);
        connect(radio,SIGNAL(clicked(bool)),this,SLOT(radioChanged()));
        ui->groupVertical->addWidget(radio);
    }
    ui->groupBox->setLayout(ui->groupVertical);

    ui->dataBar->setValue(p->getDataPercent()*100);
    ui->systemBar->setValue(p->getSystemPercent()*100);
    ui->cacheBar->setValue(p->getCachePercent()*100);
}

PhoneDetailWidget::~PhoneDetailWidget()
{
    qDebug() << "~PhoneDetailWidget";
    timer->stop();
    delete ui;
}

void PhoneDetailWidget::radioChanged()
{
    QRadioButton *btn = (QRadioButton*)sender();
    this->phone->setCpuGovernor(btn->text());
    //qDebug() << btn->text();
}

void PhoneDetailWidget::showCPUInfo()
{
    qDebug() << "poll cpu info";
    QList<QByteArray> tlist = this->phone->getCurFreq();
    QString temp;
    foreach(QByteArray a,tlist)
    {
        temp.append(a+'\n');
    }
    ui->freq_label->setText(temp);
}

void PhoneDetailWidget::showMemInfo()
{
    QMap<QString,int> temp = phone->getMemInfo();
//  int totalValue = temp["MemTotal"];
//  temp.remove("MemTotal");

    ui->memLabel->setValue(temp,nameColor,phone->getMemTotal());
    ui->memLabel->repaint();
}

void PhoneDetailWidget::showMe()
{
    this->show();
    timer->start(1000);
    meminfoTimer->start(5000);
}

void PhoneDetailWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "PhoneDetailWidget close";
    event->accept();
    timer->stop();
    meminfoTimer->stop();
}
