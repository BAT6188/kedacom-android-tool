#include "phonedockwidget.h"
#include "ui_phonedockwidget.h"
#include <QDebug>

PhoneDockWidget::PhoneDockWidget(QWidget *parent,Phone *p) :
    QDockWidget(parent),
    ui(new Ui::PhoneDockWidget)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
    ui->phoneID->setText(p->getProperty("[ro.boot.serialno]"));
    ui->phoneName->setText(p->getProperty("[ro.product.name]"));
}

PhoneDockWidget::~PhoneDockWidget()
{
    delete ui;
    qDebug() << "~PhoneDockWidget";
}
