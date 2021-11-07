#ifndef FRMGAUGEMINI_H
#define FRMGAUGEMINI_H

#include <QWidget>

class QEXTScaleKnob;
class QLabel;

namespace Ui {
class FrmScaleKnob;
}

class FrmScaleKnob : public QWidget
{
    Q_OBJECT

public:
    explicit FrmScaleKnob(QWidget *parent = 0);
    ~FrmScaleKnob();

private:
    Ui::FrmScaleKnob *ui;
    QList<QEXTScaleKnob *> gauges;
    QList<QLabel *> labs;

private slots:
    void initForm();
    void valueChanged(double value);

private slots:
    void on_ckDouble_stateChanged(int arg1);
    void on_cboxPointerStyle_currentIndexChanged(int index);
};

#endif // FRMGAUGEMINI_H
