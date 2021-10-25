#ifndef _QEXTMVVMVIEWMODEL_H
#define _QEXTMVVMVIEWMODEL_H

#include <qextMvvmGlobal.h>

#include <cfMvvmModel.h>
#include <cfMvvmViewModelBase.h>
#include <cfMvvmViewModelController.h>

#include <QObject>
#include <QAbstractItemModel>

CF_USE_NAMESPACE

class QEXTMvvmViewModelPrivate;
class QEXT_MVVM_API QEXTMvvmViewModel : public QAbstractItemModel, public CFMvvmViewModelBase
{
public:
    QEXTMvvmViewModel(CFMvvmViewModelController *controller, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmViewModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const QEXT_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const QEXT_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) QEXT_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const QEXT_DECL_OVERRIDE;

    CFMvvmModel *model() const;
    CFMvvmItem *rootItem() const;
    void setRootItem(CFMvvmItem *item);

    QModelIndexList indexsOfItem(const CFMvvmItem *item) const;
    CFMvvmItem *itemFromIndex(const QModelIndex &index) const;

    QModelIndex indexFromViewItem(const CFMvvmViewItem *item) const;
    CFMvvmViewItem *viewItemFromIndex(const QModelIndex &index) const;

    std::vector<CFMvvmViewItem *> findViewItems(const CFMvvmItem *item) const QEXT_DECL_OVERRIDE;

    void itemDataChanged(const CFMvvmViewItem *item) QEXT_DECL_OVERRIDE;
    bool isItemValid(const CFMvvmViewItem *item) QEXT_DECL_OVERRIDE;

    void beginResetViewModel() QEXT_DECL_OVERRIDE;
    void beginRemoveViewRows(const CFMvvmViewItem *parent, int first, int last) QEXT_DECL_OVERRIDE;
    void beginInsertViewRows(const CFMvvmViewItem *parent, int first, int last) QEXT_DECL_OVERRIDE;

    void endResetViewModel() QEXT_DECL_OVERRIDE;
    void endRemoveViewRows() QEXT_DECL_OVERRIDE;
    void endInsertViewRows() QEXT_DECL_OVERRIDE;

private:
    CF_DECL_PRIVATE(QEXTMvvmViewModel)
    CF_DECL_DISABLE_COPY_MOVE(QEXTMvvmViewModel)
};

#endif // _QEXTMVVMVIEWMODEL_H
