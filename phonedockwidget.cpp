#include "phonedockwidget.h"
#include "ui_phonedockwidget.h"

PhoneDockWidget::PhoneDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PhoneDockWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
}

PhoneDockWidget::~PhoneDockWidget()
{
    delete ui;
}
