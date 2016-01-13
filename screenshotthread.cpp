#include "screenshotthread.h"

QImage noScreenshotImage(int width, int height)
{
    int i, j;
    QImage image = QImage(width, height, QImage::Format_ARGB32);
    for (i=0; i < height; i++){
        for (j=0; j<width; j++){
            if (i <= 1 || j <= 1 ||\
                i >= height - 2 || j >= width - 2 ||\
                (i <= height*j/width + 1 && i >= height*j/width - 2)||\
                (i <= (height*(-j)/width+height) + 1 && i >= (height*(-j)/width+height) - 2))
                image.setPixel(j, i, qRgba(0,0,0,255));
            else
                image.setPixel(j, i, qRgba(255, 255, 255, 255));
        }
    }
    return image;
}
QImage rgb565toQImage(QByteArray data, unsigned int bytesPerPixel, unsigned int width,
                                        unsigned int height, unsigned int redOffset, unsigned int redSize,
                                        unsigned int blueOffset, unsigned int blueSize, unsigned int greenOffset,
                                        unsigned int greenSize, unsigned int alfaOffset, unsigned int alfaSize)
{
    QImage image = QImage(width, height,QImage::Format_RGB888);
    unsigned int i, j, k;
    unsigned int temp, alfa, red, green, blue;
    unsigned char a;
    for (i=0; i < height; i++){
        for (j=0; j<width; j++){
            temp = 0;
            for (k=0; k< bytesPerPixel;k++){
                temp = temp<<8;
                a = data[i*width*bytesPerPixel + j*bytesPerPixel + 3-k];
                temp = temp | a;
            }

            red = (temp & ((0xFF >> (8 - redSize)) << redOffset)) >> redOffset;
            green = (temp & ((0xFF >> (8 - greenSize)) << greenOffset)) >> greenOffset;
            blue = (temp & ((0xFF >> (8 - blueSize)) << blueOffset)) >> blueOffset;
            alfa = (temp & ((0xFF >> (8 - alfaSize)) << alfaOffset)) >> alfaOffset;

            red = (red << (8 - redSize)) | (red >> (redSize - (8 - redSize)));
            green = (green << (8 - greenSize)) | (green >> (greenSize - (8 - greenSize)));
            blue = (blue << (8 - blueSize)) | (blue >> (blueSize - (8 - blueSize)));
            alfa = (alfa << (8 - alfaSize)) | (alfa >> (alfaSize - (8 - alfaSize)));

            image.setPixel(j, i, qRgba(red, green, blue, alfa));
        }
    }
    return image;
}
unsigned int bytes_to_int(QByteArray data, int start)
{
    unsigned int result=0;
    unsigned char temp;
    temp = data[start + 3];
    result = result | temp;
    result = result << 8;
    temp = data[start + 2];
    result = result | temp;
    result = result << 8;
    temp = data[start + 1];
    result = result | temp;
    result = result << 8;
    temp = data[start];
    result = result | temp;

    return result;
}

void ThreadScreenshot::run()
{
    QByteArray data, imageData;
    QImage image;
    QString tmp;
    bool recovery=false;
    unsigned int width=0, height=0, redSize=0, greenSize=0, blueSize=0, alfaSize=0;
    unsigned int redOffset=0, greenOffset=0, blueOffset=0, alfaOffset=0;
    unsigned int bytesPerPixel=0, dataSize=0;

    QTcpSocket *shotsocket = new QTcpSocket();
    shotsocket->connectToHost("127.0.0.1",5037,QTcpSocket::ReadWrite);
    //serialNumber = "0123456789";

    if (!serialNumber.isEmpty())
    {
        //SCREENSHOT
        if (shotsocket->waitForConnected(2000))
        {
            tmp.setNum(serialNumber.length()+15, 16);
            tmp = tmp.rightJustified(4, '0');

            shotsocket->write(tmp.toLatin1() + "host:transport:" + serialNumber.toLatin1());
            shotsocket->waitForReadyRead(2000);
            data = shotsocket->read(4);
            if (data == "OKAY")
            {
                shotsocket->write("000Cframebuffer:");
                shotsocket->waitForReadyRead(2000);
                data = shotsocket->read(4);
                if (data == "OKAY")
                {
                    shotsocket->waitForReadyRead(2000);
                    data = shotsocket->read(52);
                    if (recovery)
                    {
                        dataSize = bytes_to_int(data,4);
                        width = bytes_to_int(data, 8);
                        height = bytes_to_int(data, 12);
                        bytesPerPixel = dataSize/width/height;
                        redOffset = 11;
                        redSize = 5;
                        blueOffset = 0;
                        blueSize = 5;
                        greenOffset = 5;
                        greenSize = 6;
                        alfaOffset = 0;
                        alfaSize = 0;
                        shotsocket->write("00");
                    }
                    else
                    {
                        bytesPerPixel = bytes_to_int(data, 4)/8;
                        width = bytes_to_int(data, 12);
                        height = bytes_to_int(data, 16);
                        redOffset = bytes_to_int(data, 20);
                        redSize = bytes_to_int(data, 24);
                        blueOffset = bytes_to_int(data, 28);
                        blueSize = bytes_to_int(data, 32);
                        greenOffset = bytes_to_int(data, 36);
                        greenSize = bytes_to_int(data, 40);
                        alfaOffset = bytes_to_int(data, 44);
                        alfaSize = bytes_to_int(data, 48);
                    }
                    if ( width == 0 || height == 0 || bytesPerPixel == 0)
                    {
                        emit gotScreenshot(noScreenshotImage(this->widthScreen, this->heightScreen), this->widthScreen, this->heightScreen);
                    }
                    else
                    {
                        qDebug() << "screenshotthread emit";
                        do{
                            shotsocket->waitForReadyRead(1000);
                            imageData.append(shotsocket->readAll());
                        }while((unsigned int)imageData.size() < bytesPerPixel*width*height);
                        image = rgb565toQImage(imageData, bytesPerPixel, width, height, redOffset, redSize,
                                               blueOffset, blueSize, greenOffset, greenSize, alfaOffset, alfaSize);
                        emit gotScreenshot(image, width, height);
                    }

                }
                else
                {
                    emit gotScreenshot(noScreenshotImage(this->widthScreen, this->heightScreen), this->widthScreen, this->heightScreen);
                }
            }
            else
            {
                emit gotScreenshot(noScreenshotImage(this->widthScreen, this->heightScreen), this->widthScreen, this->heightScreen);
            }
            shotsocket->disconnectFromHost();
        }
     }//END SCREENSHOT
}

void ThreadScreenshot::setSerialNum(QString serialNum)
{
    this->serialNumber = serialNum;
    qDebug() << "ThreadScreenShot:"+this->serialNumber;
}
