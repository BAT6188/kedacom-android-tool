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
    void showMe();
    void closeEvent(QCloseEvent *e);

private slots:
    void showCPUInfo();
    void showMemInfo();
    void radioChanged();
private:
    Ui::PhoneDetailWidget *ui;
    Phone *phone;
    QTimer *timer;
    QTimer *meminfoTimer;
    QMap<QString,QColor> nameColor;
};

#endif // PHONEDETAILWIDGET_H
