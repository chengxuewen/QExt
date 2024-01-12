#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>

#include <qextPatternInterface.h>

namespace Ui
{
class Dialog;
}

class LoginMediator;

class Dialog : public QDialog, public QExtPatternViewComponentInterface
{
Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void update(QExtPatternUpdateDataInterface *updateData);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
    LoginMediator *loginMediator;

private slots:
    void on_loginButton_clicked();
};

#endif // LOGINFORM_H
