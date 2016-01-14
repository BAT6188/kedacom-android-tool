#ifndef SCREENFORM_H
#define SCREENFORM_H

#include <QWidget>

namespace Ui {
class ScreenForm;
}

class ScreenForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenForm(QWidget *parent = 0);
    ~ScreenForm();

private:
    Ui::ScreenForm *ui;
};

#endif // SCREENFORM_H
