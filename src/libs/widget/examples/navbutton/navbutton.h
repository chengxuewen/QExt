#ifndef NAVBUTTON_H
#define NAVBUTTON_H

#include <QWidget>

class QEXTNavButton;

namespace Ui
{
class NavButton;
}

class NavButton : public QWidget
{
    Q_OBJECT

public:
    explicit NavButton(QWidget *parent = 0);
    ~NavButton();

private:
    Ui::NavButton *ui;
    QList< QEXTNavButton * > btns1;
    QList< QEXTNavButton * > btns2;
    QList< QEXTNavButton * > btns3;
    QList< QEXTNavButton * > btns4;
    QList< QEXTNavButton * > btns5;
    QList< QEXTNavButton * > btns6;
    QList< QEXTNavButton * > btns7;

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

#endif // NAVBUTTON_H
