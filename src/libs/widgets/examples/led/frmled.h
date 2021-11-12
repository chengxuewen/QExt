#ifndef FRMLED_H
#define FRMLED_H

#include <QWidget>

namespace Ui {
class FrmLED;
}

class FrmLED : public QWidget
{
    Q_OBJECT

public:
    explicit FrmLED(QWidget *parent = 0);
    ~FrmLED();

private:
    Ui::FrmLED *ui;

private slots:
    void initForm();
};

#endif // FRMLED_H
