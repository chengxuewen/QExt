#ifndef FRMRINGCOMPASS_H
#define FRMRINGCOMPASS_H

#include <QWidget>

namespace Ui {
class FrmRingCompass;
}

class FrmRingCompass : public QWidget
{
    Q_OBJECT

public:
    explicit FrmRingCompass(QWidget *parent = 0);
    ~FrmRingCompass();

private slots:
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::FrmRingCompass *ui;
};

#endif // FRMRINGCOMPASS_H
