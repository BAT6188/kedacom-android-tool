#include "screendockwidget.h"
//#include "ui_screendockwidget.h"
#include <QCloseEvent>

ScreenDockWidget::ScreenDockWidget(QWidget *parent,QString serialNum) :
    QWidget(parent),
    ui(new Ui::ScreenForm)
{
    ui->setupUi(this);
    //ui->dockWidgetContents->setLayout(ui->gridLayout);
    this->setLayout(ui->gridLayout);

    this->rotation = 0;
    this->widthScreen = 240;
    this->heightScreen = 480;
    this->screenshot = QPixmap::fromImage(noScreenshotImage(this->widthScreen, this->heightScreen), Qt::AutoColor);
    this->ui->labelScreen->setPixmap(this->screenshot);

    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(takeScreenshot()));
    threadScreenshot.setSerialNum(serialNum);
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
    this->setWindowTitle(serialNum);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(takeScreenshot()));
    connect(ui->start,SIGNAL(clicked(bool)),this,SLOT(startTimer()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(stopTimer(bool)));
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
