// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGroupItem.h>
#include <viewmodel/qextMvvmLabelDataRowStrategy.h>
#include <viewmodel/qextMvvmPropertiesRowStrategy.h>
#include <viewmodel/qextMvvmStandardChildrenStrategies.h>
#include <viewmodel/qextMvvmStandardViewItems.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

QEXTMvvmDefaultViewModelController::QEXTMvvmDefaultViewModelController(QEXTMvvmSessionModel* session_model,
                                                       QEXTMvvmViewModelBase* view_model)
    : QEXTMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(make_unique<QEXTMvvmAllChildrenStrategy>());
    setRowStrategy(make_unique<QEXTMvvmLabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

QEXTMvvmTopItemsViewModelController::QEXTMvvmTopItemsViewModelController(QEXTMvvmSessionModel* session_model,
                                                         QEXTMvvmViewModelBase* view_model)
    : QEXTMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(make_unique<QEXTMvvmTopItemsStrategy>());
    setRowStrategy(make_unique<QEXTMvvmLabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

QEXTMvvmPropertyViewModelController::QEXTMvvmPropertyViewModelController(QEXTMvvmSessionModel* session_model,
                                                         QEXTMvvmViewModelBase* view_model)
    : QEXTMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(make_unique<QEXTMvvmPropertyItemsStrategy>());
    setRowStrategy(make_unique<QEXTMvvmLabelDataRowStrategy>());
}

void QEXTMvvmPropertyViewModelController::onDataChange(QEXTMvvmSessionItem* item, int role)
{
    QEXTMvvmViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QEXTMvvmGroupItem*>(item))
        update_branch(group);
}

// ----------------------------------------------------------------------------

// FIXME What to do with group property?

QEXTMvvmPropertyTableViewModelController::QEXTMvvmPropertyTableViewModelController(
    QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model, const std::vector<std::string>& labels)
    : QEXTMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(make_unique<QEXTMvvmTopItemsStrategy>());
    setRowStrategy(make_unique<QEXTMvvmPropertiesRowStrategy>(labels));
}

// ----------------------------------------------------------------------------

QEXTMvvmPropertyFlatViewModelController::QEXTMvvmPropertyFlatViewModelController(QEXTMvvmSessionModel* session_model,
                                                                 QEXTMvvmViewModelBase* view_model)
    : QEXTMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(make_unique<QEXTMvvmPropertyItemsFlatStrategy>());
    setRowStrategy(make_unique<QEXTMvvmLabelDataRowStrategy>());
}

void QEXTMvvmPropertyFlatViewModelController::onDataChange(QEXTMvvmSessionItem* item, int role)
{
    QEXTMvvmViewModelController::onDataChange(item, role);
    // If data change occured with GroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QEXTMvvmGroupItem*>(item))
        update_branch(group->parent());
}
