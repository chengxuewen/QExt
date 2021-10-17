#ifndef FRMRRANGESLIDE_H
#define FRMRRANGESLIDE_H

#include <QWidget>

namespace Ui
{
class frmRangeSlider;
}

class frmRangeSlider : public QWidget
{
	Q_OBJECT

public:
    explicit frmRangeSlider(QWidget *parent = 0);
    ~frmRangeSlider();

private:
    Ui::frmRangeSlider *ui;

private slots:
    void initForm();
};

#endif // FRMRRANGESLIDE_H
