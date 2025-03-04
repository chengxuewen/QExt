// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/viewmodelcontroller.h"
#include "viewmodel/interfaces/childrenstrategyinterface.h"
#include "viewmodel/interfaces/rowstrategyinterface.h"
#include "model/model/itemutils.h"
#include "model/model/modelutils.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"
#include "model/model/sessionmodel.h"
#include "model/utils/containerutils.h"
#include "viewmodel/viewmodel/standardviewitems.h"
#include "viewmodel/viewmodel/viewmodelbase.h"
#include "viewmodel/viewmodel/viewmodelutils.h"
#include <map>
#include <stdexcept>

using namespace ModelView;

namespace {

//! Returns true if given QExtMvvmSessionItem role is valid for view
bool isValidItemRole(const QExtMvvmViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ItemDataRole::APPEARANCE || item_role == ItemDataRole::TOOLTIP)
        return true;
    return false;
}

} // namespace

struct QExtMvvmViewModelController::ViewModelControllerImpl {
    QExtMvvmViewModelController* m_self;
    QExtMvvmViewModelBase* m_viewModel{nullptr};
    QExtUniquePointer<QExtMvvmChildrenStrategyInterface> m_childrenStrategy;
    QExtUniquePointer<QExtMvvmRowStrategyInterface> m_rowStrategy;
    std::map<QExtMvvmSessionItem*, QExtMvvmViewItem*> m_itemToVview; //! correspondence of item and its view
    QExtMvvmPath m_rootItemPath;

    ViewModelControllerImpl(QExtMvvmViewModelController* controller, QExtMvvmViewModelBase* view_model)
        : m_self(controller), m_viewModel(view_model)
    {
    }

    void check_initialization()
    {
        const std::string msg("Error in QExtMvvmViewModelController: ");
        if (!m_viewModel)
            throw std::runtime_error(msg + "QExtMvvmViewModel is not defined");

        if (!m_rowStrategy)
            throw std::runtime_error(msg + "RowStrategy is not defined");

        if (!m_childrenStrategy)
            throw std::runtime_error(msg + "Children is not defined");
    }

    void init_view_model()
    {
        check_initialization();
        m_itemToVview.clear();
        m_itemToVview[m_self->rootSessionItem()] = m_viewModel->rootItem();
        iterate(m_self->rootSessionItem(), m_viewModel->rootItem());
    }

    void iterate(const QExtMvvmSessionItem* item, QExtMvvmViewItem* parent)
    {
        QExtMvvmViewItem* origParent(parent);
        for (auto child : m_childrenStrategy->children(item)) {
            auto row = m_rowStrategy->constructRow(child);
            if (!row.empty()) {
                auto next_parent = row.at(0).get();
                m_viewModel->appendRow(parent, std::move(row));
                m_itemToVview[child] = next_parent;
                parent = next_parent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }

    //! Remove row of QExtMvvmViewItem's corresponding to given item.

    void remove_row_of_views(QExtMvvmSessionItem* item)
    {
        auto pos = m_itemToVview.find(item);
        if (pos != m_itemToVview.end()) {
            auto view = pos->second;
            m_viewModel->removeRow(view->parent(), view->row());
            m_itemToVview.erase(pos);
        }
    }

    void remove_children_of_view(QExtMvvmViewItem* view)
    {
        for (auto child : view->children()) {
            auto pos = std::find_if(m_itemToVview.begin(), m_itemToVview.end(),
                                    [child](const std::pair<QExtMvvmSessionItem*, QExtMvvmViewItem*>& it) { return it.second == child; });
            if (pos != m_itemToVview.end())
                m_itemToVview.erase(pos);
        }

        m_viewModel->clearRows(view);
    }

    void insert_view(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
    {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        auto children = m_childrenStrategy->children(parent);
        auto index = Utils::IndexOfItem(children, child);
        if (index == -1)
            return;

        auto pos = m_itemToVview.find(parent);
        if (pos == m_itemToVview.end())
            return;

        auto parent_view = pos->second;

        auto row = m_rowStrategy->constructRow(child);
        if (!row.empty()) {
            auto next_parent = row.at(0).get();
            m_viewModel->insertRow(parent_view, index, std::move(row));
            m_itemToVview[child] = next_parent;
            parent_view = next_parent; // labelItem
            iterate(child, parent_view);
        }
    }

    std::vector<QExtMvvmViewItem*> findViews(const QExtMvvmSessionItem* item) const
    {
        if (item == m_viewModel->rootItem()->item())
            return {m_viewModel->rootItem()};

        std::vector<QExtMvvmViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = m_viewModel->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        Utils::iterate_model(m_viewModel, QModelIndex(), on_index);
        return result;
    }

    void setRootSessionItemIntern(QExtMvvmSessionItem* item)
    {
        m_rootItemPath = Utils::PathFromItem(item);
        m_viewModel->setRootViewItem(qextMakeUnique<QExtMvvmRootViewItem>(item));
    }
};

QExtMvvmViewModelController::QExtMvvmViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model)
    : QExtMvvmModelListener(session_model)
    , p_impl(qextMakeUnique<ViewModelControllerImpl>(this, view_model))
{
    auto on_data_change = [this](QExtMvvmSessionItem* item, int role) { onDataChange(item, role); };
    setOnDataChange(on_data_change);

    auto on_item_inserted = [this](QExtMvvmSessionItem* item, QExtMvvmTagRow tagrow) {
        onItemInserted(item, std::move(tagrow));
    };
    setOnItemInserted(on_item_inserted);

    auto on_item_removed = [this](QExtMvvmSessionItem* item, QExtMvvmTagRow tagrow) {
        onItemRemoved(item, std::move(tagrow));
    };
    setOnItemRemoved(on_item_removed);

    auto on_about_to_remove = [this](QExtMvvmSessionItem* item, QExtMvvmTagRow tagrow) {
        onAboutToRemoveItem(item, std::move(tagrow));
    };
    setOnAboutToRemoveItem(on_about_to_remove);

    auto on_model_destroyed = [this](QExtMvvmSessionModel*) {
        p_impl->m_viewModel->setRootViewItem(qextMakeUnique<QExtMvvmRootViewItem>(nullptr));
    };
    setOnModelDestroyed(on_model_destroyed);

    auto on_model_reset = [this](QExtMvvmSessionModel*) {
        auto root_item = Utils::ItemFromPath(*model(), p_impl->m_rootItemPath);
        p_impl->setRootSessionItemIntern(root_item ? root_item : model()->rootItem());
        p_impl->m_viewModel->endResetModel();
        p_impl->init_view_model();
    };
    setOnModelReset(on_model_reset);

    auto on_model_about_to_be_reset = [this](QExtMvvmSessionModel*) { p_impl->m_viewModel->beginResetModel(); };
    setOnModelAboutToBeReset(on_model_about_to_be_reset);
}

void QExtMvvmViewModelController::setViewModel(QExtMvvmViewModelBase* view_model)
{
    p_impl->m_viewModel = view_model;
}

QExtMvvmViewModelController::~QExtMvvmViewModelController() = default;

void QExtMvvmViewModelController::setChildrenStrategy(
    QExtUniquePointer<QExtMvvmChildrenStrategyInterface> children_strategy)
{
    p_impl->m_childrenStrategy = std::move(children_strategy);
}

void QExtMvvmViewModelController::setRowStrategy(QExtUniquePointer<QExtMvvmRowStrategyInterface> row_strategy)
{
    p_impl->m_rowStrategy = std::move(row_strategy);
}

//! Returns QExtMvvmSessionModel handled by this controller.

QExtMvvmSessionModel* QExtMvvmViewModelController::sessionModel() const
{
    return model();
}

void QExtMvvmViewModelController::setRootSessionItem(QExtMvvmSessionItem* item)
{
    if (!item)
        throw std::runtime_error(
            "Error in QExtMvvmViewModelController: atttemp to set nulptr as root item");

    if (item->model() != model())
        throw std::runtime_error(
            "Error in QExtMvvmViewModelController: atttemp to use item from alien model as new root.");

    p_impl->m_viewModel->beginResetModel();
    p_impl->setRootSessionItemIntern(item);
    p_impl->m_viewModel->endResetModel();
    p_impl->init_view_model();
}

QExtMvvmSessionItem* QExtMvvmViewModelController::rootSessionItem() const
{
    return p_impl->m_viewModel->rootItem()->item();
}

//! Returns all QExtMvvmViewItem's displaying given QExtMvvmSessionItem.

std::vector<QExtMvvmViewItem*> QExtMvvmViewModelController::findViews(const QExtMvvmSessionItem* item) const
{
    return p_impl->findViews(item);
}

QStringList QExtMvvmViewModelController::horizontalHeaderLabels() const
{
    return p_impl->m_rowStrategy->horizontalHeaderLabels();
}

void QExtMvvmViewModelController::onDataChange(QExtMvvmSessionItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = p_impl->m_viewModel->indexFromItem(view);
            p_impl->m_viewModel->dataChanged(index, index, Utils::ItemRoleToQtRole(role));
        }
    }
}

void QExtMvvmViewModelController::onItemInserted(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow)
{
    p_impl->insert_view(parent, tagrow);
}

void QExtMvvmViewModelController::onItemRemoved(QExtMvvmSessionItem*, QExtMvvmTagRow) {}

void QExtMvvmViewModelController::onAboutToRemoveItem(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow)
{
    auto item_to_remove = parent->getItem(tagrow.tag, tagrow.row);
    if (item_to_remove == rootSessionItem()
        || Utils::IsItemAncestor(rootSessionItem(), item_to_remove)) {
        // special case when user removes QExtMvvmSessionItem which is one of ancestors of our root item
        // or root item iteslf
        p_impl->m_viewModel->beginResetModel();
        p_impl->m_viewModel->setRootViewItem(qextMakeUnique<QExtMvvmRootViewItem>(nullptr));
        p_impl->m_itemToVview.clear();
        p_impl->m_rootItemPath = {};
        p_impl->m_viewModel->endResetModel();
    }
    else {
        p_impl->remove_row_of_views(item_to_remove);
    }
}

void QExtMvvmViewModelController::update_branch(const QExtMvvmSessionItem* item)
{
    auto views = findViews(item);
    if (views.empty())
        return;

    for (auto view : views)
        p_impl->remove_children_of_view(view);

    p_impl->iterate(item, views.at(0));
}
