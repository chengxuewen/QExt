#include "qtkplugingeneratorabstractuiextension.h"

class QTKPluginGeneratorAbstractUiExtensionPrivate
{
public:

    QTKPluginGeneratorAbstractUiExtensionPrivate()
        : extensionWidget(0)
    {

    }

    QWidget* extensionWidget;

    QString description;
    QString title;
    QString message;
    QIcon icon;
};

QTKPluginGeneratorAbstractUiExtension::QTKPluginGeneratorAbstractUiExtension()
    : d_ptr(new QTKPluginGeneratorAbstractUiExtensionPrivate())
{

}

QTKPluginGeneratorAbstractUiExtension::~QTKPluginGeneratorAbstractUiExtension()
{

}

QWidget* QTKPluginGeneratorAbstractUiExtension::getWidget()
{
    Q_D(QTKPluginGeneratorAbstractUiExtension);
    if (d->extensionWidget == 0)
    {
        d->extensionWidget = this->createWidget();
    }

    return d->extensionWidget;
}

QString QTKPluginGeneratorAbstractUiExtension::getDescription() const
{
    Q_D(const QTKPluginGeneratorAbstractUiExtension);
    return d->description;
}

QString QTKPluginGeneratorAbstractUiExtension::getTitle() const
{
    Q_D(const QTKPluginGeneratorAbstractUiExtension);
    return d->title;
}

QString QTKPluginGeneratorAbstractUiExtension::getMessage() const
{
    Q_D(const QTKPluginGeneratorAbstractUiExtension);
    return d->message;
}

QIcon QTKPluginGeneratorAbstractUiExtension::getIcon() const
{
    Q_D(const QTKPluginGeneratorAbstractUiExtension);
    return d->icon;
}

void QTKPluginGeneratorAbstractUiExtension::setDescription(const QString& description)
{
    Q_D(QTKPluginGeneratorAbstractUiExtension);
    if (d->description != description)
    {
        d->description = description;
        emit descriptionChanged(description);
    }
}

void QTKPluginGeneratorAbstractUiExtension::setTitle(const QString& title)
{
    Q_D(QTKPluginGeneratorAbstractUiExtension);
    if (d->title != title)
    {
        d->title = title;
        emit titleChanged(title);
    }
}

void QTKPluginGeneratorAbstractUiExtension::setMessage(const QString& msg)
{
    Q_D(QTKPluginGeneratorAbstractUiExtension);
    if (d->message != msg)
    {
        d->message = msg;
        emit messageChanged(msg);
    }
}

void QTKPluginGeneratorAbstractUiExtension::setIcon(const QIcon& icon)
{
    Q_D(QTKPluginGeneratorAbstractUiExtension);
    d->icon = icon;
    emit iconChanged(icon);
}

