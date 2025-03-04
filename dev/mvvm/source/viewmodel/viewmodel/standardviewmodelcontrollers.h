// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H
#define MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H

#include "viewmodel/viewmodel/viewmodel.h"
#include "viewmodel/viewmodel/viewmodelcontroller.h"
#include <string>
#include <vector>

//! @file viewmodelcontrollers.h
//! Collection of standard controllers for AbstractViewModel.

namespace ModelView {

//! Controller for AbstractViewModel to show all items of QExtMvvmSessionModel.
//! The layout corresponds to original QExtMvvmSessionModel, generates standard label/value tree.

class QEXT_MVVM_API QExtMvvmDefaultViewModelController : public QExtMvvmViewModelController {
public:
    QExtMvvmDefaultViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model);
};

//! Controller for AbstractViewModel to show top level items.
//! Shows only top level items, property items, group items are hidden.

class QEXT_MVVM_API QExtMvvmTopItemsViewModelController : public QExtMvvmViewModelController {
public:
    explicit QExtMvvmTopItemsViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model);
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty.

class QEXT_MVVM_API QExtMvvmPropertyViewModelController : public QExtMvvmViewModelController {
public:
    QExtMvvmPropertyViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model);

protected:
    void onDataChange(QExtMvvmSessionItem* item, int role) override;
};

//! Controller for AbstractViewModel to show item properties in table layout.
//! Shows all property items and place them in table columns.

class QEXT_MVVM_API QExtMvvmPropertyTableViewModelController : public QExtMvvmViewModelController {
public:
    QExtMvvmPropertyTableViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model,
                                     const std::vector<std::string>& labels = {});
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty,
//! moves subproperties of group item under parent of group item.

class QEXT_MVVM_API QExtMvvmPropertyFlatViewModelController : public QExtMvvmViewModelController {
public:
    QExtMvvmPropertyFlatViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model);

protected:
    void onDataChange(QExtMvvmSessionItem* item, int role) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWMODELCONTROLLERS_H
