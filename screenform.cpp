#include "screenform.h"
#include "ui_screenform.h"
#include <QDebug>

ScreenForm::ScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenForm)
{
    ui->setupUi(this);
}

ScreenForm::~ScreenForm()
{
    qDebug() << "~ScreenForm";
    delete ui;
}
