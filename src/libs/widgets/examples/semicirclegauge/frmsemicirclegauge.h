#ifndef FRMSEMICIRCLEGAUGE_H
#define FRMSEMICIRCLEGAUGE_H

#include <QWidget>

namespace Ui {
class FrmSemicircleGauge;
}

class FrmSemicircleGauge : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSemicircleGauge(QWidget *parent = 0);
    ~FrmSemicircleGauge();

private:
    Ui::FrmSemicircleGauge *ui;

private slots:
    void initForm();
};

#endif // FRMSEMICIRCLEGAUGE_H
