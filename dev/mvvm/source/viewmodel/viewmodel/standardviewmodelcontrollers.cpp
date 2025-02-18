// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/standardviewmodelcontrollers.h"
#include "model/model/groupitem.h"
#include "viewmodel/viewmodel/labeldatarowstrategy.h"
#include "viewmodel/viewmodel/propertiesrowstrategy.h"
#include "viewmodel/viewmodel/standardchildrenstrategies.h"
#include "viewmodel/viewmodel/standardviewitems.h"

using namespace ModelView;

// ----------------------------------------------------------------------------

DefaultViewModelController::DefaultViewModelController(SessionModel* session_model,
                                                       ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<AllChildrenStrategy>());
    setRowStrategy(qextMakeUnique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

TopItemsViewModelController::TopItemsViewModelController(SessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<TopItemsStrategy>());
    setRowStrategy(qextMakeUnique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

PropertyViewModelController::PropertyViewModelController(SessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<PropertyItemsStrategy>());
    setRowStrategy(qextMakeUnique<LabelDataRowStrategy>());
}

void PropertyViewModelController::onDataChange(SessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        update_branch(group);
}

// ----------------------------------------------------------------------------

// FIXME What to do with group property?

PropertyTableViewModelController::PropertyTableViewModelController(
    SessionModel* session_model, ViewModelBase* view_model, const std::vector<std::string>& labels)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<TopItemsStrategy>());
    setRowStrategy(qextMakeUnique<PropertiesRowStrategy>(labels));
}

// ----------------------------------------------------------------------------

PropertyFlatViewModelController::PropertyFlatViewModelController(SessionModel* session_model,
                                                                 ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<PropertyItemsFlatStrategy>());
    setRowStrategy(qextMakeUnique<LabelDataRowStrategy>());
}

void PropertyFlatViewModelController::onDataChange(SessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<GroupItem*>(item))
        update_branch(group->parent());
}
