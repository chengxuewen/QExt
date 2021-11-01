#ifndef QTKPLUGINGENERATORABSTRACTEXTENSION_H
#define QTKPLUGINGENERATORABSTRACTEXTENSION_H

#include "qtkplugingeneratorcore_global.h"

#include <QObject>
#include <QHash>

class QTKPluginGeneratorAbstractExtensionPrivate;
class QTKPluginGeneratorCodeModel;

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorAbstractExtension : public QObject
{
    Q_OBJECT

public:
    QTKPluginGeneratorAbstractExtension();
    virtual ~QTKPluginGeneratorAbstractExtension();

    //virtual void getCommandLineArgs() const = 0;

    void setParameter(const QHash<QString, QVariant>& params);
    void setParameter(const QString& name, const QVariant& value);
    QHash<QString, QVariant> getParameter() const;

    bool isValid() const;
    void validate();
    void updateCodeModel();

    QString getErrorMessage() const;

    QTKPluginGeneratorCodeModel* getCodeModel() const;

Q_SIGNALS:

    void errorMessageChanged(const QString&);

protected:

    void setErrorMessage(const QString& errMsg);

    virtual bool verifyParameters(const QHash<QString, QVariant>& params) = 0;
    virtual void updateCodeModel(const QHash<QString, QVariant>& params) = 0;

private:

    Q_DECLARE_PRIVATE(QTKPluginGeneratorAbstractExtension)

    const QScopedPointer<QTKPluginGeneratorAbstractExtensionPrivate> d_ptr;

};

#endif // QTKPLUGINGENERATORABSTRACTEXTENSION_H
