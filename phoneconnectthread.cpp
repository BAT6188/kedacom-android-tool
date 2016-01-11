#include "phoneconnectthread.h"

void PhoneConnectThread::run()
{
    int dataLength;
    bool ok, first = true;
    QString data,serialNumber,tmp;
    int serialLength=0;

    this->socket = new QTcpSocket();
    this->socket->connectToHost("127.0.0.1",5037,QTcpSocket::ReadWrite);
    if (this->socket->waitForConnected(2000))
    {
        this->socket->write("0012host:track-devices");
        this->socket->waitForReadyRead(2000);
        data = this->socket->read(4);
        if (data == "OKAY")
        {

            while (true)
            {
                if (!first)
                    this->socket->waitForReadyRead(-1);
                first = false;

                data = this->socket->read(4);
                tmp=data;
                if (data == "")
                    continue;
                dataLength = data.toInt(&ok, 16);
                if (dataLength == 0)
                {
                    emit this->connectionChanged(1,"");
                }
                else
                {
                    data = this->socket->read(dataLength);

                    if (data.contains("device"))
                        serialLength = tmp.toInt(&ok, 16) - 8;
                    if (data.contains("recovery"))
                        serialLength = tmp.toInt(&ok, 16) - 10;

                    serialNumber = data;

                    serialNumber = serialNumber.left(serialLength);
                    if (data.contains("device"))
                        emit this->connectionChanged(2,serialNumber);
                    if (data.contains("recovery"))
                        emit this->connectionChanged(3,serialNumber);
                    if (data.contains("offline"))
                        emit this->connectionChanged(1,serialNumber);
                }
                qDebug() << serialNumber;
            }
        }
        else
        {
            emit this->connectionChanged(-1,"");
            return;
        }
    }
    else
    {
        emit this->connectionChanged(-1,"");
        return;
    }
}
