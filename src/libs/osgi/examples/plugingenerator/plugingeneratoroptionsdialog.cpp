#include "qtkplugingeneratoroptionsdialog_p.h"
#include "ui_qtkplugingeneratoroptionsdialog.h"

#include <QTKPluginGeneratorCore/QTKPluginGeneratorConstants>

#include <QSettings>

QTKPluginGeneratorOptionsDialog::QTKPluginGeneratorOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTKPluginGeneratorOptionsDialog)
{
    ui->setupUi(this);

    QSettings settings;
    ui->licenseEdit->setPlainText(settings.value(
                                      QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER).toString());
}

QTKPluginGeneratorOptionsDialog::~QTKPluginGeneratorOptionsDialog()
{
    delete ui;
}

void QTKPluginGeneratorOptionsDialog::accept()
{
    QSettings settings;
    settings.setValue(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER,
                      ui->licenseEdit->toPlainText());

    QDialog::accept();
}
