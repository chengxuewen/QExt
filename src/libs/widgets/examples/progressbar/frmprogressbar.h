#ifndef FRMPROGRESSBAR_H
#define FRMPROGRESSBAR_H

#include <QWidget>

namespace Ui
{
class frmProgressBar;
}

class frmProgressBar : public QWidget
{
	Q_OBJECT

public:
    explicit frmProgressBar(QWidget *parent = 0);
    ~frmProgressBar();

private:
    Ui::frmProgressBar *ui;

private slots:
    void initForm();
};

#endif // FRMPROGRESSBAR_H
