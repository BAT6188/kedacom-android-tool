#include "screenform.h"
#include "ui_screenform.h"

ScreenForm::ScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenForm)
{
    ui->setupUi(this);
}

ScreenForm::~ScreenForm()
{
    delete ui;
}
