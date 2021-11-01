// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QStandardItemModel>
#include <iterator>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmItemUtils.h>
#include <qextMvvmConstants.h>
#include <qextMvvmSessionItem.h>
#include <viewmodel/viewitem.h>
#include <viewmodel/viewmodel.h>
#include <viewmodel/viewmodelutils.h>
#include <set>

using namespace ModelView;

void Utils::iterate_model(const QAbstractItemModel* model, const QModelIndex& parent,
                          const std::function<void(const QModelIndex& child)>& fun)
{
    if (!model)
        return;

    for (int row = 0; row < model->rowCount(parent); ++row) {
        for (int col = 0; col < model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            if (index.isValid())
                fun(index);
        }
        for (int col = 0; col < model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            iterate_model(model, index, fun);
        }
    }
}

//! Translates QEXTMvvmSessionItem's data role to vector of Qt roles.

QVector<int> Utils::ItemRoleToQtRole(int role)
{
    QVector<int> result;
    // In Qt when we are editing the data in a view two roles are emmited.
    if (role == ItemDataRole::DISPLAY || role == ItemDataRole::DATA)
        result = {Qt::DisplayRole, Qt::EditRole};
    else if (role == ItemDataRole::APPEARANCE)
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        result = {Qt::ForegroundRole};
#else
        result = {Qt::TextColorRole};
#endif
    else if (role == ItemDataRole::TOOLTIP)
        result = {Qt::ToolTipRole};

    return result;
}

QVariant Utils::TextColorRole(const QEXTMvvmSessionItem& item)
{
    return item.isEnabled() ? QVariant() : QColor(Qt::gray);
}

QVariant Utils::CheckStateRole(const QEXTMvvmSessionItem& item)
{
    auto value = item.data<QVariant>();
    if (Utils::IsBoolVariant(value))
        return value.value<bool>() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

QVariant Utils::DecorationRole(const QEXTMvvmSessionItem& item)
{
    auto value = item.data<QVariant>();
    if (Utils::IsColorVariant(value))
        return value;
    else if (Utils::IsExtPropertyVariant(value))
        return value.value<QEXTMvvmExternalProperty>().color();
    return QVariant();
}

QVariant Utils::ToolTipRole(const QEXTMvvmSessionItem& item)
{
    return item.hasData(ItemDataRole::TOOLTIP) ? QEXTMvvmVariant(QString::fromStdString(item.toolTip()))
                                               : QVariant();
}

std::vector<QEXTMvvmSessionItem*> Utils::ItemsFromIndex(const QModelIndexList& index_list)
{
    if (index_list.empty())
        return {};

    std::vector<QEXTMvvmSessionItem*> result;

    if (auto model = dynamic_cast<const ViewModelBase*>(index_list.front().model()))
        std::transform(index_list.begin(), index_list.end(), std::back_inserter(result),
                       [model](auto index) { return model->itemFromIndex(index)->item(); });

    return result;
}

std::vector<QEXTMvvmSessionItem*> Utils::UniqueItemsFromIndex(const QModelIndexList& index_list)
{
    return Utils::UniqueItems(Utils::ItemsFromIndex(index_list));
}

std::vector<QEXTMvvmSessionItem*> Utils::ParentItemsFromIndex(const QModelIndexList& index_list)
{
    std::set<QEXTMvvmSessionItem*> unique_parents;
    for (auto item : ItemsFromIndex(index_list))
        if (item)
            unique_parents.insert(item->parent());

    std::vector<QEXTMvvmSessionItem*> result;
    std::copy(unique_parents.begin(), unique_parents.end(), std::back_inserter(result));
    return result;
}
