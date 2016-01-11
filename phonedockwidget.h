#ifndef PHONEDOCKWIDGET_H
#define PHONEDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class PhoneDockWidget;
}

class PhoneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit PhoneDockWidget(QWidget *parent = 0);
    ~PhoneDockWidget();

private:
    Ui::PhoneDockWidget *ui;
};

#endif // PHONEDOCKWIDGET_H
