#include <qextPropertyModel.h>

#include <QDebug>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QMouseEvent>
#include <QPushButton>
#include <QApplication>
#include <QDoubleSpinBox>
#include <QDoubleSpinBox>

QExtPropertyModelItem::QExtPropertyModelItem()
    : mEnable(true)
    , mParent(QEXT_NULLPTR)
{
}

QExtPropertyModelItem::~QExtPropertyModelItem()
{
    if (!mChildrenList.isEmpty())
    {
        QList<QExtPropertyModelItem *>::Iterator iter;
        for (iter = mChildrenList.begin(); iter < mChildrenList.end(); ++iter)
        {
            this->removeChild(*iter);
            (*iter)->deleteLater();
        }
        mChildrenList.clear();
    }
}

int QExtPropertyModelItem::childrenCount() const
{
    return mChildrenList.size();
}

int QExtPropertyModelItem::childIndexOf(QExtPropertyModelItem *child) const
{
    return mChildrenList.indexOf(child);
}

QExtPropertyModelItem *QExtPropertyModelItem::child(int index) const
{
    Q_ASSERT_X(index >= 0 && index < mChildrenList.size(), "QExtPropertyModelItem::child()", "index out of range");
    return mChildrenList.at(index);
}

QList<QExtPropertyModelItem *> QExtPropertyModelItem::childrenList() const
{
    return mChildrenList;
}

void QExtPropertyModelItem::appendChild(QExtPropertyModelItem *child)
{
    if (!mChildrenList.contains(child))
    {
        emit this->childAboutToBeAppended(child);
        child->setParent(this);
        mChildrenList.append(child);
        connect(child, SIGNAL(beginResetModel()), this, SIGNAL(beginResetModel()));
        connect(child, SIGNAL(endResetModel()), this, SIGNAL(endResetModel()));
        connect(child, SIGNAL(requestClosedEditor(QWidget*)), this, SIGNAL(requestClosedEditor(QWidget*)));
        connect(child, SIGNAL(childAboutToBeAppended(QExtPropertyModelItem*)), this, SIGNAL(childAboutToBeAppended(QExtPropertyModelItem*)));
        connect(child, SIGNAL(childAppended(QExtPropertyModelItem*)), this, SIGNAL(childAppended(QExtPropertyModelItem*)));
        connect(child, SIGNAL(childAboutToBeRemoveed(QExtPropertyModelItem*)), this, SIGNAL(childAboutToBeRemoveed(QExtPropertyModelItem*)));
        connect(child, SIGNAL(childRemoveed(QExtPropertyModelItem*)), this, SIGNAL(childRemoveed(QExtPropertyModelItem*)));
        emit this->childAppended(child);
    }
}

void QExtPropertyModelItem::appendChildren(const QList<QExtPropertyModelItem *> &children)
{
    for (auto &&child : children)
    {
        this->appendChild(child);
    }
}

void QExtPropertyModelItem::removeChild(QExtPropertyModelItem *child)
{
    if (mChildrenList.contains(child))
    {
        emit this->childAboutToBeRemoveed(child);
        child->setParent(QEXT_NULLPTR);
        child->disconnect(this);
        mChildrenList.removeOne(child);
        emit this->childRemoveed(child);
    }
}

QExtPropertyModelItem *QExtPropertyModelItem::parent() const
{
    return mParent;
}

void QExtPropertyModelItem::setParent(QExtPropertyModelItem *parent)
{
    if (parent != mParent)
    {
        if (mParent)
        {
            mParent->disconnect(this);
        }
        mParent = parent;
        if (mParent)
        {
            connect(this, &QExtPropertyModelItem::itemDataChanged, mParent, &QExtPropertyModelItem::itemDataChanged);
        }
    }
}

bool QExtPropertyModelItem::isEnabled() const
{
    return mEnable;
}

void QExtPropertyModelItem::setEnable(bool enable)
{
    mEnable = enable;
    emit this->itemDataChanged(this);
    for (auto &&child : mChildrenList)
    {
        child->setEnable(enable);
    }
}

QVariant QExtPropertyModelItem::data(int role) const
{
    Q_UNUSED(role);
    return QVariant();
}

bool QExtPropertyModelItem::setData(const QVariant &value, int role)
{
    Q_UNUSED(value);
    Q_UNUSED(role);
    return false;
}

bool QExtPropertyModelItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (this->editorType())
    {
    case Editor_ComboBox:
    {
        auto widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            widget->setCurrentIndex(widget->findData(index.model()->data(index, Qt::EditRole)));
            return true;
        }
    }
    case Editor_SpinBox:
    {
        auto widget = qobject_cast<QSpinBox *>(editor);
        if (widget)
        {
            int data = index.model()->data(index, Qt::EditRole).toInt();
            widget->setValue(data);
            return true;
        }
    }
    case Editor_DoubleSpinBox:
    {
        auto widget = qobject_cast<QDoubleSpinBox *>(editor);
        if (widget)
        {
            double data = index.model()->data(index, Qt::EditRole).toDouble();
            widget->setValue(data);
            return true;
        }
    }
    case Editor_LineEdit:
    {
        auto widget = qobject_cast<QLineEdit *>(editor);
        if (widget)
        {
            QString data = index.model()->data(index, Qt::EditRole).toString();
            widget->setText(data);
            return true;
        }
    }
    default: return false;
    }
    return false;
}

bool QExtPropertyModelItem::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (this->editorType())
    {
    case Editor_ComboBox:
    {
        auto widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            model->setData(index, widget->currentData(), Qt::EditRole);
            return true;
        }
    }
    case Editor_SpinBox:
    {
        auto widget = qobject_cast<QSpinBox *>(editor);
        if (widget)
        {
            int data = widget->value();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    case Editor_DoubleSpinBox:
    {
        auto widget = qobject_cast<QDoubleSpinBox *>(editor);
        if (widget)
        {
            double data = widget->value();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    case Editor_LineEdit:
    {
        auto widget = qobject_cast<QLineEdit *>(editor);
        if (widget)
        {
            QString data = widget->text();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    default: break;
    }
    return false;
}

QSize QExtPropertyModelItem::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index,
                                      const QSize &baseSize) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    Q_UNUSED(baseSize);
    QSize size = baseSize;
    size.setHeight(30);
    return size;
}

QWidget *QExtPropertyModelItem::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    switch (this->editorType())
    {
    case Editor_ComboBox:
    {
        return new QComboBox(parent);
    }
    case Editor_SpinBox:
    {
        return new QSpinBox(parent);
    }
    case Editor_DoubleSpinBox:
    {
        return new QDoubleSpinBox(parent);
    }
    case Editor_LineEdit:
    {
        return new QLineEdit(parent);
    }
    default:
        return QEXT_NULLPTR;
    }
    return QEXT_NULLPTR;
}

QWidget *QExtPropertyModelItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                   const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return editor;
}

bool QExtPropertyModelItem::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(index);
    return false;
}

bool QExtPropertyModelItem::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(index);
    return false;
}


QList<QExtPropertyModelItem *> QExtPropertyModelItem::allSubItems(QExtPropertyModelItem *item)
{
    QList<QExtPropertyModelItem *> items;
    if (item)
    {
        auto childItems = item->childrenList();
        for (auto &&child : childItems)
        {
            items.append(child);
            items.append(QExtPropertyModelItem::allSubItems(child));
        }
    }
    return items;
}


class QExtPropertyModelPrivate
{
public:
    explicit QExtPropertyModelPrivate(QExtPropertyModel *q);
    virtual ~QExtPropertyModelPrivate();

    QExtPropertyModel * const q_ptr;

    QScopedPointer<QExtPropertyModelItem> mRootItem;

private:
    Q_DECLARE_PUBLIC(QExtPropertyModel)
    QEXT_DISABLE_COPY_MOVE(QExtPropertyModelPrivate)
};

QExtPropertyModelPrivate::QExtPropertyModelPrivate(QExtPropertyModel *q)
    : q_ptr(q)
    , mRootItem(new QExtPropertyModelRootItem)
{

}

QExtPropertyModelPrivate::~QExtPropertyModelPrivate()
{

}


QExtPropertyModel::QExtPropertyModel(QObject *parent)
    : QAbstractItemModel(parent)
    , dd_ptr(new QExtPropertyModelPrivate(this))
{
    Q_D(QExtPropertyModel);
    connect(d->mRootItem.data(), SIGNAL(itemDataChanged(QExtPropertyModelItem*)), this, SLOT(onItemDataChanged(QExtPropertyModelItem*)));
    connect(d->mRootItem.data(), SIGNAL(beginResetModel()), this, SLOT(onBeginResetModel()));
    connect(d->mRootItem.data(), SIGNAL(endResetModel()), this, SLOT(onEndResetModel()));
}

QExtPropertyModel::~QExtPropertyModel()
{
}

QModelIndex QExtPropertyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }

    QExtPropertyModelItem *parentItem = this->itemFromIndex(parent);
    if (!parentItem || row >= parentItem->childrenCount())
    {
        return QModelIndex();
    }
    QExtPropertyModelItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex QExtPropertyModel::parent(const QModelIndex &child) const
{
    Q_D(const QExtPropertyModel);
    if (!child.isValid())
    {
        return QModelIndex();
    }

    QExtPropertyModelItem *childItem = this->itemFromIndex(child);
    QExtPropertyModelItem *parentItem = childItem->parent();
    if (d->mRootItem.data() == parentItem || QEXT_NULLPTR == parentItem)
    {
        return QModelIndex();
    }
    QExtPropertyModelItem *grandParentItem = parentItem->parent();
    int row = grandParentItem->childIndexOf(parentItem);
    return this->createIndex(row, 0, parentItem);
}

int QExtPropertyModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const QExtPropertyModel);
    if (parent.column() > 0)
    {
        return 0;
    }

    QExtPropertyModelItem *parentItem = parent.isValid() ? static_cast<QExtPropertyModelItem*>(parent.internalPointer())
                                                         : d->mRootItem.data();
    return parentItem->childrenCount();
}

int QExtPropertyModel::columnCount(const QModelIndex &/*parent*/) const
{
    return ColumnNum;
}

QVariant QExtPropertyModel::data(const QModelIndex &index, int role) const
{
    // check index
    if (!index.isValid())
    {
        return QVariant();
    }

    QExtPropertyModelItem *item = static_cast<QExtPropertyModelItem *>(index.internalPointer());
    if (item)
    {
        if (ItemRole == role)
        {
            return reinterpret_cast<qulonglong>(item);
        }

        if (Qt::TextColorRole == role && !item->isEnabled())
        {
            return QColor(Qt::gray);
        }

        switch (index.column())
        {
        case Column_Property:
        {
            if (role == Qt::DisplayRole)
            {
                return item->name();
            }
            break;
        }
        case Column_Value:
        {
            return item->data(role);
        }
        default:
            break;
        }
    }

    return QVariant();
}

bool QExtPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // check index
    if (!index.isValid())
    {
        return false;
    }

    QExtPropertyModelItem *item = static_cast<QExtPropertyModelItem *>(index.internalPointer());
    if (item)
    {
        switch (index.column())
        {
        case Column_Value:
        {
            if (item->setData(value, role))
            {
                emit this->dataChanged(index, index, QVector< int >({ role }));
                return true;
            }
        }
        default:
            break;
        }
    }

    return false;
}

Qt::ItemFlags QExtPropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    QExtPropertyModelItem *item = static_cast<QExtPropertyModelItem *>(index.internalPointer());
    if (item && item->isEnabled())
    {
        switch (index.column())
        {
        case Column_Property:
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        case Column_Value:
        {
            return item->flags();
        }
        default:
            break;
        }
    }

    return Qt::NoItemFlags;
}

QVariant QExtPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            if (section >= 0 && section < ColumnNum)
            {
                return QExtPropertyModel::columnEnumString(section);
            }
        }
    }

    return QVariant();
}

QModelIndex QExtPropertyModel::indexFromItem(QExtPropertyModelItem *item) const
{
    Q_D(const QExtPropertyModel);
    if (item && d->mRootItem.data() != item)
    {
        auto parentItem = item->parent();
        if (parentItem)
        {
            auto childList = parentItem->childrenList();
            if (childList.contains(item))
            {
                return this->createIndex(childList.indexOf(item), Column_Value, item);
            }
        }
    }
    return QModelIndex();
}

QExtPropertyModelItem *QExtPropertyModel::itemFromIndex(const QModelIndex &index) const
{
    Q_D(const QExtPropertyModel);
    if (index.isValid())
    {
        QExtPropertyModelItem *item = static_cast<QExtPropertyModelItem *>(index.internalPointer());
        if (item)
        {
            return item;
        }
    }
    return d->mRootItem.data();
}

QExtPropertyModelItem *QExtPropertyModel::rootItem() const
{
    Q_D(const QExtPropertyModel);
    return d->mRootItem.data();
}

void QExtPropertyModel::setRootItem(QExtPropertyModelItem *item)
{
    Q_D(QExtPropertyModel);
    this->beginResetModel();
    if (d->mRootItem.data() != item)
    {
        d->mRootItem.reset(item);
    }
    this->endResetModel();
}

QString QExtPropertyModel::columnEnumString(int type, bool isEng)
{
    switch (type)
    {
    case Column_Property:
        return isEng ? "Property" : tr("Property");
    case Column_Value:
        return isEng ? "Value" : tr("Value");
    default:
        break;
    }
    return "";
}

void QExtPropertyModel::updateModel()
{
    QModelIndex leftIndex = this->index(0, ColumnNum);
    QModelIndex rightIndex = this->index(this->rowCount(), ColumnNum);
    emit this->dataChanged(leftIndex, rightIndex);
}

void QExtPropertyModel::resetModel()
{
    this->beginResetModel();
    this->endResetModel();
}

void QExtPropertyModel::onItemDataChanged(QExtPropertyModelItem *item)
{
    QModelIndex index = this->indexFromItem(item);
    if (index.isValid())
    {
        emit this->dataChanged(index, index);
    }
}

void QExtPropertyModel::onBeginResetModel()
{
    emit this->beginResetModel();
}

void QExtPropertyModel::onEndResetModel()
{
    emit this->endResetModel();
}


QExtPropertyDelegate::QExtPropertyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , mRootItem(QEXT_NULLPTR)
{

}

QExtPropertyDelegate::QExtPropertyDelegate(QExtPropertyModelItem *rootItem, QObject *parent)
    : QStyledItemDelegate(parent)
    , mRootItem(QEXT_NULLPTR)
{
    this->setRootItem(rootItem);
}

QExtPropertyDelegate::~QExtPropertyDelegate()
{

}

void QExtPropertyDelegate::setRootItem(QExtPropertyModelItem *rootItem)
{
    if (mRootItem)
    {
        mRootItem->disconnect(this);
    }
    mRootItem = rootItem;
    if (rootItem)
    {
        connect(rootItem, SIGNAL(requestClosedEditor(QWidget*)), this, SLOT(closeItemEditor(QWidget*)));
    }
}

QExtPropertyModelItem *QExtPropertyDelegate::rootItem() const
{
    return mRootItem;
}

QWidget *QExtPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
        if (item)
        {
            auto editor = item->createEditor(parent, option, index);
            if (editor)
            {
                return item->initEditorProperty(editor, option, index);
            }
        }
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QExtPropertyDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
        if (item)
        {
            if (item->destroyEditor(editor, index))
            {
                return;
            }
        }
    }
    QStyledItemDelegate::destroyEditor(editor, index);
}

void QExtPropertyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
        if (item)
        {
            if (item->paint(painter, option, index))
            {
                return;
            }
        }
    }
    QStyledItemDelegate::paint(painter, option, index);
}

void QExtPropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
        if (item)
        {
            if (item->setEditorData(editor, index))
            {
                return;
            }
        }
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void QExtPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
    QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
    if (item)
    {
        if (item->setModelData(editor, model, index))
        {
            return;
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

QSize QExtPropertyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        QExtPropertyModelItem *item = reinterpret_cast<QExtPropertyModelItem *>(value);
        if (item)
        {
            return item->sizeHint(option, index, QStyledItemDelegate::sizeHint(option, index));
        }
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

void QExtPropertyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void QExtPropertyDelegate::closeItemEditor(QWidget *editor)
{
    emit this->closeEditor(editor);
}

bool QExtPropertyDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
                                     const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::helpEvent(event, view, option, index);
}

bool QExtPropertyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void QExtPropertyDelegate::updateItemMap()
{
    mItemMap.clear();
    if (mRootItem)
    {
        QList<QExtPropertyModelItem *> items = QExtPropertyModelItem::allSubItems(mRootItem);
        for (QList<QExtPropertyModelItem *>::Iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            mItemMap.insert(qulonglong(*iter), *iter);
        }
    }
}
