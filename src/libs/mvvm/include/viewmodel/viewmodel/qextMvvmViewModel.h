#ifndef _QEXTMVVMVIEWMODELVIEWMODEL_H
#define _QEXTMVVMVIEWMODELVIEWMODEL_H

#include <qextMvvmViewModelBase.h>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmSessionItem;
class QEXTMvvmViewItem;
class QEXTMvvmViewModelController;

//! Main class to represent content of SessionModel in Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewModel : public QEXTMvvmViewModelBase
{
    Q_OBJECT

public:
    QEXTMvvmViewModel(std::unique_ptr<QEXTMvvmViewModelController> controller, QObject* parent = nullptr);
    ~QEXTMvvmViewModel() override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QEXTMvvmSessionModel* sessionModel() const;

    QEXTMvvmSessionItem* rootSessionItem();

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    QEXTMvvmSessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    QEXTMvvmViewItem* viewItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const QEXTMvvmSessionItem* item) const;

    std::vector<QEXTMvvmViewItem*> findViews(const ModelView::QEXTMvvmSessionItem* item) const;

private:
    std::unique_ptr<QEXTMvvmViewModelController> m_controller;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWMODEL_H
