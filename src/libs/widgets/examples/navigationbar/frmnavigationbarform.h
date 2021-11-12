#ifndef FRMNAVIGATIONBARFORM_H
#define FRMNAVIGATIONBARFORM_H

#include <QWidget>

namespace Ui
{
class FrmNavigationBarForm;
}

class FrmNavigationBarForm : public QWidget
{
	Q_OBJECT

public:
    explicit FrmNavigationBarForm(QWidget *parent = 0);
    ~FrmNavigationBarForm();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::FrmNavigationBarForm *ui;

private slots:
	void initForm();
    void currentItemChanged(int index, const QString &item);
    void setIndex();
};

#endif // FRMNAVIGATIONBARFORM_H
