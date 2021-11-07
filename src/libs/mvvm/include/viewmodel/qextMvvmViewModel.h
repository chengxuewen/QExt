#ifndef _QEXTMVVMVIEWMODEL_H
#define _QEXTMVVMVIEWMODEL_H

#include <qextMvvmViewModelBase.h>

#include <QScopedPointer>

class QEXTMvvmModel;
class QEXTMvvmItem;
class QEXTMvvmViewItem;
class QEXTMvvmViewModelController;

//! Main class to represent content of QEXTMvvmModel in Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewModel : public QEXTMvvmViewModelBase
{
    Q_OBJECT

public:
    QEXTMvvmViewModel(QEXTMvvmViewModelController *controller, QObject *parent = nullptr);
    ~QEXTMvvmViewModel() QEXT_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const QEXT_DECL_OVERRIDE;

    QEXTMvvmModel *model() const;

    QEXTMvvmItem *rootItem();

    void setRootItem(QEXTMvvmItem *item);

    QEXTMvvmItem *itemFromIndex(const QModelIndex &index) const;

    QEXTMvvmViewItem *viewItemFromIndex(const QModelIndex &index) const;

    QModelIndexList indexOfItem(const QEXTMvvmItem *item) const;

    QVector<QEXTMvvmViewItem *> findViews(const QEXTMvvmItem *item) const;

private:
    QScopedPointer<QEXTMvvmViewModelController> m_controller;
};


#endif // _QEXTMVVMVIEWMODEL_H
