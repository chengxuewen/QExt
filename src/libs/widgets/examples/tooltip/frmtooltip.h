#ifndef FRMTOOLTIP_H
#define FRMTOOLTIP_H

#include <QWidget>

namespace Ui
{
class FrmTooltip;
}

class FrmTooltip : public QWidget
{
	Q_OBJECT

public:
    explicit FrmTooltip(QWidget *parent = 0);
    ~FrmTooltip();

private:
    Ui::FrmTooltip *ui;

private slots:
    void initForm();
};

#endif // FRMTOOLTIP_H
