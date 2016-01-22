#include "screendockwidget.h"
//#include "ui_screendockwidget.h"
#include <QCloseEvent>
#include <QProcess>

ScreenDockWidget::ScreenDockWidget(QWidget *parent,Phone *p) :
    QWidget(parent),
    ui(new Ui::ScreenForm)
{
    ui->setupUi(this);
    //ui->dockWidgetContents->setLayout(ui->gridLayout);
    this->setLayout(ui->gridLayout);

    this->phone = p;
    this->rotation = 0;
    this->widthScreen = 240;
    this->heightScreen = 480;

    QRegExp regx("[0-9]+$");//only number
    QValidator *validator = new QRegExpValidator(regx, ui->x_width);
    ui->x_width->setValidator(validator);
    ui->y_height->setValidator(validator);

    this->screenshot = QPixmap::fromImage(noScreenshotImage(this->widthScreen, this->heightScreen), Qt::AutoColor);
    this->ui->labelScreen->setPixmap(this->screenshot);

    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(takeScreenshot()));
    threadScreenshot.setSerialNum(p->getID());
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
    this->setWindowTitle(p->getID());

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(takeScreenshot()));
    connect(ui->start,SIGNAL(clicked(bool)),this,SLOT(startTimer()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(stopTimer(bool)));

    connect(ui->backBtn,SIGNAL(clicked(bool)),this,SLOT(back()));
    connect(ui->menuBtn,SIGNAL(clicked(bool)),this,SLOT(menu()));
    connect(ui->powerBtn,SIGNAL(clicked(bool)),this,SLOT(power()));
}

void ScreenDockWidget::startTimer()
{
    if(ui->checkBox->isChecked())
    {
        if(!timer->isActive())
        {
            timer->start(100);
        }
    }
    else
    {
        takeScreenshot();
    }
}

void ScreenDockWidget::stopTimer(bool checked)
{
    if(checked)
    {
        if(!timer->isActive())
            timer->start(100);
    }
    else
    {
        timer->stop();
    }
}

void ScreenDockWidget::showScreenshot(QImage image, int width, int height)
{
    this->rotation = 0;
    QSize scaledSize = QSize(width, height);
    scaledSize.scale(this->size(), Qt::KeepAspectRatio);
    this->screenshot = QPixmap::fromImage(image, Qt::AutoColor);
    this->ui->labelScreen->setPixmap(this->screenshot.scaled(this->ui->labelScreen->size(),
                                                             Qt::KeepAspectRatio,
                                                             Qt::SmoothTransformation));
    //disconnect(this, SLOT(showScreenshot(QImage,int,int)));
}

void ScreenDockWidget::takeScreenshot()
{
    threadScreenshot.widthScreen = this->ui->labelScreen->width();
    threadScreenshot.heightScreen = this->ui->labelScreen->height();
    threadScreenshot.start();
    //connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
}

ScreenDockWidget::~ScreenDockWidget()
{
    qDebug() << "~ScreenDockWidget";
    threadScreenshot.deleteLater();
    delete ui;
}

void ScreenDockWidget::closeEvent(QCloseEvent *e)
{
    qDebug() << "ScreenDockWidget::closeEvent";
    timer->stop();
    e->accept();
}


void ScreenDockWidget::mousePressEvent(QMouseEvent *event)
{
    double fixed_x,fixed_y = 0;
    int res_x = ui->x_width->text().toInt();
    int res_y = ui->y_height->text().toInt();
    if(res_x > 0 && res_y >0)
    {
        if(event->button() == Qt::LeftButton)
        {
            qDebug() << event->pos();
            fixed_x = (res_x/this->widthScreen)*event->pos().x();
            fixed_y = (res_y/this->heightScreen)*event->pos().y();
            QString str = "input touchscreen tap " + QString("%1 %2").arg(fixed_x).arg(fixed_y);
            qDebug() << str;
            phone->exec_shell(str);
        }
    }
}

void ScreenDockWidget::back()
{
    QString str = "input keyevent BACK";
    phone->exec_shell(str);
}

void ScreenDockWidget::menu()
{
    QString str = "input keyevent MENU";
    phone->exec_shell(str);
}

void ScreenDockWidget::power()
{
    QString str = "input keyevent POWER";
    phone->exec_shell(str);
}

void ScreenDockWidget::left()
{
    QString str = "input touchscreen swipe "+QString("%1 %2 %3 %4").arg(800).arg(800).arg(200).arg(800);
    phone->exec_shell(str);
}

void ScreenDockWidget::right()
{
    QString str = "input touchscreen swipe "+QString("%1 %2 %3 %4").arg(200).arg(800).arg(800).arg(800);
    phone->exec_shell(str);

}
