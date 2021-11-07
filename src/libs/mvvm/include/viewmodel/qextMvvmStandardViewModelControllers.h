#ifndef _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H
#define _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H

#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelController.h>
#include <string>
#include <QVector>

//! @file viewmodelcontrollers.h
//! Collection of standard controllers for AbstractViewModel.


//! Controller for AbstractViewModel to show all items of QEXTMvvmModel.
//! The layout corresponds to original QEXTMvvmModel, generates standard label/value tree.

    class QEXT_MVVM_API QEXTMvvmDefaultViewModelController : public QEXTMvvmViewModelController
    {
    public:
        explicit QEXTMvvmDefaultViewModelController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel);
    };

//! Controller for AbstractViewModel to show top level items.
//! Shows only top level items, property items, group items are hidden.

    class QEXT_MVVM_API QEXTMvvmTopItemsViewModelController : public QEXTMvvmViewModelController
    {
    public:
        explicit QEXTMvvmTopItemsViewModelController(QEXTMvvmModel *session_model, QEXTMvvmViewModelBase *view_model);
    };

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty.

    class QEXT_MVVM_API QEXTMvvmPropertyViewModelController : public QEXTMvvmViewModelController
    {
    public:
        explicit QEXTMvvmPropertyViewModelController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel);

    protected:
        void onDataChange(QEXTMvvmItem *item, int role) QEXT_DECL_OVERRIDE;
    };

//! Controller for AbstractViewModel to show item properties in table layout.
//! Shows all property items and place them in table columns.

    class QEXT_MVVM_API QEXTMvvmPropertyTableViewModelController : public QEXTMvvmViewModelController
    {
    public:
        QEXTMvvmPropertyTableViewModelController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel,
                const QVector<QString> &labels = {});
    };

//! Controller for AbstractViewModel to show item properties.
//! Shows property items, hides top level items, hides inactive items of GroupProperty,
//! moves subproperties of group item under parent of group item.

    class QEXT_MVVM_API QEXTMvvmPropertyFlatViewModelController : public QEXTMvvmViewModelController
    {
    public:
        explicit QEXTMvvmPropertyFlatViewModelController(QEXTMvvmModel *session_model,
                QEXTMvvmViewModelBase *viewModel);

    protected:
        void onDataChange(QEXTMvvmItem *item, int role) QEXT_DECL_OVERRIDE;
    };


#endif // _QEXTMVVMSTANDARDVIEWMODELCONTROLLERS_H
