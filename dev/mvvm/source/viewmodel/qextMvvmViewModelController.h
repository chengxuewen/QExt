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

#include <qextMvvmModelListener.h>
#include <qextMvvmGlobal.h>
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmSessionItem;
class QExtMvvmViewModelBase;
class QExtMvvmViewItem;
class QExtMvvmChildrenStrategyInterface;
class QExtMvvmRowStrategyInterface;

//! Propagates changes from QExtMvvmSessionModel to its QExtMvvmViewModelBase.

class QEXT_MVVM_API QExtMvvmViewModelController : public QExtMvvmModelListener<QExtMvvmSessionModel> {
public:
    QExtMvvmViewModelController(QExtMvvmSessionModel* session_model, QExtMvvmViewModelBase* view_model = nullptr);
    ~QExtMvvmViewModelController() override;

    void setViewModel(QExtMvvmViewModelBase* view_model);

    void setChildrenStrategy(QExtUniquePointer<QExtMvvmChildrenStrategyInterface> children_strategy);

    void setRowStrategy(QExtUniquePointer<QExtMvvmRowStrategyInterface> row_strategy);

    QExtMvvmSessionModel* sessionModel() const;

    void setRootSessionItem(QExtMvvmSessionItem* item);

    QExtMvvmSessionItem* rootSessionItem() const;

    std::vector<QExtMvvmViewItem*> findViews(const ModelView::QExtMvvmSessionItem* item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(QExtMvvmSessionItem* item, int role);
    virtual void onItemInserted(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow);
    virtual void onItemRemoved(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow);
    virtual void onAboutToRemoveItem(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow);

    void update_branch(const QExtMvvmSessionItem* item);

private:
    struct ViewModelControllerImpl;
    QExtUniquePointer<ViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H
