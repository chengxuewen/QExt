// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
#define MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H

#include <QStringList>
#include <memory>
#include <qextMvvmTagRow.h>
#include <qextMvvmModelListener.h>
#include <qextMvvmGlobal.h>
#include <vector>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class QEXTMvvmSessionItem;
class ViewModelBase;
class ViewItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Propagates changes from SessionModel to its ViewModelBase.

class QEXT_MVVM_API ViewModelController : public ModelListener<SessionModel>
{
public:
    ViewModelController(SessionModel* session_model, ViewModelBase* view_model = nullptr);
    ~ViewModelController();

    void setViewModel(ViewModelBase* view_model);

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    SessionModel* sessionModel() const;

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    QEXTMvvmSessionItem* rootSessionItem() const;

    std::vector<ViewItem*> findViews(const ModelView::QEXTMvvmSessionItem* item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(QEXTMvvmSessionItem* item, int role);
    virtual void onItemInserted(QEXTMvvmSessionItem* parent, TagRow tagrow);
    virtual void onItemRemoved(QEXTMvvmSessionItem* parent, TagRow tagrow);
    virtual void onAboutToRemoveItem(QEXTMvvmSessionItem* parent, TagRow tagrow);

    void update_branch(const QEXTMvvmSessionItem* item);

private:
    struct ViewModelControllerImpl;
    std::unique_ptr<ViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
