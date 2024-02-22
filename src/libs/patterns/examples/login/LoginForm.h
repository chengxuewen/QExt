#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>

#include <qextMVCInterface.h>

namespace Ui
{
class Dialog;
}

class LoginMediator;

class Dialog : public QDialog, public QExtMVCViewComponentInterface
{
Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void update(QExtMVCUpdateDataInterface *updateData);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    LoginMediator *loginMediator;

private slots:
    void on_loginButton_clicked();
};

#endif // LOGINFORM_H
