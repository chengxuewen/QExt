#ifndef QTKPLUGINGENERATORCODEMODEL_H
#define QTKPLUGINGENERATORCODEMODEL_H

#include <QObject>
#include <QScopedPointer>

#include "qtkplugingeneratorabstracttemplate.h"
#include "qtkplugingeneratorcore_global.h"

class QTKPluginGeneratorCodeModelPrivate;

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorCodeModel : public QObject
{
    Q_OBJECT

public:
    QTKPluginGeneratorCodeModel();

    virtual ~QTKPluginGeneratorCodeModel();

    void addTemplate(QTKPluginGeneratorAbstractTemplate* templ, const QString& path = "");

    QTKPluginGeneratorAbstractTemplate* getTemplate(const QString& path) const;

    void addContent(const QString& marker, const QString& content);
    QString getContent(const QString& marker) const;

    void setExportMacro(const QString& exportMacro);
    QString getExportMacro() const;

    void setExportMacroInclude(const QString& exportMacroInclude);
    QString getExportMacroInclude() const;

    void setSymbolicName(const QString& symbolicName);
    QString getSymbolicName(bool withPeriods = false) const;

    void setLicense(const QString& license);
    QString getLicense() const;

    void create(const QString& location);

    void reset();

private:

    Q_DECLARE_PRIVATE(QTKPluginGeneratorCodeModel)

    const QScopedPointer<QTKPluginGeneratorCodeModelPrivate> d_ptr;


};

#endif // QTKPLUGINGENERATORCODEMODEL_H
