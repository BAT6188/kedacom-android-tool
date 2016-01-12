#include "phonedockwidget.h"
#include "ui_phonedockwidget.h"
#include <QDebug>

PhoneDockWidget::PhoneDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PhoneDockWidget)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

PhoneDockWidget::~PhoneDockWidget()
{
    delete ui;
}

void PhoneDockWidget::slotConnectionChanged(int flag,QString msg)
{
    //create Phone instanse here
    qDebug() << "slotConnectionChanged:" + msg;
    if(flag == 1)
    {
        Phone *p = new Phone(this);
        phoneMap.insert(1,p);
        ui->phoneID->setText(p->getProperty("[ro.boot.serialno]"));
        ui->phoneName->setText(p->getProperty("[ro.product.name]"));
    }
    if(flag == 0)
    {
        phoneMap.remove(1);
    }
}
