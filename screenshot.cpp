#include "screenshot.h"
#include "ui_screenshot.h"
#include <QTimer>

ScreenShot::ScreenShot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenShot)
{
    ui->setupUi(this);
    this->rotation = 0;
    this->widthScreen = 480;
    this->heightScreen = 960;
    this->screenshot = QPixmap::fromImage(noScreenshotImage(this->widthScreen, this->heightScreen), Qt::AutoColor);
    this->ui->labelScreen->setPixmap(this->screenshot);

    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(takeScreenshot()));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(takeScreenshot()));
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
    //timer->start(200);
}

void ScreenShot::showScreenshot(QImage image, int width, int height)
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

void ScreenShot::takeScreenshot()
{
    threadScreenshot.widthScreen = this->ui->labelScreen->width();
    threadScreenshot.heightScreen = this->ui->labelScreen->height();
    threadScreenshot.start();
    //connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
}

ScreenShot::~ScreenShot()
{
    delete ui;
}
