#ifndef FORMICONBUTTON_H
#define FORMICONBUTTON_H

#include <QWidget>

namespace Ui {
class FormIconButton;
}

class FormIconButton : public QWidget
{
    Q_OBJECT

public:
    explicit FormIconButton(QWidget *parent = 0);
    ~FormIconButton();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    void init();

private:
    Ui::FormIconButton *ui;
};

#endif // FORMICONBUTTON_H
