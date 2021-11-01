// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGroupItem.h>
#include <viewmodel/labeldatarowstrategy.h>
#include <viewmodel/propertiesrowstrategy.h>
#include <viewmodel/standardchildrenstrategies.h>
#include <viewmodel/standardviewitems.h>
#include <viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

DefaultViewModelController::DefaultViewModelController(QEXTMvvmSessionModel* session_model,
                                                       ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

TopItemsViewModelController::TopItemsViewModelController(QEXTMvvmSessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

PropertyViewModelController::PropertyViewModelController(QEXTMvvmSessionModel* session_model,
                                                         ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<PropertyItemsStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

void PropertyViewModelController::onDataChange(QEXTMvvmSessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with QEXTMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QEXTMvvmGroupItem*>(item))
        update_branch(group);
}

// ----------------------------------------------------------------------------

// FIXME What to do with group property?

PropertyTableViewModelController::PropertyTableViewModelController(
    QEXTMvvmSessionModel* session_model, ViewModelBase* view_model, const std::vector<std::string>& labels)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<TopItemsStrategy>());
    setRowStrategy(std::make_unique<PropertiesRowStrategy>(labels));
}

// ----------------------------------------------------------------------------

PropertyFlatViewModelController::PropertyFlatViewModelController(QEXTMvvmSessionModel* session_model,
                                                                 ViewModelBase* view_model)
    : ViewModelController(session_model, view_model)
{
    setChildrenStrategy(std::make_unique<PropertyItemsFlatStrategy>());
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
}

void PropertyFlatViewModelController::onDataChange(QEXTMvvmSessionItem* item, int role)
{
    ViewModelController::onDataChange(item, role);
    // If data change occured with QEXTMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QEXTMvvmGroupItem*>(item))
        update_branch(group->parent());
}
