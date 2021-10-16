#ifndef FRMPROGRESSPIE_H
#define FRMPROGRESSPIE_H

#include <QWidget>

class QEXTProgressPie;

namespace Ui
{
class frmProgressPie;
}

class frmProgressPie : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressPie(QWidget *parent = 0);
    ~frmProgressPie();

private:
    Ui::frmProgressPie *ui;

private slots:
    void initForm();
	void connectToSlider(QEXTProgressPie *bar);
};

#endif // FRMPROGRESSPIE_H
