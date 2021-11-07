#ifndef FRMSLIDERSELECT_H
#define FRMSLIDERSELECT_H

#include <QWidget>

class QEXTSelectSlider;

namespace Ui
{
class frmSelectSlider;
}

class frmSelectSlider : public QWidget
{
	Q_OBJECT

public:
    explicit frmSelectSlider(QWidget *parent = 0);
    ~frmSelectSlider();

private:
    Ui::frmSelectSlider *ui;
    QList<QEXTSelectSlider *> sliders;

private slots:
    void initForm();

private slots:
    void valueChanged(int leftValue, int rightValue);
    void rangeChanged(int rangeValue);
};

#endif // FRMSLIDERSELECT_H
