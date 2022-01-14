#ifndef _QEXTMVVMVIEWMODELSTANDARDVIEWMODELCONTROLLERS_H
#define _QEXTMVVMVIEWMODELSTANDARDVIEWMODELCONTROLLERS_H

#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelController.h>

#include <string>
#include <vector>

//! @file viewmodelcontrollers.h
//! Collection of standard controllers for AbstractViewModel.

namespace ModelView
{

//! Controller for AbstractViewModel to show all items of SessionModel.
//! The layout corresponds to original SessionModel, generates standard label/value tree.

class QEXT_MVVM_API QEXTMvvmDefaultViewModelController : public QEXTMvvmViewModelController
{
public:
    explicit QEXTMvvmDefaultViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model);
};

//! Controller for AbstractViewModel to show top level items.
//! Shows only top level items, property items, group items are hidden.

class QEXT_MVVM_API QEXTMvvmTopItemsViewModelController : public QEXTMvvmViewModelController
{
public:
    explicit QEXTMvvmTopItemsViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model);
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyViewModelController : public QEXTMvvmViewModelController
{
public:
    explicit QEXTMvvmPropertyViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model);

protected:
    void onDataChange(QEXTMvvmSessionItem* item, int role) override;
};

//! Controller for AbstractViewModel to show item properties in table layout.
//! Shows all property items and place them in table columns.

class QEXT_MVVM_API QEXTMvvmPropertyTableViewModelController : public QEXTMvvmViewModelController
{
public:
    QEXTMvvmPropertyTableViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model,
                                     const std::vector<std::string>& labels = {});
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty,
//! moves subproperties of group item under parent of group item.

class QEXT_MVVM_API QEXTMvvmPropertyFlatViewModelController : public QEXTMvvmViewModelController
{
public:
    explicit QEXTMvvmPropertyFlatViewModelController(QEXTMvvmSessionModel* session_model,
                                             QEXTMvvmViewModelBase* view_model);

protected:
    void onDataChange(QEXTMvvmSessionItem* item, int role) override;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELSTANDARDVIEWMODELCONTROLLERS_H
