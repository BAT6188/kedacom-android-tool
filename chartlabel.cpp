#include "chartlabel.h"
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QPaintEvent>
#include <QDebug>

ChartLabel::ChartLabel(QWidget *parent) : QLabel(parent)
{
//    nameValue["one"] = 10;
//    nameValue["two"] = 20;
//    nameValue["three"] = 5;

//    totalValue = 60;
//    nameColor["one"] = Qt::red;
//    nameColor["two"] = Qt::black;
//    nameColor["three"] = Qt::blue;
}

void ChartLabel::setValue(QMap<QString,int> nameValue,QMap<QString, QColor> nameColor,int totalValue)
{
    this->nameValue = nameValue;
    this->nameColor = nameColor;
    this->totalValue = totalValue;
}

void ChartLabel::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
    QPainter painter(this);

    QBrush background = painter.brush();
    QPen foreground(Qt::black);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), background);
    painter.setPen(foreground);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect pieRect = QRect(5, 5, 100, 100);

    QMapIterator<QString, int> i(nameValue);
    int startAngle = 0;
    int endAngle = 0;
    while (i.hasNext()) {
        i.next();
        qDebug() << nameColor[i.key()];
        QBrush pieBrush(nameColor[i.key()]);
        painter.setBrush(pieBrush);
        endAngle = 360*nameValue[i.key()]/totalValue;
        qDebug() << endAngle;
        painter.drawPie(pieRect,16*startAngle,16*endAngle);
        startAngle += endAngle;

        //left
        QBrush padBrush(QColor(Qt::cyan));
        painter.setBrush(padBrush);
        painter.drawPie(pieRect,16*startAngle,16*(360-startAngle));
    }
}

