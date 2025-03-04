// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/viewmodelutils.h"
#include "model/model/customvariants.h"
#include "model/model/externalproperty.h"
#include "model/model/itemutils.h"
#include "model/model/mvvm_types.h"
#include "model/model/sessionitem.h"
#include "viewmodel/viewmodel/viewitem.h"
#include "viewmodel/viewmodel/viewmodel.h"
#include <QStandardItemModel>
#include <iterator>
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

//! Translates QExtMvvmSessionItem's data role to vector of Qt roles.

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

QVariant Utils::TextColorRole(const QExtMvvmSessionItem& item)
{
    const bool item_hidden = !item.isVisible();
    const bool item_disabled = !item.isEnabled();
    return item_disabled || item_hidden ? QColor(Qt::gray) : QVariant();
}

QVariant Utils::CheckStateRole(const QExtMvvmSessionItem& item)
{
    auto value = item.data<QVariant>();
    if (Utils::IsBoolVariant(value))
        return value.value<bool>() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

QVariant Utils::DecorationRole(const QExtMvvmSessionItem& item)
{
    auto value = item.data<QVariant>();
    if (Utils::IsColorVariant(value))
        return value;
    else if (Utils::IsExtPropertyVariant(value))
        return value.value<QExtMvvmExternalProperty>().color();
    return QVariant();
}

QVariant Utils::ToolTipRole(const QExtMvvmSessionItem& item)
{
    return item.hasData(ItemDataRole::TOOLTIP) ? QVariant(QString::fromStdString(item.toolTip()))
                                               : QVariant();
}

std::vector<QExtMvvmSessionItem*> Utils::ItemsFromIndex(const QModelIndexList& index_list)
{
    if (index_list.empty())
        return {};

    std::vector<QExtMvvmSessionItem*> result;

    if (auto model = dynamic_cast<const QExtMvvmViewModelBase*>(index_list.front().model()))
        std::transform(index_list.begin(), index_list.end(), std::back_inserter(result),
                       [model](QModelIndexList::value_type index) { return model->itemFromIndex(index)->item(); });

    return result;
}

std::vector<QExtMvvmSessionItem*> Utils::UniqueItemsFromIndex(const QModelIndexList& index_list)
{
    return Utils::UniqueItems(Utils::ItemsFromIndex(index_list));
}

std::vector<QExtMvvmSessionItem*> Utils::ParentItemsFromIndex(const QModelIndexList& index_list)
{
    std::set<QExtMvvmSessionItem*> unique_parents;
    for (auto item : ItemsFromIndex(index_list))
        if (item)
            unique_parents.insert(item->parent());

    std::vector<QExtMvvmSessionItem*> result;
    std::copy(unique_parents.begin(), unique_parents.end(), std::back_inserter(result));
    return result;
}
