#ifndef _QEXTMVVMVIEWMODELVIEWMODELBASE_H
#define _QEXTMVVMVIEWMODELVIEWMODELBASE_H

#include <qextMvvmGlobal.h>

#include <QAbstractItemModel>

#include <memory>

namespace ModelView
{

class QEXTMvvmViewItem;

//! Base class for all view models to show content of SessionModel in Qt views.
//! ViewModelBase is made of ViewItems, where each ViewItem represents some concrete data role
//!  of QEXTMvvmSessionItem. ViewModelBase doesn't have own logic and needs ViewModelController to listen
//! for SessionModel changes.

class QEXT_MVVM_API QEXTMvvmViewModelBase : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QEXTMvvmViewModelBase(QObject* parent = nullptr);
    ~QEXTMvvmViewModelBase() override;

    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    QEXTMvvmViewItem* rootItem() const;

    QEXTMvvmViewItem* itemFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromItem(const QEXTMvvmViewItem* item) const;

    void removeRow(QEXTMvvmViewItem* parent, int row);

    void clearRows(QEXTMvvmViewItem* parent);

    void insertRow(QEXTMvvmViewItem* parent, int row, std::vector<std::unique_ptr<QEXTMvvmViewItem>> items);

    void appendRow(QEXTMvvmViewItem* parent, std::vector<std::unique_ptr<QEXTMvvmViewItem>> items);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    void setRootViewItem(std::unique_ptr<QEXTMvvmViewItem> root_item);
    friend class QEXTMvvmViewModelController;
    struct ViewModelBaseImpl;
    std::unique_ptr<ViewModelBaseImpl> p_impl;
};

}; // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWMODELBASE_H
