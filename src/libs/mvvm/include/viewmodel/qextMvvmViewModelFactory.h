#ifndef _QEXTMVVMSTANDARDVIEWMODELS_H
#define _QEXTMVVMSTANDARDVIEWMODELS_H

#include <qextMvvmGlobal.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelControllerBuilder.h>

#include <QSharedPointer>

class QEXTMvvmModel;
class QEXTMvvmViewModel;

struct QEXT_MVVM_API QEXTMvvmViewModelFactory
{
    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! The model has two columns, all items are shown.
    static QEXTMvvmViewModel *createDefaultViewModel(QEXTMvvmModel *model);

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! The model has two columns, shows only property items and simplified group items.
    static QEXTMvvmViewModel *createPropertyViewModel(QEXTMvvmModel *model);

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! Shows all properties of QEXTMvvmCompoundItem in columns of the table, rows of the table represent
    //! different CompoundItems. Items of same type and table like structure of the model are expected.
    static QEXTMvvmViewModel *createPropertyTableViewModel(QEXTMvvmModel *model);

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! Shows only top items.
    static QEXTMvvmViewModel *createTopItemsViewModel(QEXTMvvmModel *model);

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! The model has two columns, shows only property items and simplified group items.
    //! Subproperties of group item moved one level up.
    static QEXTMvvmViewModel *createPropertyFlatViewModel(QEXTMvvmModel *model);

    //! Create universal controller.
    template <typename ChildrenStrategy, typename RowStrategy>
    static QEXTMvvmViewModelController *createController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel)
    {
        return QEXTMvvmViewModelControllerBuilder()
                .model(model)
                .viewModel(viewModel)
                .childrenStrategy(new ChildrenStrategy)
                .rowStrategy(new RowStrategy);
    }

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! Use user provided types for ChildrenStrategy and RowStrategy.
    template <typename ChildrenStrategy, typename RowStrategy>
    static QEXTMvvmViewModel *createViewModel(QEXTMvvmModel *model)
    {
        auto controller = createController<ChildrenStrategy, RowStrategy>(model, QEXT_DECL_NULLPTR);
        return new QEXTMvvmViewModel(controller);
    }

    //! Creates view model to represent QEXTMvvmModel for Qt views.
    //! Use user provided controller type.
    template <typename QEXTMvvmViewModelController>
    static QEXTMvvmViewModel *createViewModel(QEXTMvvmModel *model)
    {
        auto controller = new QEXTMvvmViewModelController(model);
        return new QEXTMvvmViewModel(controller);
    }

};

#endif // _QEXTMVVMSTANDARDVIEWMODELS_H
