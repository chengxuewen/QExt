#include <qextPropertyModel.h>

#include <QDebug>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QDoubleSpinBox>

QExtPropertyModelItem::QExtPropertyModelItem()
    : m_enable(true)
    , m_parent(QEXT_NULLPTR)
{
}

QExtPropertyModelItem::~QExtPropertyModelItem()
{
    if (!m_childrenList.isEmpty())
    {
        for (auto &&child : m_childrenList)
        {
            this->removeChild(child);
            child->deleteLater();
        }
        m_childrenList.clear();
    }
}

int QExtPropertyModelItem::childrenCount() const
{
    return m_childrenList.size();
}

int QExtPropertyModelItem::childIndexOf(QExtPropertyModelItem *child) const
{
    return m_childrenList.indexOf(child);
}

QExtPropertyModelItem *QExtPropertyModelItem::child(int index) const
{
    Q_ASSERT_X(index >= 0 && index < m_childrenList.size(), "QExtPropertyModelItem::child()", "index out of range");
    return m_childrenList.at(index);
}

QList<QExtPropertyModelItem *> QExtPropertyModelItem::childrenList() const
{
    return m_childrenList;
}

void QExtPropertyModelItem::appendChild(QExtPropertyModelItem *child)
{
    if (!m_childrenList.contains(child))
    {
        child->setParent(this);
        m_childrenList.append(child);
        connect(child, &QExtPropertyModelItem::beginResetModel, this, &QExtPropertyModelItem::beginResetModel);
        connect(child, &QExtPropertyModelItem::endResetModel, this, &QExtPropertyModelItem::endResetModel);
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
    if (m_childrenList.contains(child))
    {
        child->setParent(QEXT_NULLPTR);
        child->disconnect(this);
        m_childrenList.removeOne(child);
    }
}

QExtPropertyModelItem *QExtPropertyModelItem::parent() const
{
    return m_parent;
}

void QExtPropertyModelItem::setParent(QExtPropertyModelItem *parent)
{
    if (parent != m_parent)
    {
        if (m_parent)
        {
            m_parent->disconnect(this);
        }
        m_parent = parent;
        if (m_parent)
        {
            connect(this, &QExtPropertyModelItem::itemDataChanged, m_parent, &QExtPropertyModelItem::itemDataChanged);
        }
    }
}

bool QExtPropertyModelItem::isEnabled() const
{
    return m_enable;
}

void QExtPropertyModelItem::setEnable(bool enable)
{
    m_enable = enable;
    emit this->itemDataChanged(this);
    for (auto &&child : m_childrenList)
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
    case Editor_ComboBoxWithListView:
    {
        auto widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            int data = index.model()->data(index, Qt::EditRole).toInt();
            widget->setCurrentIndex(data);
            widget->showPopup();
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
    case Editor_ComboBoxWithListView:
    {
        auto widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            int data = widget->currentData().toInt();
            model->setData(index, data, Qt::EditRole);
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
    case Editor_ComboBoxWithListView:
    {
        auto editor = new QComboBox(parent);
        editor->setView(new QListView(editor));
        return editor;
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
    Q_DISABLE_COPY(QExtPropertyModelPrivate)
    Q_DECLARE_PUBLIC(QExtPropertyModel)
public:
    explicit QExtPropertyModelPrivate(QExtPropertyModel *q);
    virtual ~QExtPropertyModelPrivate();

    QExtPropertyModel * const q_ptr;
    QScopedPointer<QExtPropertyModelItem> m_rootItem;
};

QExtPropertyModelPrivate::QExtPropertyModelPrivate(QExtPropertyModel *q)
    : q_ptr(q)
    , m_rootItem(new QExtPropertyModelRootItem)
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
    connect(d->m_rootItem.data(), &QExtPropertyModelItem::itemDataChanged, this, [=](QExtPropertyModelItem *item) {
        QModelIndex index = this->indexFromItem(item);
        if (index.isValid())
        {
            emit this->dataChanged(index, index);
        }
    });
    connect(d->m_rootItem.data(), &QExtPropertyModelItem::beginResetModel, this, &QExtPropertyModel::beginResetModel);
    connect(d->m_rootItem.data(), &QExtPropertyModelItem::endResetModel, this, &QExtPropertyModel::endResetModel);
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
    if (d->m_rootItem.data() == parentItem || QEXT_NULLPTR == parentItem)
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
                                                         : d->m_rootItem.data();
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
            return qulonglong(item);
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
    if (item && d->m_rootItem.data() != item)
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
    return d->m_rootItem.data();
}

QExtPropertyModelItem *QExtPropertyModel::rootItem() const
{
    Q_D(const QExtPropertyModel);
    return d->m_rootItem.data();
}

void QExtPropertyModel::setRootItem(QExtPropertyModelItem *item)
{
    Q_D(QExtPropertyModel);
    this->beginResetModel();
    if (d->m_rootItem.data() != item)
    {
        d->m_rootItem.reset(item);
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


QExtPropertyDelegate::QExtPropertyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_rootItem(QEXT_NULLPTR)
{

}

QExtPropertyDelegate::QExtPropertyDelegate(QExtPropertyModelItem *rootItem, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_rootItem(QEXT_NULLPTR)
{
    this->setRootItem(rootItem);
}

QExtPropertyDelegate::~QExtPropertyDelegate()
{

}

void QExtPropertyDelegate::setRootItem(QExtPropertyModelItem *rootItem)
{
    if (m_rootItem)
    {
        m_rootItem->disconnect(this);
    }
    m_rootItem = rootItem;
    this->updateItemMap();
    if (rootItem)
    {
        connect(rootItem, &QExtPropertyModelItem::endResetModel, this, &QExtPropertyDelegate::updateItemMap);
    }
}

QExtPropertyModelItem *QExtPropertyDelegate::rootItem() const
{
    return m_rootItem;
}

QWidget *QExtPropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    QExtPropertyModelItem *item = QEXT_NULLPTR;
    const QAbstractItemModel *model = index.model();
    if (model)
    {
        qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
        item = m_itemMap.value(value);
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
        QExtPropertyModelItem *item = m_itemMap.value(value);
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
        QExtPropertyModelItem *item = m_itemMap.value(value);
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
        QExtPropertyModelItem *item = m_itemMap.value(value);
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

void QExtPropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    qulonglong value = model->data(index, QExtPropertyModel::ItemRole).toULongLong();
    QExtPropertyModelItem *item = m_itemMap.value(value);
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
        QExtPropertyModelItem *item = m_itemMap.value(value);
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
    m_itemMap.clear();
    if (m_rootItem)
    {
        QList<QExtPropertyModelItem *> items = QExtPropertyModelItem::allSubItems(m_rootItem);
        for (QList<QExtPropertyModelItem *>::Iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            m_itemMap.insert(qulonglong(*iter), *iter);
        }
    }
}



