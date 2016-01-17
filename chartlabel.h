#ifndef CHARTLABEL_H
#define CHARTLABEL_H

#include <QObject>
#include <QLabel>
#include <QMap>

class ChartLabel : public QLabel
{
public:
    ChartLabel(QWidget *parent);

    int totalValue;
    QMap<QString,int> nameValue;
    QMap<QString, QColor> nameColor;
    void setValue(QMap<QString,int>,QMap<QString, QColor>,int totalValue);
private:
    void paintEvent(QPaintEvent *event);
};

#endif // CHARTLABEL_H
