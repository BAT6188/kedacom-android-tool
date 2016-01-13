#include "phoneconnectthread.h"

void PhoneConnectThread::run()
{
    int dataLength;
    bool ok, first = true;
    QString data,serialNumber,tmp;
    int serialLength=0;

    QTcpSocket *connectSocket = new QTcpSocket();
    connectSocket->connectToHost("127.0.0.1",5037,QTcpSocket::ReadWrite);
    if (connectSocket->waitForConnected(2000))
    {
        connectSocket->write("0012host:track-devices");
        connectSocket->waitForReadyRead(2000);
        data = connectSocket->read(4);
        if (data == "OKAY")
        {
            while (true)
            {
                if (!first)
                    connectSocket->waitForReadyRead(-1);
                first = false;
                data = connectSocket->read(4);
                tmp=data;
                qDebug() << "PhoneConnectThread data1:"+data;
                if (data == "")
                {
                    sleep(1);
                    continue;
                }
                dataLength = data.toInt(&ok, 16);
                if (dataLength == 0)
                {
                    emit this->connectionChanged(0,"");
                }
                else
                {
                    data = connectSocket->read(dataLength);
                    qDebug() << "PhoneConnectThread data2:"+data;
                    if (data.contains("device"))
                    {
                        serialLength = tmp.toInt(&ok, 16) - 8;
                    }
                    if (data.contains("recovery"))
                        serialLength = tmp.toInt(&ok, 16) - 10;

                    serialNumber = data;

                    serialNumber = serialNumber.left(serialLength);
                    if (data.contains("device"))
                        emit this->connectionChanged(1,serialNumber);
                    if (data.contains("recovery"))
                        emit this->connectionChanged(2,serialNumber);
                    if (data.contains("offline"))
                        emit this->connectionChanged(3,serialNumber);
                }
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
