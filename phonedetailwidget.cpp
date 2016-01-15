#include "phonedetailwidget.h"
#include "ui_phonedetailwidget.h"
#include <QDebug>
#include <adbprocess.h>

PhoneDetailWidget::PhoneDetailWidget(QWidget *parent,Phone *p) :
    QWidget(parent),
    ui(new Ui::PhoneDetailWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    connect(p,SIGNAL(destroyed(QObject*)),this,SLOT(deleteLater()));
    this->setWindowTitle(p->getID());
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showCPUInfo()));
    timer->start(1000);
    this->phone = p;
}

PhoneDetailWidget::~PhoneDetailWidget()
{
    qDebug() << "~PhoneDetailWidget";
    timer->stop();
    delete ui;
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
