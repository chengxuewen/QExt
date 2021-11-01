#ifndef QTKPLUGINGENERATOR_H
#define QTKPLUGINGENERATOR_H

#include <QTKPluginGeneratorUI/QTKPluginGeneratorAbstractUiExtension>
#include <QTKPluginFramework/QTKPluginFramework>

#include <QMainWindow>
#include <QMultiMap>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QListWidgetItem;
class QFileSystemModel;

#include <QModelIndex>

namespace Ui {
class QTKPluginGeneratorMainWindow;
}

class QTKPluginGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTKPluginGenerator(QTKPluginFramework* framework, QWidget *parent = 0);
    ~QTKPluginGenerator();

protected Q_SLOTS:

    void previewClicked();
    void generateClicked();
    void previewIndexChanged(const QModelIndex& index);
    void extensionItemClicked(QListWidgetItem* item);
    void errorMessageChanged(const QString& errMsg);

    void menuOptionsTriggered();

private:

    void extensionClicked(QTKPluginGeneratorAbstractUiExtension* extension);

    QString createPlugin(const QString& path);

    bool createPreview();

    enum GeneratorMode {
        EDIT,
        PREVIEW
    };

    QTKPluginFramework *const framework;
    Ui::QTKPluginGeneratorMainWindow *ui;
    GeneratorMode mode;

    QFileSystemModel* previewModel;

    QString previewDir;

    QMultiMap<int, QTKPluginGeneratorAbstractUiExtension*> uiExtensionMap;
    QHash<int, QTKPluginGeneratorAbstractUiExtension*> idToExtensionMap;

};

#endif // QTKPLUGINGENERATOR_H
