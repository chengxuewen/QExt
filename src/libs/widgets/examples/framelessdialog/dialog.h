#ifndef DIALOG_H
#define DIALOG_H

#include "qextFramelessDialog.h"

namespace Ui {
class Dialog;
}

class Dialog : public QEXTFramelessDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

private slots:
    void initForm();
    void onTitleDoubleClicked();
    void onWindowStateChanged(bool max);

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // DIALOG_H
