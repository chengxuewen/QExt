#ifndef QTKPLUGINGENERATORABSTRACTTEMPLATE_H
#define QTKPLUGINGENERATORABSTRACTTEMPLATE_H

#include "qtkplugingeneratorcore_global.h"

#include <QObject>
#include <QScopedPointer>
#include <QStringList>

class QTKPluginGeneratorCodeModel;
class QTKPluginGeneratorAbstractTemplatePrivate;

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorAbstractTemplate : public QObject
{
    Q_OBJECT

public:
    enum Position {
        PREPEND,
        APPEND,
        REPLACE
    };

    QTKPluginGeneratorAbstractTemplate(const QString& name, QTKPluginGeneratorAbstractTemplate* parent = 0);

    virtual ~QTKPluginGeneratorAbstractTemplate();

    void setFilename(const QString& filename);
    QString getFilename() const;

    void addContent(const QString& marker, const QString& content, Position pos = APPEND);

    QStringList getContent(const QString& marker) const;

    virtual void create(const QString& location);

    void reset();

    virtual QStringList getMarkers() const;

    virtual QString generateContent() = 0;

protected:

    QString getSymbolicName(bool withPeriods = false) const;

private:

    friend class QTKPluginGeneratorCodeModel;

    Q_DECLARE_PRIVATE(QTKPluginGeneratorAbstractTemplate)

    void setCodeModel(QTKPluginGeneratorCodeModel* codeModel);

    const QScopedPointer<QTKPluginGeneratorAbstractTemplatePrivate> d_ptr;
};

#endif // QTKPLUGINGENERATORABSTRACTTEMPLATE_H
