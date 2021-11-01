#include "qtkpluginresourcestreemodel.h"

#include <QTKPluginFramework/QTKPlugin>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginResourceTreeNode;

class QTKPluginResourceTreeItem
{
public:

    QTKPluginResourceTreeItem(const QString& path, QTKPluginResourceTreeNode* parent = 0);

    virtual ~QTKPluginResourceTreeItem();

    virtual QTKPluginResourceTreeItem* child(int row);

    virtual int childCount() const;

    int row();

    QVariant data(int role) const;

    QTKPluginResourceTreeNode* parent() const;

protected:
    const QString path;
    QTKPluginResourceTreeNode* parentNode;
};

class QTKPluginResourceTreeNode : public QTKPluginResourceTreeItem
{
public:

    QTKPluginResourceTreeNode(QSharedPointer<const QTKPlugin> plugin, const QString& path, QTKPluginResourceTreeNode* parent = 0);

    ~QTKPluginResourceTreeNode();

    QTKPluginResourceTreeItem* child(int row);

    int childCount() const;

    int indexOf(QTKPluginResourceTreeItem* child) const;

private:

    QSharedPointer<const QTKPlugin> plugin;
    QList<QTKPluginResourceTreeItem*> children;

};


QTKPluginResourceTreeItem::QTKPluginResourceTreeItem(const QString& path,
                                                     QTKPluginResourceTreeNode* parent)
    : path(path), parentNode(parent)
{

}

QTKPluginResourceTreeItem::~QTKPluginResourceTreeItem()
{

}

QTKPluginResourceTreeItem* QTKPluginResourceTreeItem::child(int row)
{
    Q_UNUSED(row)

    return 0;
}

int QTKPluginResourceTreeItem::childCount() const
{
    return 0;
}

int QTKPluginResourceTreeItem::row()
{
    if (parentNode)
    {
        return parentNode->indexOf(this);
    }

    return 0;
}

QVariant QTKPluginResourceTreeItem::data(int role) const
{
    if (role == Qt::DisplayRole)
    {
        QString p = path;
        if (p.endsWith('/')) p = p.left(p.size()-1);

        int i = p.lastIndexOf('/');

        return p.mid(i+1);
    }
    else if (role == Qt::UserRole)
    {
        if (this->parent())
        {
            return this->parent()->data(role).toString() + path;
        }
        else
        {
            return path;
        }
    }

    return QVariant();
}

QTKPluginResourceTreeNode* QTKPluginResourceTreeItem::parent() const
{
    return parentNode;
}


QTKPluginResourceTreeNode::QTKPluginResourceTreeNode(QSharedPointer<const QTKPlugin> plugin, const QString& path, QTKPluginResourceTreeNode* parent)
    : QTKPluginResourceTreeItem(path, parent), plugin(plugin)
{
    QStringList pathEntries = plugin->getResourceList(path);
    QStringListIterator it(pathEntries);
    while (it.hasNext())
    {
        const QString& entry = it.next();
        if (entry.endsWith('/'))
        {
            children.push_back(new QTKPluginResourceTreeNode(plugin, entry, this));
        }
        else
        {
            children.push_back(new QTKPluginResourceTreeItem(entry, this));
        }
    }
}

QTKPluginResourceTreeNode::~QTKPluginResourceTreeNode()
{
    qDeleteAll(children);
}

QTKPluginResourceTreeItem* QTKPluginResourceTreeNode::child(int row)
{
    return children.value(row);
}

int QTKPluginResourceTreeNode::childCount() const
{
    return children.size();
}

int QTKPluginResourceTreeNode::indexOf(QTKPluginResourceTreeItem* child) const
{
    return children.indexOf(child);
}


QTKPluginResourcesTreeModel::QTKPluginResourcesTreeModel(QSharedPointer<const QTKPlugin> plugin, QObject* parent)
    : QAbstractItemModel(parent), plugin(plugin)
{
    rootItem = new QTKPluginResourceTreeNode(plugin, "/");
}

QTKPluginResourcesTreeModel::~QTKPluginResourcesTreeModel()
{
    delete rootItem;
}

QVariant QTKPluginResourcesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ((role == Qt::DisplayRole) | (role == Qt::UserRole))
    {
        QTKPluginResourceTreeItem* item = static_cast<QTKPluginResourceTreeItem*>(index.internalPointer());
        return item->data(role);
    }

    return QVariant();
}

Qt::ItemFlags QTKPluginResourcesTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant QTKPluginResourcesTreeModel::headerData(int section, Qt::Orientation orientation,
                                                 int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

QModelIndex QTKPluginResourcesTreeModel::index(int row, int column,
                                               const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QTKPluginResourceTreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<QTKPluginResourceTreeItem*>(parent.internalPointer());

    QTKPluginResourceTreeItem* childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QTKPluginResourcesTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QTKPluginResourceTreeItem* childItem = static_cast<QTKPluginResourceTreeItem*>(index.internalPointer());
    QTKPluginResourceTreeItem* parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int QTKPluginResourcesTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) return 0;

    QTKPluginResourceTreeItem* parentItem;
    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<QTKPluginResourceTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int QTKPluginResourcesTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 1;
}
