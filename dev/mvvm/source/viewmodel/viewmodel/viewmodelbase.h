// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELBASE_H
#define MVVM_VIEWMODEL_VIEWMODELBASE_H

#include <qextMvvmGlobal.h>
#include <QAbstractItemModel>
#include <memory>

namespace ModelView {

class QExtMvvmViewItem;

//! Base class for all view models to show content of QExtMvvmSessionModel in Qt views.
//! QExtMvvmViewModelBase is made of ViewItems, where each QExtMvvmViewItem represents some concrete data role
//! of QExtMvvmSessionItem. QExtMvvmViewModelBase doesn't have own logic and needs QExtMvvmViewModelController to listen
//! for QExtMvvmSessionModel changes.

class QEXT_MVVM_API QExtMvvmViewModelBase : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit QExtMvvmViewModelBase(QObject* parent = nullptr);
    ~QExtMvvmViewModelBase() override;

    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    QExtMvvmViewItem* rootItem() const;

    QExtMvvmViewItem* itemFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromItem(const QExtMvvmViewItem* item) const;

    void removeRow(QExtMvvmViewItem* parent, int row);

    void clearRows(QExtMvvmViewItem* parent);

    virtual void insertRow(QExtMvvmViewItem* parent, int row, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items);

    void appendRow(QExtMvvmViewItem* parent, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    void setRootViewItem(QExtUniquePointer<QExtMvvmViewItem> root_item);
    friend class QExtMvvmViewModelController;
    struct ViewModelBaseImpl;
    QExtUniquePointer<ViewModelBaseImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELBASE_H
