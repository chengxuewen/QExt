#ifndef FRMCIRCLEGAUGE_H
#define FRMCIRCLEGAUGE_H

#include <QWidget>

namespace Ui {
class FrmCircleGauge;
}

class FrmCircleGauge : public QWidget
{
    Q_OBJECT

public:
    explicit FrmCircleGauge(QWidget *parent = 0);
    ~FrmCircleGauge();

private:
    Ui::FrmCircleGauge *ui;

private slots:
    void initForm();
    void on_cboxPieStyle_currentIndexChanged(int index);
    void on_cboxPointerStyle_currentIndexChanged(int index);
    void on_ckAnimation_stateChanged(int arg1);
};

#endif // FRMCIRCLEGAUGE_H
