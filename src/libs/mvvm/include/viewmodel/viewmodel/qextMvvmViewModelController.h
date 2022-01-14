#ifndef _QEXTMVVMVIEWMODELREFVIEWMODELCONTROLLER_H
#define _QEXTMVVMVIEWMODELREFVIEWMODELCONTROLLER_H

#include <qextMvvmTagRow.h>
#include <qextMvvmModelListener.h>
#include <qextMvvmGlobal.h>

#include <QStringList>

#include <memory>
#include <vector>

class QStandardItem;

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmSessionItem;
class QEXTMvvmViewModelBase;
class QEXTMvvmViewItem;
class QEXTMvvmChildrenStrategyInterface;
class QEXTMvvmRowStrategyInterface;

//! Propagates changes from SessionModel to its ViewModelBase.

class QEXT_MVVM_API QEXTMvvmViewModelController : public QEXTMvvmModelListener<QEXTMvvmSessionModel>
{
public:
    QEXTMvvmViewModelController(QEXTMvvmSessionModel* session_model, QEXTMvvmViewModelBase* view_model = nullptr);
    ~QEXTMvvmViewModelController();

    void setViewModel(QEXTMvvmViewModelBase* view_model);

    void setChildrenStrategy(std::unique_ptr<QEXTMvvmChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<QEXTMvvmRowStrategyInterface> row_strategy);

    QEXTMvvmSessionModel* sessionModel() const;

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    QEXTMvvmSessionItem* rootSessionItem() const;

    std::vector<QEXTMvvmViewItem*> findViews(const ModelView::QEXTMvvmSessionItem* item) const;

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

#endif // _QEXTMVVMVIEWMODELREFVIEWMODELCONTROLLER_H
