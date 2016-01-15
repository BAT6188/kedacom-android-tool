#include "phonedockwidget.h"
#include "ui_phonedockwidget.h"
#include <QDebug>
#include "phonedetailwidget.h"

PhoneDockWidget::PhoneDockWidget(QWidget *parent,Phone *p) :
    QDockWidget(parent),
    ui(new Ui::PhoneDockWidget)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
    ui->phoneID->setText(p->getProperty("[ro.boot.serialno]"));
    ui->phoneName->setText(p->getProperty("[ro.product.name]"));
    this->p = p;
    pdw = new PhoneDetailWidget(0,p);
    screenDockWidget = new ScreenDockWidget(0,p->getID());
    connect(p,SIGNAL(destroyed(QObject*)),screenDockWidget,SLOT(deleteLater()));
    connect(ui->More,SIGNAL(clicked(bool)),this,SLOT(showDetail()));
    connect(ui->ScreenBtn,SIGNAL(clicked(bool)),this,SLOT(showScreen()));
}

PhoneDockWidget::~PhoneDockWidget()
{
    qDebug() << "~PhoneDockWidget";
    delete ui;
}

void PhoneDockWidget::showDetail()
{
    pdw->show();
}

void PhoneDockWidget::showScreen()
{
    screenDockWidget->show();
}


