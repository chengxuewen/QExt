#ifndef _QEXTMVVMREFVIEWMODELCONTROLLER_H
#define _QEXTMVVMREFVIEWMODELCONTROLLER_H

#include <QStringList>
#include <memory>
#include <qextMvvmTagRow.h>
#include <qextMvvmModelListener.h>
#include <qextMvvmGlobal.h>
#include <QVector>

class QStandardItem;

class QEXTMvvmModel;
class QEXTMvvmItem;
class QEXTMvvmViewModelBase;
class QEXTMvvmViewItem;
class QEXTMvvmChildrenStrategyInterface;
class QEXTMvvmRowStrategyInterface;

//! Propagates changes from QEXTMvvmModel to its QEXTMvvmViewModelBase.

class QEXT_MVVM_API QEXTMvvmViewModelController : public QEXTMvvmModelListener<QEXTMvvmModel>
{
public:
    QEXTMvvmViewModelController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel = QEXT_DECL_NULLPTR);
    ~QEXTMvvmViewModelController();

    void setViewModel(QEXTMvvmViewModelBase *viewModel);

    void setChildrenStrategy(QEXTMvvmChildrenStrategyInterface *childrenStrategy);

    void setRowStrategy(QEXTMvvmRowStrategyInterface *rowStrategy);

    QEXTMvvmModel *sessionModel() const;

    void setRootSessionItem(QEXTMvvmItem *item);

    QEXTMvvmItem *rootItem() const;

    QVector<QEXTMvvmViewItem *> findViews(const QEXTMvvmItem *item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(QEXTMvvmItem *item, int role);
    virtual void onItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    virtual void onItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    virtual void onAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);

    void updateBranch(const QEXTMvvmItem *item);

private:
    struct ViewModelControllerImpl;
    QScopedPointer<ViewModelControllerImpl> d;
};


#endif // _QEXTMVVMREFVIEWMODELCONTROLLER_H
