// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmStandardViewModelControllers.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmLabelDataRowStrategy.h>
#include <qextMvvmPropertiesRowStrategy.h>
#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmStandardViewItems.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

QExtMvvmDefaultViewModelController::QExtMvvmDefaultViewModelController(QExtMvvmSessionModel* session_model,
                                                       QExtMvvmViewModelBase* view_model)
    : QExtMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<QExtMvvmAllChildrenStrategy>());
    setRowStrategy(qextMakeUnique<QExtMvvmLabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

QExtMvvmTopItemsViewModelController::QExtMvvmTopItemsViewModelController(QExtMvvmSessionModel* session_model,
                                                         QExtMvvmViewModelBase* view_model)
    : QExtMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<QExtMvvmTopItemsStrategy>());
    setRowStrategy(qextMakeUnique<QExtMvvmLabelDataRowStrategy>());
}

// ----------------------------------------------------------------------------

QExtMvvmPropertyViewModelController::QExtMvvmPropertyViewModelController(QExtMvvmSessionModel* session_model,
                                                         QExtMvvmViewModelBase* view_model)
    : QExtMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<QExtMvvmPropertyItemsStrategy>());
    setRowStrategy(qextMakeUnique<QExtMvvmLabelDataRowStrategy>());
}

void QExtMvvmPropertyViewModelController::onDataChange(QExtMvvmSessionItem* item, int role)
{
    QExtMvvmViewModelController::onDataChange(item, role);
    // If data change occured with QExtMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QExtMvvmGroupItem*>(item))
        update_branch(group);
}

// ----------------------------------------------------------------------------

// FIXME What to do with group property?

QExtMvvmPropertyTableViewModelController::QExtMvvmPropertyTableViewModelController(
    QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model, const std::vector<std::string>& labels)
    : QExtMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<QExtMvvmTopItemsStrategy>());
    setRowStrategy(qextMakeUnique<QExtMvvmPropertiesRowStrategy>(labels));
}

// ----------------------------------------------------------------------------

QExtMvvmPropertyFlatViewModelController::QExtMvvmPropertyFlatViewModelController(QExtMvvmSessionModel* session_model,
                                                                 QExtMvvmViewModelBase* view_model)
    : QExtMvvmViewModelController(session_model, view_model)
{
    setChildrenStrategy(qextMakeUnique<QExtMvvmPropertyItemsFlatStrategy>());
    setRowStrategy(qextMakeUnique<QExtMvvmLabelDataRowStrategy>());
}

void QExtMvvmPropertyFlatViewModelController::onDataChange(QExtMvvmSessionItem* item, int role)
{
    QExtMvvmViewModelController::onDataChange(item, role);
    // If data change occured with QExtMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    if (auto group = dynamic_cast<QExtMvvmGroupItem*>(item))
        update_branch(group->parent());
}
