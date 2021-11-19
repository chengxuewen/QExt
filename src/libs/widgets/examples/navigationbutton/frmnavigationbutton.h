#ifndef FRMNAVIGATIONBUTTON_H
#define FRMNAVIGATIONBUTTON_H

#include <QWidget>

class QEXTNavigationButton;

namespace Ui
{
class FrmNavigationButton;
}

class FrmNavigationButton : public QWidget
{
    Q_OBJECT

public:
    explicit FrmNavigationButton(QWidget *parent = 0);
    ~FrmNavigationButton();

private:
    Ui::FrmNavigationButton *ui;
    QList< QEXTNavigationButton * > btns1;
    QList< QEXTNavigationButton * > btns2;
    QList< QEXTNavigationButton * > btns3;
    QList< QEXTNavigationButton * > btns4;
    QList< QEXTNavigationButton * > btns5;
    QList< QEXTNavigationButton * > btns6;
    QList< QEXTNavigationButton * > btns7;

private slots:
    void initForm();
    void buttonClick1();
    void buttonClick2();
    void buttonClick3();
    void buttonClick4();
    void buttonClick5();
    void buttonClick6();
    void buttonClick7();
};

#endif // FRMNAVIGATIONBUTTON_H
