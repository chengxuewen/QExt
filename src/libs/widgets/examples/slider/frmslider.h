#ifndef FRMSLIDER_H
#define FRMSLIDER_H

#include <QWidget>

namespace Ui
{
class FrmSlider;
}

class FrmSlider : public QWidget
{
	Q_OBJECT

public:
    explicit FrmSlider(QWidget *parent = 0);
    ~FrmSlider();

private:
    Ui::FrmSlider *ui;

private slots:
    void initForm();
};

#endif // FRMSLIDER_H
