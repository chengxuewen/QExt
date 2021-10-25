#ifndef _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H
#define _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H

#include <qextMvvmGlobal.h>

#include <cfMvvmItem.h>
#include <cfMvvmModel.h>
#include <cfMvvmViewModelBase.h>
#include <cfMvvmViewModelController.h>

#include <vector>

CF_USE_NAMESPACE

//! Controller for AbstractViewModel to show all items of SessionModel.
//! The layout corresponds to original SessionModel, generates standard label/value tree.

class QEXT_MVVM_API QEXTMvvmDefaultViewModelController : public CFMvvmViewModelController
{
public:
    QEXTMvvmDefaultViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel);
};

//! Controller for AbstractViewModel to show top level items.
//! Shows only top level items, property items, group items are hidden.

class QEXT_MVVM_API QEXTMvvmTopItemsViewModelController : public CFMvvmViewModelController
{
public:
    QEXTMvvmTopItemsViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel);
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty.

class QEXT_MVVM_API QEXTMvvmPropertyViewModelController : public CFMvvmViewModelController
{
public:
    QEXTMvvmPropertyViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel);

protected:
    void onDataChange(CFMvvmItem *item, int role) QEXT_DECL_OVERRIDE;
};

//! Controller for AbstractViewModel to show item properties in table layout.
//! Shows all property items and place them in table columns.

class QEXT_MVVM_API QEXTMvvmPropertyTableViewModelController : public CFMvvmViewModelController
{
public:
    QEXTMvvmPropertyTableViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel,
                                             const std::vector<std::string> &labels = std::vector<std::string>());
};

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty,
//! moves subproperties of group item under parent of group item.

class QEXT_MVVM_API QEXTMvvmPropertyFlatViewModelController : public CFMvvmViewModelController
{
public:
    QEXTMvvmPropertyFlatViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel);

protected:
    void onDataChange(CFMvvmItem *item, int role) QEXT_DECL_OVERRIDE;
};


#endif // _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H
