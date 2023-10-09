#ifndef FRMNAVIGATIONBUTTON_H
#define FRMNAVIGATIONBUTTON_H

#include <QWidget>

class QExtNavigationButton;

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
    QList< QExtNavigationButton * > btns1;
    QList< QExtNavigationButton * > btns2;
    QList< QExtNavigationButton * > btns3;
    QList< QExtNavigationButton * > btns4;
    QList< QExtNavigationButton * > btns5;
    QList< QExtNavigationButton * > btns6;
    QList< QExtNavigationButton * > btns7;

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
