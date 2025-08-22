#ifndef _RPLOGDIALOG_H
#define _RPLOGDIALOG_H

#include <QDialog>

namespace Ui
{
class RPLogDialog;
}

class RPLogDialogPrivate;
class RPLogDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RPLogDialog(QWidget *parent = nullptr);
    ~RPLogDialog();

protected slots:
    void onClearLogButtonClicked();
    void onExportLogButtonClicked();

    void refreshLog();
    void exportLogFileText(const QString &log);

protected:
    void initDialog();

private:
    Ui::RPLogDialog *ui;
    QScopedPointer<RPLogDialogPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, RPLogDialog)
    Q_DISABLE_COPY(RPLogDialog)
};

#endif // _RPLOGDIALOG_H
