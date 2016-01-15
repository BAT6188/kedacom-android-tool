#ifndef PHONEDETAILWIDGET_H
#define PHONEDETAILWIDGET_H

#include <QWidget>
#include <phone.h>
#include <QTimer>
#include <adbprocess.h>

namespace Ui {
class PhoneDetailWidget;
}

class PhoneDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneDetailWidget(QWidget *parent = 0,Phone *p = 0);
    ~PhoneDetailWidget();

private slots:
    void showCPUInfo();

private:
    Ui::PhoneDetailWidget *ui;
    Phone *phone;
    QTimer *timer;
};

#endif // PHONEDETAILWIDGET_H
