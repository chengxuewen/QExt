#ifndef QTKPLUGINGENERATORABSTRACTUIEXTENSION_H
#define QTKPLUGINGENERATORABSTRACTUIEXTENSION_H

#include "qtkplugingeneratorui_global.h"

#include <QTKPluginGeneratorCore/QTKPluginGeneratorAbstractExtension>

#include <QObject>
#include <QIcon>

class QWidget;
class QTKPluginGeneratorAbstractUiExtensionPrivate;

class QTK_PLUGINGENERATORUI_EXPORT QTKPluginGeneratorAbstractUiExtension : public QTKPluginGeneratorAbstractExtension
{

    Q_OBJECT

public:

    QTKPluginGeneratorAbstractUiExtension();
    virtual ~QTKPluginGeneratorAbstractUiExtension();

    QWidget* getWidget();

    QString getDescription() const;
    QString getTitle() const;

    QString getMessage() const;

    QIcon getIcon() const;

Q_SIGNALS:

    void descriptionChanged(const QString&);
    void titleChanged(const QString&);
    void messageChanged(const QString&);
    void iconChanged(const QIcon&);

protected:

    virtual QWidget* createWidget() = 0;

    void setDescription(const QString& description);
    void setTitle(const QString& title);

    void setMessage(const QString& msg);

    void setIcon(const QIcon& icon);

private:

    Q_DECLARE_PRIVATE(QTKPluginGeneratorAbstractUiExtension)

    const QScopedPointer<QTKPluginGeneratorAbstractUiExtensionPrivate> d_ptr;

};

#endif // QTKPLUGINGENERATORABSTRACTUIEXTENSION_H
