#include "qtkplugingenerator_p.h"
#include "ui_qtkplugingeneratormainwindow.h"
#include "qtkplugingeneratoroptionsdialog_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/QTKPluginConstants>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorCodeModel>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorConstants>
#include <QTKCore/QTKUtils>

#include <QDebug>
#include <QListWidgetItem>
#include <QDir>
#include <QFileSystemModel>
#include <QTime>
#include <QMessageBox>
#include <QSettings>

#include <stdexcept>


class QTKTemporaryDir
{
public:

    static QString create(const QString& path = QString())
    {
        QString tmpPath = path;
        if (tmpPath.isEmpty())
        {
            tmpPath = "QTKplugingenerator";
        }
        tmpPath +=  "." + QTime::currentTime().toString("hhmmsszzz");

        QDir tmp = QDir::temp();
        if (!tmp.mkdir(tmpPath))
        {
            QString msg = QString("Creating temporary directory ") + tmpPath + " in "
                    + QDir::temp().canonicalPath() + " failed.";
            throw std::runtime_error(msg.toStdString());
        }

        tmp.cd(tmpPath);

        return tmp.canonicalPath();
    }
};

QTKPluginGenerator::QTKPluginGenerator(QTKPluginFramework* framework, QWidget *parent) :
    QMainWindow(parent),
    framework(framework), ui(new Ui::QTKPluginGeneratorMainWindow),
    mode(EDIT), previewModel(0)
{
    ui->setupUi(this);

    previewModel = new QFileSystemModel(this);
    ui->previewTreeView->setModel(previewModel);
    ui->previewTreeView->hideColumn(1);
    ui->previewTreeView->hideColumn(2);
    ui->previewTreeView->hideColumn(3);

    this->setStatusBar(0);

    connect(ui->actionOptions, SIGNAL(triggered(bool)), this, SLOT(menuOptionsTriggered()));
    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generateClicked()));
    connect(ui->previewButton, SIGNAL(clicked()), this, SLOT(previewClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->uiExtensionList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(extensionItemClicked(QListWidgetItem*)));
    connect(ui->previewTreeView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(previewIndexChanged(QModelIndex)));

    QList<QTKServiceReference> serviceRefs = framework->getPluginContext()->
            getServiceReferences("QTKPluginGeneratorAbstractUiExtension");
    QListIterator<QTKServiceReference> it(serviceRefs);
    while (it.hasNext())
    {
        QTKServiceReference serviceRef = it.next();
        QTKPluginGeneratorAbstractUiExtension* extension =
                qobject_cast<QTKPluginGeneratorAbstractUiExtension*>(framework->getPluginContext()->getService(serviceRef));
        qDebug() << "Service reference found";
        if (extension)
        {
            qDebug() << "inserted";
            int ranking = serviceRef.getProperty(QTKPluginConstants::SERVICE_RANKING).toInt();
            if (ranking > 0)
            {
                uiExtensionMap.insert(ranking, extension);
            }
            else
            {
                uiExtensionMap.insert(-1, extension);
            }
        }
    }

    int id = 0;
    foreach (QTKPluginGeneratorAbstractUiExtension* extension, uiExtensionMap)
    {
        idToExtensionMap.insert(id, extension);
        ui->extensionStack->addWidget(extension->getWidget());

        connect(extension, SIGNAL(errorMessageChanged(QString)), this, SLOT(errorMessageChanged(QString)));

        extension->validate();

        (new QListWidgetItem(extension->getTitle(), ui->uiExtensionList))->setData(Qt::UserRole, id);
        ++id;
    }

    ui->uiExtensionList->setCurrentRow(0);
    extensionClicked(idToExtensionMap[0]);
}

QTKPluginGenerator::~QTKPluginGenerator()
{
    delete ui;
    if (!previewDir.isEmpty())
    {
        QTKUtils::removeDirRecursively(previewDir);
    }
}

void QTKPluginGenerator::menuOptionsTriggered()
{
    QTKPluginGeneratorOptionsDialog optionsDialog;
    int result = optionsDialog.exec();
    if (result == QDialog::Accepted && mode == PREVIEW)
    {
        QString selPath;
        QString oldPreviewDir = previewDir;
        if (!ui->previewTreeView->selectionModel()->selection().isEmpty())
        {
            QModelIndex index = ui->previewTreeView->selectionModel()->selectedIndexes().front();
            selPath = previewModel->data(index, QFileSystemModel::FilePathRole).toString();
        }
        if (createPreview())
        {
            ui->modeStack->setCurrentWidget(ui->previewPage);
            ui->previewButton->setText(tr("<< Back"));
            ui->previewTreeView->expandAll();
            if (!selPath.isEmpty())
            {
                selPath.replace(oldPreviewDir, previewDir);
                QModelIndex index = previewModel->index(selPath);
                ui->previewTreeView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
                previewIndexChanged(index);
            }
        }
    }
}

void QTKPluginGenerator::previewClicked()
{
    if (mode == EDIT)
    {
        if (createPreview())
        {
            ui->modeStack->setCurrentWidget(ui->previewPage);
            ui->previewButton->setText(tr("<< Back"));
            ui->previewTreeView->expandAll();
            if (!ui->previewTreeView->selectionModel()->selection().isEmpty())
            {
                previewIndexChanged(ui->previewTreeView->selectionModel()->selectedIndexes().front());
            }
            mode = PREVIEW;
        }
    }
    else
    {
        ui->modeStack->setCurrentWidget(ui->editPage);
        ui->previewButton->setText(tr("Preview >>"));
        mode = EDIT;

        QTKUtils::removeDirRecursively(previewDir);
        previewDir.clear();
    }
}

void QTKPluginGenerator::generateClicked()
{
    try
    {
        createPlugin(ui->outputDirButton->directory());

        QMessageBox msgBox;
        msgBox.setText(tr("Successfully create plugin"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    catch (const std::runtime_error& error)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Creating the plugin failed."));
        msgBox.setInformativeText(QString::fromLatin1(error.what()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

QString QTKPluginGenerator::createPlugin(const QString& path)
{
    QTKServiceReference codeModelRef = framework->getPluginContext()->
            getServiceReference("QTKPluginGeneratorCodeModel");

    QTKPluginGeneratorCodeModel* codeModel =
            qobject_cast<QTKPluginGeneratorCodeModel*>(framework->getPluginContext()->getService(codeModelRef));
    codeModel->reset();

    // set global code model info from QSettings object
    QSettings settings;
    codeModel->setLicense(settings.value(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER).toString());

    foreach(QTKPluginGeneratorAbstractUiExtension* extension, idToExtensionMap)
    {
        extension->updateCodeModel();
    }

    QString pluginDir = path + "/" + codeModel->getSymbolicName(true);
    if (!QDir(path).mkdir(codeModel->getSymbolicName(true)))
    {
        QString msg(tr("Creating directory \"%1\" failed.").arg(pluginDir));
        throw std::runtime_error(msg.toStdString());
    }

    codeModel->create(pluginDir);
    return pluginDir;
}

void QTKPluginGenerator::previewIndexChanged(const QModelIndex& index)
{
    QString filePath = previewModel->data(index, QFileSystemModel::FilePathRole).toString();
    ui->previewTextLabel->setText(QDir(QString(filePath).replace(previewDir, ui->outputDirButton->directory())).absolutePath());

    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);
    ui->previewTextEdit->setText(textStream.readAll());
}

bool QTKPluginGenerator::createPreview()
{
    try
    {
        previewDir = QTKTemporaryDir::create();

        QString tmpPluginDir = createPlugin(previewDir);

        previewModel->setRootPath(tmpPluginDir);
        ui->previewTreeView->setRootIndex(previewModel->index(previewDir));
    }
    catch (const std::runtime_error& error)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Creating the preview failed."));
        msgBox.setInformativeText(QString::fromLatin1(error.what()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return false;
    }

    return true;
}

void QTKPluginGenerator::extensionItemClicked(QListWidgetItem* item)
{
    QTKPluginGeneratorAbstractUiExtension* extension = idToExtensionMap[item->data(Qt::UserRole).toInt()];
    extensionClicked(extension);
}

void QTKPluginGenerator::extensionClicked(QTKPluginGeneratorAbstractUiExtension* extension)
{
    ui->extensionStack->setCurrentWidget(extension->getWidget());
    ui->extensionMsgLabel->setText(extension->getTitle());
    this->errorMessageChanged(extension->getErrorMessage());
}

void QTKPluginGenerator::errorMessageChanged(const QString& errMsg)
{
    ui->extensionErrMsgLabel->setText(errMsg);

    bool enableButtons = false;
    if (errMsg.isEmpty())
    {
        enableButtons = true;
    }

    ui->previewButton->setEnabled(enableButtons);
    ui->generateButton->setEnabled(enableButtons);
}
