#include "qtkplugingeneratorabstractextension.h"
#include "qtkplugingeneratorcoreplugin_p.h"

#include <QVariant>

class QTKPluginGeneratorAbstractExtensionPrivate
{
public:

    QTKPluginGeneratorAbstractExtensionPrivate()
        : valid(true)
    {}

    bool valid;
    QString errorMessage;
    QHash<QString, QVariant> parameters;
};

QTKPluginGeneratorAbstractExtension::QTKPluginGeneratorAbstractExtension()
    : d_ptr(new QTKPluginGeneratorAbstractExtensionPrivate())
{
}

QTKPluginGeneratorAbstractExtension::~QTKPluginGeneratorAbstractExtension()
{
}

void QTKPluginGeneratorAbstractExtension::setParameter(const QHash<QString, QVariant>& params)
{
    Q_D(QTKPluginGeneratorAbstractExtension);
    d->parameters = params;
}

void QTKPluginGeneratorAbstractExtension::setParameter(const QString& name, const QVariant& value)
{
    Q_D(QTKPluginGeneratorAbstractExtension);
    d->parameters[name] = value;
}

QHash<QString, QVariant> QTKPluginGeneratorAbstractExtension::getParameter() const
{
    Q_D(const QTKPluginGeneratorAbstractExtension);
    return d->parameters;
}

bool QTKPluginGeneratorAbstractExtension::isValid() const
{
    Q_D(const QTKPluginGeneratorAbstractExtension);
    return d->valid;
}

void QTKPluginGeneratorAbstractExtension::validate()
{
    Q_D(QTKPluginGeneratorAbstractExtension);
    d->valid = verifyParameters(d->parameters);
}

void QTKPluginGeneratorAbstractExtension::updateCodeModel()
{
    Q_D(QTKPluginGeneratorAbstractExtension);
    this->updateCodeModel(d->parameters);
}

QString QTKPluginGeneratorAbstractExtension::getErrorMessage() const
{
    Q_D(const QTKPluginGeneratorAbstractExtension);
    return d->errorMessage;
}

QTKPluginGeneratorCodeModel* QTKPluginGeneratorAbstractExtension::getCodeModel() const
{
    return QTKPluginGeneratorCorePlugin::getInstance()->getCodeModel();
}

void QTKPluginGeneratorAbstractExtension::setErrorMessage(const QString& errorMsg)
{
    Q_D(QTKPluginGeneratorAbstractExtension);
    if (d->errorMessage != errorMsg)
    {
        d->errorMessage = errorMsg;
        emit errorMessageChanged(errorMsg);
    }
}
