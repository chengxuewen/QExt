#ifndef _QEXTMVVMVIEWMODELBASE_H
#define _QEXTMVVMVIEWMODELBASE_H

#include <qextMvvmGlobal.h>

#include <QAbstractItemModel>
#include <QScopedPointer>


    class QEXTMvvmViewItem;

//! Base class for all view models to show content of QEXTMvvmModel in Qt views.
//! QEXTMvvmViewModelBase is made of ViewItems, where each QEXTMvvmViewItem represents some concrete data role
//!  of QEXTMvvmItem. QEXTMvvmViewModelBase doesn't have own logic and needs QEXTMvvmViewModelController to listen
//! for QEXTMvvmModel changes.

    class QEXT_MVVM_API QEXTMvvmViewModelBase : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        explicit QEXTMvvmViewModelBase(QObject *parent = nullptr);
        ~QEXTMvvmViewModelBase() QEXT_DECL_OVERRIDE;

        QModelIndex index(int row, int column,
                          const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;

        QModelIndex parent(const QModelIndex &child) const QEXT_DECL_OVERRIDE;

        int rowCount(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;

        int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const QEXT_DECL_OVERRIDE;

        bool setData(const QModelIndex &index, const QVariant &value, int role) QEXT_DECL_OVERRIDE;

        QEXTMvvmViewItem *rootItem() const;

        QEXTMvvmViewItem *itemFromIndex(const QModelIndex &index) const;

        QModelIndex indexFromItem(const QEXTMvvmViewItem *item) const;

        void removeRow(QEXTMvvmViewItem *parent, int row);

        void clearRows(QEXTMvvmViewItem *parent);

        void insertRow(QEXTMvvmViewItem *parent, int row, QVector<QEXTMvvmViewItem *> items);

        void appendRow(QEXTMvvmViewItem *parent, QVector<QEXTMvvmViewItem *> items);

        Qt::ItemFlags flags(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    private:
        void setRootViewItem(QEXTMvvmViewItem *root_item);
        friend class QEXTMvvmViewModelController;
        struct ViewModelBaseImpl;
        QScopedPointer<ViewModelBaseImpl> p_impl;
    };


#endif // _QEXTMVVMVIEWMODELBASE_H
