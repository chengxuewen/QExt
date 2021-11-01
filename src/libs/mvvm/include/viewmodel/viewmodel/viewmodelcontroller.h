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

class QEXTMvvmSessionModel;
class QEXTMvvmSessionItem;
class ViewModelBase;
class ViewItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Propagates changes from QEXTMvvmSessionModel to its ViewModelBase.

class QEXT_MVVM_API ViewModelController : public QEXTMvvmModelListener<QEXTMvvmSessionModel>
{
public:
    ViewModelController(QEXTMvvmSessionModel* session_model, ViewModelBase* view_model = nullptr);
    ~ViewModelController();

    void setViewModel(ViewModelBase* view_model);

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    QEXTMvvmSessionModel* sessionModel() const;

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    QEXTMvvmSessionItem* rootSessionItem() const;

    std::vector<ViewItem*> findViews(const ModelView::QEXTMvvmSessionItem* item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(QEXTMvvmSessionItem* item, int role);
    virtual void onItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    virtual void onItemRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    virtual void onAboutToRemoveItem(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);

    void update_branch(const QEXTMvvmSessionItem* item);

private:
    struct ViewModelControllerImpl;
    std::unique_ptr<ViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
