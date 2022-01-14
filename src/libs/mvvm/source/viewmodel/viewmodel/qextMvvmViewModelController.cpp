// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <map>
#include <qextMvvmChildrenStrategyInterface.h>
#include <qextMvvmRowStrategyInterface.h>
#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmContainerUtils.h>
#include <viewmodel/qextMvvmStandardViewItems.h>
#include <viewmodel/qextMvvmViewModelBase.h>
#include <viewmodel/qextMvvmViewModelController.h>
#include <viewmodel/qextMvvmViewModelUtils.h>
#include <stdexcept>

using namespace ModelView;

namespace
{

//! Returns true if given QEXTMvvmSessionItem role is valid for view
bool isValidItemRole(const QEXTMvvmViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ItemDataRole::APPEARANCE || item_role == ItemDataRole::TOOLTIP)
        return true;
    return false;
}

} // namespace

struct QEXTMvvmViewModelController::ViewModelControllerImpl {
    QEXTMvvmViewModelController* controller;
    QEXTMvvmViewModelBase* view_model{nullptr};
    std::unique_ptr<QEXTMvvmChildrenStrategyInterface> children_strategy;
    std::unique_ptr<QEXTMvvmRowStrategyInterface> row_strategy;
    std::map<QEXTMvvmSessionItem*, QEXTMvvmViewItem*> item_to_view; //! correspondence of item and its view
    QEXTMvvmPath root_item_path;

    ViewModelControllerImpl(QEXTMvvmViewModelController* controller, QEXTMvvmViewModelBase* view_model)
        : controller(controller), view_model(view_model)
    {
    }

    void check_initialization()
    {
        const std::string msg("Error in ViewModelController: ");
        if (!view_model)
            throw std::runtime_error(msg + "ViewModel is not defined");

        if (!row_strategy)
            throw std::runtime_error(msg + "RowStrategy is not defined");

        if (!children_strategy)
            throw std::runtime_error(msg + "Children is not defined");
    }

    void init_view_model()
    {
        check_initialization();
        item_to_view.clear();
        item_to_view[controller->rootSessionItem()] = view_model->rootItem();
        iterate(controller->rootSessionItem(), view_model->rootItem());
    }

    void iterate(const QEXTMvvmSessionItem* item, QEXTMvvmViewItem* parent)
    {
        QEXTMvvmViewItem* origParent(parent);
        for (auto child : children_strategy->children(item)) {
            auto row = row_strategy->constructRow(child);
            if (!row.empty()) {
                auto next_parent = row.at(0).get();
                view_model->appendRow(parent, std::move(row));
                item_to_view[child] = next_parent;
                parent = next_parent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }

    //! Remove row of ViewItem's corresponding to given item.

    void remove_row_of_views(QEXTMvvmSessionItem* item)
    {
        auto pos = item_to_view.find(item);
        if (pos != item_to_view.end()) {
            auto view = pos->second;
            view_model->removeRow(view->parent(), view->row());
            item_to_view.erase(pos);
        }
    }

    void remove_children_of_view(QEXTMvvmViewItem* view)
    {
        for (auto child : view->children()) {
            auto pos = std::find_if(item_to_view.begin(), item_to_view.end(),
                                    [child](const std::map<QEXTMvvmSessionItem*, QEXTMvvmViewItem*>::value_type& it) { return it.second == child; });
            if (pos != item_to_view.end())
                item_to_view.erase(pos);
        }

        view_model->clearRows(view);
    }

    void insert_view(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow)
    {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        auto children = children_strategy->children(parent);
        auto index = QEXTMvvmUtils::IndexOfItem(children, child);
        if (index == -1)
            return;

        auto pos = item_to_view.find(parent);
        if (pos == item_to_view.end())
            return;

        auto parent_view = pos->second;

        auto row = row_strategy->constructRow(child);
        if (!row.empty()) {
            auto next_parent = row.at(0).get();
            view_model->insertRow(parent_view, index, std::move(row));
            item_to_view[child] = next_parent;
            parent_view = next_parent; // labelItem
            iterate(child, parent_view);
        }
    }

    std::vector<QEXTMvvmViewItem*> findViews(const QEXTMvvmSessionItem* item) const
    {
        if (item == view_model->rootItem()->item())
            return {view_model->rootItem()};

        std::vector<QEXTMvvmViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = view_model->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        QEXTMvvmUtils::iterate_model(view_model, QModelIndex(), on_index);
        return result;
    }

    void setRootSessionItemIntern(QEXTMvvmSessionItem* item)
    {
        root_item_path = controller->model()->pathFromItem(item);
        view_model->setRootViewItem(make_unique<QEXTMvvmRootViewItem>(item));
        init_view_model();
    }
};

QEXTMvvmViewModelController::QEXTMvvmViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model)
    : QEXTMvvmModelListener(session_model)
    , p_impl(make_unique<ViewModelControllerImpl>(this, view_model))
{
    auto on_data_change = [this](QEXTMvvmSessionItem* item, int role) { onDataChange(item, role); };
    setOnDataChange(on_data_change);

    auto on_item_inserted = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        onItemInserted(item, std::move(tagrow));
    };
    setOnItemInserted(on_item_inserted);

    auto on_item_removed = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        onItemRemoved(item, std::move(tagrow));
    };
    setOnItemRemoved(on_item_removed);

    auto on_about_to_remove = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        onAboutToRemoveItem(item, std::move(tagrow));
    };
    setOnAboutToRemoveItem(on_about_to_remove);

    auto on_model_destroyed = [this](QEXTMvvmSessionModel*) {
        p_impl->view_model->setRootViewItem(make_unique<QEXTMvvmRootViewItem>(nullptr));
    };
    setOnModelDestroyed(on_model_destroyed);

    auto on_model_reset = [this](QEXTMvvmSessionModel*) {
        auto root_item = model()->itemFromPath(p_impl->root_item_path);
        p_impl->setRootSessionItemIntern(root_item ? root_item : model()->rootItem());
        p_impl->view_model->endResetModel();
    };
    setOnModelReset(on_model_reset);

    auto on_model_about_to_be_reset = [this](QEXTMvvmSessionModel*) { p_impl->view_model->beginResetModel(); };
    setOnModelAboutToBeReset(on_model_about_to_be_reset);
}

void QEXTMvvmViewModelController::setViewModel(QEXTMvvmViewModelBase* view_model)
{
    p_impl->view_model = view_model;
}

QEXTMvvmViewModelController::~QEXTMvvmViewModelController() = default;

void QEXTMvvmViewModelController::setChildrenStrategy(
    std::unique_ptr<QEXTMvvmChildrenStrategyInterface> children_strategy)
{
    p_impl->children_strategy = std::move(children_strategy);
}

void QEXTMvvmViewModelController::setRowStrategy(std::unique_ptr<QEXTMvvmRowStrategyInterface> row_strategy)
{
    p_impl->row_strategy = std::move(row_strategy);
}

//! Returns SessionModel handled by this controller.

QEXTMvvmSessionModel* QEXTMvvmViewModelController::sessionModel() const
{
    return model();
}

void QEXTMvvmViewModelController::setRootSessionItem(QEXTMvvmSessionItem* item)
{
    if (!item)
        throw std::runtime_error(
            "Error in ViewModelController: atttemp to set nulptr as root item");

    if (item->model() != model())
        throw std::runtime_error(
            "Error in ViewModelController: atttemp to use item from alien model as new root.");

    p_impl->view_model->beginResetModel();
    p_impl->setRootSessionItemIntern(item);
    p_impl->view_model->endResetModel();
}

QEXTMvvmSessionItem* QEXTMvvmViewModelController::rootSessionItem() const
{
    return p_impl->view_model->rootItem()->item();
}

//! Returns all ViewItem's displaying given QEXTMvvmSessionItem.

std::vector<QEXTMvvmViewItem*> QEXTMvvmViewModelController::findViews(const QEXTMvvmSessionItem* item) const
{
    return p_impl->findViews(item);
}

QStringList QEXTMvvmViewModelController::horizontalHeaderLabels() const
{
    return p_impl->row_strategy->horizontalHeaderLabels();
}

void QEXTMvvmViewModelController::onDataChange(QEXTMvvmSessionItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->view_model->indexFromItem(view);
            p_impl->view_model->dataChanged(index, index, QEXTMvvmUtils::ItemRoleToQtRole(role));
        }
    }
}

void QEXTMvvmViewModelController::onItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
{
    p_impl->insert_view(parent, tagrow);
}

void QEXTMvvmViewModelController::onItemRemoved(QEXTMvvmSessionItem*, QEXTMvvmTagRow) {}

void QEXTMvvmViewModelController::onAboutToRemoveItem(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
{
    auto item_to_remove = parent->getItem(tagrow.tag, tagrow.row);
    if (item_to_remove == rootSessionItem()
        || QEXTMvvmUtils::IsItemAncestor(rootSessionItem(), item_to_remove)) {
        // special case when user removes QEXTMvvmSessionItem which is one of ancestors of our root item
        // or root item iteslf
        p_impl->view_model->beginResetModel();
        p_impl->view_model->setRootViewItem(make_unique<QEXTMvvmRootViewItem>(nullptr));
        p_impl->item_to_view.clear();
        p_impl->root_item_path = {};
        p_impl->view_model->endResetModel();
    } else {
        p_impl->remove_row_of_views(item_to_remove);
    }
}

void QEXTMvvmViewModelController::update_branch(const QEXTMvvmSessionItem* item)
{
    auto views = findViews(item);
    if (views.empty())
        return;

    for (auto view : views)
        p_impl->remove_children_of_view(view);

    p_impl->iterate(item, views.at(0));
}
