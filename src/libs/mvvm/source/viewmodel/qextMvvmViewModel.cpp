#include <qextMvvmViewModel.h>
#include <qextMvvmViewModel_p.h>
#include <qextMvvmUtils.h>

#include <cfLog.h>

CF_USE_NAMESPACE

void qextMvvmIterateModelViewItems(const QEXTMvvmViewModel *model, const QModelIndex &parent,
                                   const CFMvvmItem *item, std::vector<CFMvvmViewItem *> &viewItems)
{
    for (int row = 0; row < model->rowCount(parent); ++row)
    {
        for (int column = 0; column < model->columnCount(parent); ++column)
        {
            QModelIndex index = model->index(row, column, parent);
            qextMvvmIterateModelViewItems(model, index, item, viewItems);
            if (index.isValid())
            {
                CFMvvmViewItem *viewItem = model->viewItemFromIndex(index);
                if (viewItem->item() == item)
                {
                    viewItems.push_back(viewItem);
                }
            }
        }
    }
}

QEXTMvvmViewModelPrivate::QEXTMvvmViewModelPrivate(QEXTMvvmViewModel *qq)
    : CFMvvmViewModelBasePrivate(qq)
{

}

QEXTMvvmViewModelPrivate::~QEXTMvvmViewModelPrivate()
{

}

QEXTMvvmViewModel::QEXTMvvmViewModel(CFMvvmViewModelController *controller, QObject *parent)
    : QAbstractItemModel(parent), CFMvvmViewModelBase(*(new QEXTMvvmViewModelPrivate(this)))
{
    CF_DECL_D(QEXTMvvmViewModel);
    d->m_modelController.reset(controller);
    d->m_modelController->setViewModel(this);
    d->m_modelController->setRootItem(this->model()->rootItem());
}

QEXTMvvmViewModel::~QEXTMvvmViewModel()
{

}

QModelIndex QEXTMvvmViewModel::index(int row, int column, const QModelIndex &parent) const
{
    CFMvvmViewItem *parentViewItem = this->viewItemFromIndex(parent);
    if (!parentViewItem)
    {
        parentViewItem = this->rootViewItem();
    }
    const bool isValidRow = row >= 0 && row < this->rowCount(parent);
    const bool isValidColumn = column >= 0 && column < this->columnCount(parent);
    if (isValidRow && isValidColumn)
    {
        return this->createIndex(row, column, parentViewItem->child(row, column));
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex QEXTMvvmViewModel::parent(const QModelIndex &child) const
{
    CFMvvmViewItem *childViewItem = this->viewItemFromIndex(child);
    if (childViewItem)
    {
        CFMvvmViewItem *parentViewItem = childViewItem->parent();
        if (parentViewItem != this->rootViewItem())
        {
            return this->createIndex(parentViewItem->row(), parentViewItem->column(), parentViewItem);
        }
    }
    return QModelIndex();
}

int QEXTMvvmViewModel::rowCount(const QModelIndex &parent) const
{
    CFMvvmViewItem *parentViewItem = this->viewItemFromIndex(parent);
    int count = parentViewItem ? parentViewItem->rowCount() : this->rootViewItem()->rowCount();
    return count;
}

int QEXTMvvmViewModel::columnCount(const QModelIndex &parent) const
{
    CFMvvmViewItem *parentViewItem = this->viewItemFromIndex(parent);
    int count = parentViewItem ? parentViewItem->columnCount() : this->rootViewItem()->columnCount();
    return count;
}

QVariant QEXTMvvmViewModel::data(const QModelIndex &index, int role) const
{
    if (this->rootViewItem())
    {
        CFMvvmViewItem *viewItem = this->viewItemFromIndex(index);
        if (viewItem)
        {
            return QEXTMvvmUtils::anyToQVariant(viewItem->data(role));
        }
    }
    return QVariant();
}

bool QEXTMvvmViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid())
    {
        CFMvvmViewItem *viewItem = this->viewItemFromIndex(index);
        if (viewItem)
        {
            bool result = viewItem->setData(QEXTMvvmUtils::qVariantToAny(value), role);
            if (result)
            {
                emit this->dataChanged(index, index);
            }
            return result;
        }
    }
    return false;
}

Qt::ItemFlags QEXTMvvmViewModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    CFMvvmViewItem *viewItem = this->viewItemFromIndex(index);
    if (viewItem)
    {
        result |= QEXTMvvmUtils::viewItemFlagsToQtItemFlags(viewItem->itemFlags());
    }
    return result;
}

QVariant QEXTMvvmViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        CF_DECL_DC(QEXTMvvmViewModel);
        std::list<std::string> labels = d->m_modelController->horizontalHeaderLabels();
        if (section < (int)labels.size())
        {
            std::list<std::string>::const_iterator iter = labels.begin();
            std::advance(iter, section);
            return QString::fromStdString(*iter);
        }
    }
    return QVariant();
}

CFMvvmModel *QEXTMvvmViewModel::model() const
{
    CF_DECL_DC(QEXTMvvmViewModel);
    return d->m_modelController->model();
}

CFMvvmItem *QEXTMvvmViewModel::rootItem() const
{
    CF_DECL_DC(QEXTMvvmViewModel);
    return d->m_modelController->rootItem();
}

void QEXTMvvmViewModel::setRootItem(CFMvvmItem *item)
{
    CF_DECL_DC(QEXTMvvmViewModel);
    if (!item)
    {
        cfLogCritical() << "QEXTMvvmViewModel::setRootItem(): atttemp to set nulptr as root item";
        return;
    }
    d->m_modelController->setRootItem(item);
}

QModelIndexList QEXTMvvmViewModel::indexsOfItem(const CFMvvmItem *item) const
{
    CF_DECL_DC(QEXTMvvmViewModel);
    QModelIndexList result;
    std::vector<CFMvvmViewItem *> viewItems = d->m_modelController->findViewItems(item);
    std::vector<CFMvvmViewItem *>::const_iterator iter;
    for (iter = viewItems.begin(); iter != viewItems.end(); ++iter)
    {
        result.push_back(this->indexFromViewItem(*iter));
    }
    return result;
}

CFMvvmItem *QEXTMvvmViewModel::itemFromIndex(const QModelIndex &index) const
{
    CF_DECL_DC(QEXTMvvmViewModel);
    return index.isValid() ? this->viewItemFromIndex(index)->item() : d->m_modelController->rootItem();
}

QModelIndex QEXTMvvmViewModel::indexFromViewItem(const CFMvvmViewItem *item) const
{
    if (item && item->parent())
    {
       return this->createIndex(item->row(), item->column(), const_cast<CFMvvmViewItem *>(item));
    }
    return QModelIndex();
}

CFMvvmViewItem *QEXTMvvmViewModel::viewItemFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<CFMvvmViewItem *>(index.internalPointer()) : QEXT_DECL_NULLPTR;
}

std::vector<CFMvvmViewItem *> QEXTMvvmViewModel::findViewItems(const CFMvvmItem *item) const
{
    CF_DECL_DC(QEXTMvvmViewModel);
    std::vector<CFMvvmViewItem *> result;
    if (item == d->m_rootViewItem->item())
    {
        result.push_back(d->m_rootViewItem.data());
    }
    else
    {
        qextMvvmIterateModelViewItems(this, QModelIndex(), item, result);
    }
    return result;
}

void QEXTMvvmViewModel::itemDataChanged(const CFMvvmViewItem *item)
{
    QModelIndex index = this->indexFromViewItem(item);
    emit this->dataChanged(index, index);
}

bool QEXTMvvmViewModel::isItemValid(const CFMvvmViewItem *item)
{
    QModelIndex index = this->indexFromViewItem(item);
    return index.isValid();
}

void QEXTMvvmViewModel::beginResetViewModel()
{
    this->beginResetModel();
}

void QEXTMvvmViewModel::beginRemoveViewRows(const CFMvvmViewItem *parent, int first, int last)
{
    QModelIndex index = this->indexFromViewItem(parent);
    this->beginRemoveRows(index, first, last);
}

void QEXTMvvmViewModel::beginInsertViewRows(const CFMvvmViewItem *parent, int first, int last)
{
    QModelIndex index = this->indexFromViewItem(parent);
    this->beginInsertRows(index, first, last);
}

void QEXTMvvmViewModel::endResetViewModel()
{
    this->endResetModel();
}

void QEXTMvvmViewModel::endRemoveViewRows()
{
    this->endRemoveRows();
}

void QEXTMvvmViewModel::endInsertViewRows()
{
    this->endInsertRows();
}
