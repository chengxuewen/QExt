// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H
#define MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H

#include "model/signals/modellistener.h"
#include "qextMVVMGlobal.h"
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class SessionModel;
class SessionItem;
class ViewModelBase;
class ViewItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Propagates changes from SessionModel to its ViewModelBase.

class QEXT_MVVM_API ViewModelController : public ModelListener<SessionModel> {
public:
    ViewModelController(SessionModel* session_model, ViewModelBase* view_model = nullptr);
    ~ViewModelController() override;

    void setViewModel(ViewModelBase* view_model);

    void setChildrenStrategy(QExtUniquePointer<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(QExtUniquePointer<RowStrategyInterface> row_strategy);

    SessionModel* sessionModel() const;

    void setRootSessionItem(SessionItem* item);

    SessionItem* rootSessionItem() const;

    std::vector<ViewItem*> findViews(const ModelView::SessionItem* item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onItemInserted(SessionItem* parent, TagRow tagrow);
    virtual void onItemRemoved(SessionItem* parent, TagRow tagrow);
    virtual void onAboutToRemoveItem(SessionItem* parent, TagRow tagrow);

    void update_branch(const SessionItem* item);

private:
    struct ViewModelControllerImpl;
    QExtUniquePointer<ViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H
