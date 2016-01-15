#ifndef PHONEDOCKWIDGET_H
#define PHONEDOCKWIDGET_H

#include <QDockWidget>
#include <phone.h>
#include <phonedetailwidget.h>
#include <screendockwidget.h>

namespace Ui {
class PhoneDockWidget;
}

class PhoneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhoneDockWidget(QWidget *parent = 0,Phone *p = 0);
    ~PhoneDockWidget();

private slots:
    void showDetail();
    void showScreen();

private:
    Ui::PhoneDockWidget *ui;
    Phone *p;
    PhoneDetailWidget *pdw;
    ScreenDockWidget *screenDockWidget;
};

#endif // PHONEDOCKWIDGET_H
