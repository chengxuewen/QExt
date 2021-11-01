#ifndef QTKPLUGINGENERATOROPTIONSDIALOG_H
#define QTKPLUGINGENERATOROPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class QTKPluginGeneratorOptionsDialog;
}

class QTKPluginGeneratorOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QTKPluginGeneratorOptionsDialog(QWidget *parent = 0);
    ~QTKPluginGeneratorOptionsDialog();

    void accept();

private:
    Ui::QTKPluginGeneratorOptionsDialog *ui;
};

#endif // QTKPLUGINGENERATOROPTIONSDIALOG_H
