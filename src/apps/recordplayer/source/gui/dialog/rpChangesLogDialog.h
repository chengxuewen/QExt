#ifndef _RPCHANGESLOGDIALOG_H
#define _RPCHANGESLOGDIALOG_H

#include <QDialog>

namespace Ui {
class RPChangesLogDialog;
}

class RPChangesLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RPChangesLogDialog(QWidget *parent = nullptr);
    ~RPChangesLogDialog();

protected:
    void initDialog();

private:
    Ui::RPChangesLogDialog *ui;
};

#endif // _RPCHANGESLOGDIALOG_H
