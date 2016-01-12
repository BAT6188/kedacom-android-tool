#ifndef PHONEDOCKWIDGET_H
#define PHONEDOCKWIDGET_H

#include <QDockWidget>
#include <phone.h>

namespace Ui {
class PhoneDockWidget;
}

class PhoneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhoneDockWidget(QWidget *parent = 0);
    ~PhoneDockWidget();
public slots:
    void slotConnectionChanged(int,QString);
private:
    Ui::PhoneDockWidget *ui;
    QMap<int,Phone*> phoneMap;
};

#endif // PHONEDOCKWIDGET_H
