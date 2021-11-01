#include "qtkqtresourcestreemodel.h"

class QTKQtResourceTreeNode;

class QTKQtResourceTreeItem
{
public:

    QTKQtResourceTreeItem(const QFileInfo& fileInfo, QTKQtResourceTreeNode* parent = 0);

    virtual ~QTKQtResourceTreeItem();

    virtual QTKQtResourceTreeItem* child(int row);

    virtual int childCount() const;

    int row();

    QVariant data(int role) const;

    QTKQtResourceTreeNode* parent() const;

protected:
    QFileInfo entry;
    QTKQtResourceTreeNode* parentNode;
};

class QTKQtResourceTreeNode : public QTKQtResourceTreeItem
{
public:

    QTKQtResourceTreeNode(const QFileInfo& dirInfo, QTKQtResourceTreeNode* parent = 0);

    ~QTKQtResourceTreeNode();

    QTKQtResourceTreeItem* child(int row);

    int childCount() const;

    int indexOf(QTKQtResourceTreeItem* child) const;

private:

    QList<QTKQtResourceTreeItem*> children;

};


QTKQtResourceTreeItem::QTKQtResourceTreeItem(const QFileInfo& fileInfo, QTKQtResourceTreeNode* parent)
    : entry(fileInfo), parentNode(parent)
{

}

QTKQtResourceTreeItem::~QTKQtResourceTreeItem()
{

}

QTKQtResourceTreeItem* QTKQtResourceTreeItem::child(int row)
{
    Q_UNUSED(row)

    return 0;
}

int QTKQtResourceTreeItem::childCount() const
{
    return 0;
}

int QTKQtResourceTreeItem::row()
{
    if (parentNode)
    {
        return parentNode->indexOf(this);
    }

    return 0;
}

QVariant QTKQtResourceTreeItem::data(int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (entry.isFile())
            return entry.fileName();

        QString lastDir = entry.absoluteFilePath();
        int i = lastDir.lastIndexOf('/');

        if (i == lastDir.size()-1) return lastDir;
        return lastDir.mid(i+1);
    }

    return QVariant();
}

QTKQtResourceTreeNode* QTKQtResourceTreeItem::parent() const
{
    return parentNode;
}


QTKQtResourceTreeNode::QTKQtResourceTreeNode(const QFileInfo& dirInfo, QTKQtResourceTreeNode* parent)
    : QTKQtResourceTreeItem(dirInfo, parent)
{
    QFileInfoList infoList = QDir(dirInfo.absoluteFilePath()).entryInfoList();
    QListIterator<QFileInfo> it(infoList);
    while (it.hasNext())
    {
        const QFileInfo& info = it.next();
        if (info.isFile())
        {
            children.push_back(new QTKQtResourceTreeItem(info, this));
        }
        else
        {
            children.push_back(new QTKQtResourceTreeNode(info, this));
        }
    }
}

QTKQtResourceTreeNode::~QTKQtResourceTreeNode()
{
    qDeleteAll(children);
}

QTKQtResourceTreeItem* QTKQtResourceTreeNode::child(int row)
{
    return children.value(row);
}

int QTKQtResourceTreeNode::childCount() const
{
    return children.size();
}

int QTKQtResourceTreeNode::indexOf(QTKQtResourceTreeItem* child) const
{
    return children.indexOf(child);
}


QTKQtResourcesTreeModel::QTKQtResourcesTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new QTKQtResourceTreeNode(QFileInfo(":/"));
}

QTKQtResourcesTreeModel::~QTKQtResourcesTreeModel()
{
    delete rootItem;
}

QVariant QTKQtResourcesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QTKQtResourceTreeItem* item = static_cast<QTKQtResourceTreeItem*>(index.internalPointer());
        return item->data(role);
    }

    return QVariant();
}

Qt::ItemFlags QTKQtResourcesTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant QTKQtResourcesTreeModel::headerData(int section, Qt::Orientation orientation,
                                             int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

QModelIndex QTKQtResourcesTreeModel::index(int row, int column,
                                           const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
        return createIndex(row, column, rootItem);

    QTKQtResourceTreeItem* parentItem = static_cast<QTKQtResourceTreeItem*>(parent.internalPointer());
    QTKQtResourceTreeItem* childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QTKQtResourcesTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QTKQtResourceTreeItem* childItem = static_cast<QTKQtResourceTreeItem*>(index.internalPointer());
    QTKQtResourceTreeItem* parentItem = childItem->parent();

    if (parentItem)
        return createIndex(parentItem->row(), 0, parentItem);

    return QModelIndex();
}

int QTKQtResourcesTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) return 0;

    if (!parent.isValid())
    {
        return 1;
    }
    else
    {
        QTKQtResourceTreeItem* parentItem = static_cast<QTKQtResourceTreeItem*>(parent.internalPointer());
        return parentItem->childCount();
    }
}

int QTKQtResourcesTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 1;
}
