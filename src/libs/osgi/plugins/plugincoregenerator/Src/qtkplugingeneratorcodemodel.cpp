#include "qtkplugingeneratorcodemodel.h"

#include <QDir>
#include <QHash>

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

class QTKPluginGeneratorCodeModelPrivate
{
public:

    QHash<QString, QTKPluginGeneratorAbstractTemplate*> rootTemplates;
    QHash<QString, QString> contentMap;

    QString symbolicNameWithPeriods;
    QString symbolicNameWithUnderscores;
    QString exportMacro;
    QString exportMacroInclude;
    QString license;
};

class QTKPluginGeneratorFolderTemplate : public QTKPluginGeneratorAbstractTemplate
{
public:
    QTKPluginGeneratorFolderTemplate(const QString& name, QTKPluginGeneratorAbstractTemplate* parent = 0)
        : QTKPluginGeneratorAbstractTemplate(name, parent)
    {}

    QString generateContent()
    {
        return "";
    }

    void create(const QString& location)
    {
        QDir dir(location);
        if (dir.mkdir(this->objectName())) {
            QString currLocation = location + QDir::separator() + this->objectName();
            QListIterator<QObject*> it(this->children());
            while (it.hasNext()) {
                qobject_cast<QTKPluginGeneratorAbstractTemplate*>(it.next())->create(currLocation);
            }
        } else {
            throw QTKRuntimeException("The directory " + location + this->objectName() + " could not be created");
        }
    }
};

QTKPluginGeneratorCodeModel::QTKPluginGeneratorCodeModel()
    : d_ptr(new QTKPluginGeneratorCodeModelPrivate)
{
}

QTKPluginGeneratorCodeModel::~QTKPluginGeneratorCodeModel()
{
}

void QTKPluginGeneratorCodeModel::addContent(const QString& marker, const QString& content)
{
    Q_D(QTKPluginGeneratorCodeModel);
    d->contentMap[marker] = content;
}

QString QTKPluginGeneratorCodeModel::getContent(const QString& marker) const
{
    Q_D(const QTKPluginGeneratorCodeModel);
    if (d->contentMap.contains(marker))
    {
        return d->contentMap[marker];
    }
    return QString();
}

void QTKPluginGeneratorCodeModel::setExportMacro(const QString& exportMacro)
{
    Q_D(QTKPluginGeneratorCodeModel);
    d->exportMacro = exportMacro;
}

QString QTKPluginGeneratorCodeModel::getExportMacro() const
{
    Q_D(const QTKPluginGeneratorCodeModel);
    return d->exportMacro;
}

void QTKPluginGeneratorCodeModel::setExportMacroInclude(const QString& exportMacroInclude)
{
    Q_D(QTKPluginGeneratorCodeModel);
    d->exportMacroInclude = exportMacroInclude;
}

QString QTKPluginGeneratorCodeModel::getExportMacroInclude() const
{
    Q_D(const QTKPluginGeneratorCodeModel);
    return d->exportMacroInclude;
}

void QTKPluginGeneratorCodeModel::setSymbolicName(const QString& symbolicName)
{
    Q_D(QTKPluginGeneratorCodeModel);
    d->symbolicNameWithPeriods = QString(symbolicName).replace("_", ".");
    d->symbolicNameWithUnderscores = QString(symbolicName).replace(".", "_");
}

QString QTKPluginGeneratorCodeModel::getSymbolicName(bool withPeriods) const
{
    Q_D(const QTKPluginGeneratorCodeModel);
    if (withPeriods)
    {
        return d->symbolicNameWithPeriods;
    }
    return d->symbolicNameWithUnderscores;
}

void QTKPluginGeneratorCodeModel::setLicense(const QString& license)
{
    Q_D(QTKPluginGeneratorCodeModel);
    d->license = license;
}

QString QTKPluginGeneratorCodeModel::getLicense() const
{
    Q_D(const QTKPluginGeneratorCodeModel);
    return d->license;
}

void QTKPluginGeneratorCodeModel::addTemplate(QTKPluginGeneratorAbstractTemplate *templ,
                                              const QString& path)
{
    Q_D(QTKPluginGeneratorCodeModel);

    templ->setCodeModel(this);

    if (path.isEmpty())
    {
        d->rootTemplates.insert(templ->objectName(), templ);
        templ->setParent(this);
    }
    else
    {
        QTKPluginGeneratorAbstractTemplate* parentTemplate = 0;
        QStringList paths = path.split("/", QString::SkipEmptyParts);
        QStringListIterator it(paths);
        if (it.hasNext())
        {
            QString rootEntry = it.next();
            // search the root templates
            if (d->rootTemplates.contains(rootEntry))
            {
                if (!dynamic_cast<QTKPluginGeneratorFolderTemplate*>(d->rootTemplates[rootEntry]))
                {
                    throw QTKRuntimeException("The segment \"" + rootEntry + "\" in \"" + path + "\" is not a folder");
                }
                parentTemplate = d->rootTemplates[rootEntry];
            }
            else
            {
                parentTemplate = new QTKPluginGeneratorFolderTemplate(rootEntry);
                d->rootTemplates.insert(rootEntry, parentTemplate);
            }
            while (it.hasNext())
            {
                QString currEntry = it.next();
                QListIterator<QObject*> children(parentTemplate->children());
                bool childFound = false;
                while (children.hasNext())
                {
                    QObject* child = children.next();
                    if (child->objectName() == currEntry)
                    {
                        childFound = true;
                        parentTemplate = qobject_cast<QTKPluginGeneratorAbstractTemplate*>(child);
                        if (parentTemplate == 0)
                        {
                            throw QTKRuntimeException("The segment \"" + currEntry + "\" in \"" + path + "\" is not a folder");
                        }
                        break;
                    }
                }

                if (!childFound)
                {
                    parentTemplate = new QTKPluginGeneratorFolderTemplate(currEntry, parentTemplate);
                }
            }
        }

        templ->setParent(parentTemplate);
    }
}

QTKPluginGeneratorAbstractTemplate* QTKPluginGeneratorCodeModel::getTemplate(const QString& path) const
{
    Q_D(const QTKPluginGeneratorCodeModel);

    if (!path.contains("/"))
    {
        foreach(QTKPluginGeneratorAbstractTemplate* t, d->rootTemplates)
        {
            if (t->objectName() == path) return t;
            QTKPluginGeneratorAbstractTemplate* child =
                    t->findChild<QTKPluginGeneratorAbstractTemplate*>(path);
            if (child) return child;
        }
        return 0;
    }

    QStringList paths = path.split("/", QString::SkipEmptyParts);
    if (paths.empty()) return 0;

    QObject* currChild = d->rootTemplates[paths.front()];
    paths.pop_front();

    int depth = 0;
    foreach (QString curr, paths)
    {
        foreach (QObject* child, currChild->children())
        {
            if (child->objectName() == curr)
            {
                currChild = child;
                ++depth;
                break;
            }
        }
    }

    if (paths.size() == depth)
    {
        return qobject_cast<QTKPluginGeneratorAbstractTemplate*>(currChild);
    }

    return 0;
}

void QTKPluginGeneratorCodeModel::create(const QString& location)
{
    Q_D(QTKPluginGeneratorCodeModel);

    QListIterator<QTKPluginGeneratorAbstractTemplate*> it(d->rootTemplates.values());
    while (it.hasNext())
    {
        QTKPluginGeneratorAbstractTemplate* templ = it.next();
        templ->create(location);
    }
}

void QTKPluginGeneratorCodeModel::reset()
{
    Q_D(QTKPluginGeneratorCodeModel);
    qDeleteAll(d->rootTemplates.values());
    d->rootTemplates.clear();
}
