// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODEL_H
#define MVVM_VIEWMODEL_VIEWMODEL_H

#include "viewmodel/viewmodel/viewmodelbase.h"

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmSessionItem;
class QExtMvvmViewItem;
class QExtMvvmViewModelController;

//! Main class to represent content of QExtMvvmSessionModel in Qt's trees and tables.

class QEXT_MVVM_API QExtMvvmViewModel : public QExtMvvmViewModelBase {
    Q_OBJECT

public:
    QExtMvvmViewModel(QExtUniquePointer<QExtMvvmViewModelController> controller, QObject* parent = nullptr);
    ~QExtMvvmViewModel() override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QExtMvvmSessionModel* sessionModel() const;

    QExtMvvmSessionItem* rootSessionItem();

    void setRootSessionItem(QExtMvvmSessionItem* item);

    QExtMvvmSessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    QExtMvvmViewItem* viewItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const QExtMvvmSessionItem* item) const;

    std::vector<QExtMvvmViewItem*> findViews(const ModelView::QExtMvvmSessionItem* item) const;

private:
    QExtUniquePointer<QExtMvvmViewModelController> m_controller;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODEL_H
