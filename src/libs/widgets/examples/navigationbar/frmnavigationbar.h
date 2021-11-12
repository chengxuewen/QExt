#ifndef FRMNAVGATIONBAR_H
#define FRMNAVGATIONBAR_H

#include <QWidget>

class QEXTNavigationBar;

namespace Ui
{
class FrmNavigationBar;
}

class FrmNavigationBar : public QWidget
{
	Q_OBJECT

public:
    explicit FrmNavigationBar(QWidget *parent = 0);
    ~FrmNavigationBar();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::FrmNavigationBar *ui;

private slots:
	void initForm();
    void setIndex();
};

#endif // FRMNAVGATIONBAR_H
