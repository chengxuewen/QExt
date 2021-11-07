#ifndef FRMTHERMOMETER_H
#define FRMTHERMOMETER_H

#include <QWidget>

namespace Ui
{
class frmThermometer;
}

class frmThermometer : public QWidget
{
	Q_OBJECT

public:
    explicit frmThermometer(QWidget *parent = 0);
    ~frmThermometer();

private:
    Ui::frmThermometer *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMTHERMOMETER_H
