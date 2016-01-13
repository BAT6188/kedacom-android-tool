#include "screendockwidget.h"
#include "ui_screendockwidget.h"

ScreenDockWidget::ScreenDockWidget(QWidget *parent,QString serialNum) :
    QDockWidget(parent),
    ui(new Ui::ScreenDockWidget)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);

    this->rotation = 0;
    this->widthScreen = 240;
    this->heightScreen = 480;
    this->screenshot = QPixmap::fromImage(noScreenshotImage(this->widthScreen, this->heightScreen), Qt::AutoColor);
    this->ui->labelScreen->setPixmap(this->screenshot);

    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(takeScreenshot()));
    threadScreenshot.setSerialNum(serialNum);
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(takeScreenshot()));
    timer->start(100);
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
    threadScreenshot.deleteLater();
    delete ui;
}
