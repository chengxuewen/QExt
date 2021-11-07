#ifndef FRMPROGRESSKNOB_H
#define FRMPROGRESSKNOB_H

#include <QWidget>

class QEXTProgressKnob;

namespace Ui {
class FrmProgressKnob;
}

class FrmProgressKnob : public QWidget
{
    Q_OBJECT

public:
    explicit FrmProgressKnob(QWidget *parent = 0);
    ~FrmProgressKnob();

private:
    Ui::FrmProgressKnob *ui;
    QList<QEXTProgressKnob *> gauges;

private slots:
    void initForm();
    void on_ckShowPointer_stateChanged(int arg1);
    void on_ckShowValue_stateChanged(int arg1);
    void on_cboxPointerStyle_currentIndexChanged(int index);
};

#endif // FRMPROGRESSKNOB_H
