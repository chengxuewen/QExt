#include "qtkplugingeneratorabstracttemplate.h"
#include "qtkplugingeneratorcodemodel.h"
#include "qtkplugingeneratorconstants.h"

#include <QHash>
#include <QFile>

class QTKPluginGeneratorAbstractTemplatePrivate
{
public:

    QTKPluginGeneratorAbstractTemplatePrivate()
        : codeModel(0)
    {}

    QTKPluginGeneratorCodeModel* codeModel;

    QString filename;
    QHash<QString, QStringList> contentMap;
};

QTKPluginGeneratorAbstractTemplate::QTKPluginGeneratorAbstractTemplate(
        const QString& name, QTKPluginGeneratorAbstractTemplate* parent)
    : QObject(parent), d_ptr(new QTKPluginGeneratorAbstractTemplatePrivate)
{
    this->setObjectName(name);
}

QTKPluginGeneratorAbstractTemplate::~QTKPluginGeneratorAbstractTemplate()
{

}

void QTKPluginGeneratorAbstractTemplate::setCodeModel(QTKPluginGeneratorCodeModel *codeModel)
{
    Q_D(QTKPluginGeneratorAbstractTemplate);
    d->codeModel = codeModel;
}

void QTKPluginGeneratorAbstractTemplate::setFilename(const QString& filename)
{
    Q_D(QTKPluginGeneratorAbstractTemplate);
    d->filename = filename;
}

QString QTKPluginGeneratorAbstractTemplate::getFilename() const
{
    Q_D(const QTKPluginGeneratorAbstractTemplate);

    QString filename = this->objectName();
    if(!d->filename.isEmpty())
    {
        filename = d->filename;
    }

    return filename;
}

void QTKPluginGeneratorAbstractTemplate::reset()
{
    Q_D(QTKPluginGeneratorAbstractTemplate);
    d->contentMap.clear();
}

void QTKPluginGeneratorAbstractTemplate::addContent(const QString &marker, const QString &content, Position pos)
{
    Q_D(QTKPluginGeneratorAbstractTemplate);
    switch (pos)
    {
    case PREPEND:
    {
        d->contentMap[marker].prepend(content);
        break;
    }
    case APPEND:
    {
        d->contentMap[marker].append(content);
        break;
    }
    case REPLACE:
    {
        QStringList& v = d->contentMap[marker];
        v.clear();
        v.append(content);
        break;
    }
    }
}

QStringList QTKPluginGeneratorAbstractTemplate::getContent(const QString &marker) const
{
    Q_D(const QTKPluginGeneratorAbstractTemplate);
    if (d->contentMap.contains(marker))
    {
        return d->contentMap[marker];
    }

    QString globalDefault = d->codeModel->getContent(marker);
    if (!globalDefault.isEmpty())
    {
        return QStringList(globalDefault);
    }

    return QStringList();
}

void QTKPluginGeneratorAbstractTemplate::create(const QString& location)
{
    QString filename = getFilename();

    const QString path = location + "/" + filename;
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(this->generateContent().toLatin1());
    file.close();
}

QStringList QTKPluginGeneratorAbstractTemplate::getMarkers() const
{
    return QTKPluginGeneratorConstants::getGlobalMarkers();
}

QString QTKPluginGeneratorAbstractTemplate::getSymbolicName(bool withPeriods) const
{
    Q_D(const QTKPluginGeneratorAbstractTemplate);
    return d->codeModel->getSymbolicName(withPeriods);
}
