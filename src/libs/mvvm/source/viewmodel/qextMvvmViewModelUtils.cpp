#include <QStandardItemModel>
#include <iterator>
#include <qextMvvmUtils.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmUtils.h>
#include <qextMvvmConstants.h>
#include <qextMvvmItem.h>
#include <qextMvvmViewItem.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelUtils.h>
#include <set>



void QEXTMvvmViewModelUtils::iterate_model(const QAbstractItemModel *model, const QModelIndex &parent,
                          const QEXTFunction<void, const QModelIndex &> &fun)
{
    if (!model)
    {
        return;
    }

    for (int row = 0; row < model->rowCount(parent); ++row)
    {
        for (int col = 0; col < model->columnCount(parent); ++col)
        {
            auto index = model->index(row, col, parent);
            if (index.isValid())
            {
                fun(index);
            }
        }
        for (int col = 0; col < model->columnCount(parent); ++col)
        {
            auto index = model->index(row, col, parent);
            iterate_model(model, index, fun);
        }
    }
}

//! Translates QEXTMvvmItem's data role to vector of Qt roles.

QVector<int> QEXTMvvmViewModelUtils::ItemRoleToQtRole(int role)
{
    QVector<int> result;
    // In Qt when we are editing the data in a view two roles are emmited.
    if (role == QEXTMvvmItem::Role_Display || role == QEXTMvvmItem::Role_Data)
        result = {Qt::DisplayRole, Qt::EditRole};
    else if (role == QEXTMvvmItem::Role_Appearance)
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        result = {Qt::ForegroundRole};
#else
        result = {Qt::TextColorRole};
#endif
    else if (role == QEXTMvvmItem::Role_ToolTip)
        result = {Qt::ToolTipRole};

    return result;
}

QVariant QEXTMvvmViewModelUtils::TextColorRole(const QEXTMvvmItem &item)
{
    return item.isEnabled() ? QVariant() : QColor(Qt::gray);
}

QVariant QEXTMvvmViewModelUtils::CheckStateRole(const QEXTMvvmItem &item)
{
    auto value = item.data<QVariant>();
    if (QEXTMvvmUtils::IsBoolVariant(value))
    {
        return value.value<bool>() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

QVariant QEXTMvvmViewModelUtils::DecorationRole(const QEXTMvvmItem &item)
{
    auto value = item.data<QVariant>();
    if (QEXTMvvmUtils::IsColorVariant(value))
    {
        return value;
    }
    else if (QEXTMvvmUtils::IsExtPropertyVariant(value))
    {
        return value.value<QEXTMvvmExternalProperty>().color();
    }
    return QVariant();
}

QVariant QEXTMvvmViewModelUtils::ToolTipRole(const QEXTMvvmItem &item)
{
    return item.hasData(QEXTMvvmItem::Role_ToolTip) ? QVariant(item.toolTip())
           : QVariant();
}

QVector<QEXTMvvmItem *> QEXTMvvmViewModelUtils::ItemsFromIndex(const QModelIndexList &index_list)
{
    if (index_list.empty())
        return {};

    QVector<QEXTMvvmItem *> result;

    if (auto model = dynamic_cast<const QEXTMvvmViewModelBase *>(index_list.front().model()))
        std::transform(index_list.begin(), index_list.end(), std::back_inserter(result),
                       [model](auto index)
    {
        return model->itemFromIndex(index)->item();
    });

    return result;
}

//QVector<QEXTMvvmItem *> QEXTMvvmViewModelUtils::UniqueItemsFromIndex(const QModelIndexList &index_list)
//{
//    return QEXTMvvmUtils::UniqueItems(QEXTMvvmViewModelUtils::ItemsFromIndex(index_list));
//}

QVector<QEXTMvvmItem *> QEXTMvvmViewModelUtils::ParentItemsFromIndex(const QModelIndexList &index_list)
{
    std::set<QEXTMvvmItem *> unique_parents;
    for (auto item : ItemsFromIndex(index_list))
        if (item)
        {
            unique_parents.insert(item->parent());
        }

    QVector<QEXTMvvmItem *> result;
    std::copy(unique_parents.begin(), unique_parents.end(), std::back_inserter(result));
    return result;
}
