#ifndef QTKPLUGINGENERATORMAINEXTENSION_H
#define QTKPLUGINGENERATORMAINEXTENSION_H

#include "qtkplugingeneratorabstractuiextension.h"

#include "ui_qtkplugingeneratormainextension.h"

class QTKPluginGeneratorMainExtension : public QTKPluginGeneratorAbstractUiExtension
{
    Q_OBJECT

public:
    QTKPluginGeneratorMainExtension();

protected Q_SLOTS:

    void updateParameters();
    void symbolicNameChanged();
    void activatorClassChanged();

protected:

    bool verifyParameters(const QHash<QString, QVariant>& params);
    void updateCodeModel(const QHash<QString, QVariant>& params);

    QWidget* createWidget();

    void connectSignals();

    Ui::QTKPluginGeneratorMainExtension* ui;

};

#endif // QTKPLUGINGENERATORMAINEXTENSION_H
