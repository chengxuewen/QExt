// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ITEMSTREEVIEW_H
#define MVVM_WIDGETS_ITEMSTREEVIEW_H

#include <qextMvvmGlobal.h>
#include <QWidget>
#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmViewModel;
class QExtMvvmViewModelDelegate;

//! Tree view to show items of QExtMvvmSessionModel via QExtMvvmViewModel mechanism.
//! Provides notification mechanism for QExtMvvmSessionItem selections, use custom delegate.

class QEXT_MVVM_API QExtMvvmItemsTreeView : public QWidget {
    Q_OBJECT

public:
    explicit QExtMvvmItemsTreeView(QWidget* parent = nullptr);
    ~QExtMvvmItemsTreeView() override;

    QTreeView* treeView();

    void setViewModel(QExtUniquePointer<QExtMvvmViewModel> viewModel);

    void setViewModelDelegate(QExtUniquePointer<QExtMvvmViewModelDelegate> delegate);

    void setSelected(QExtMvvmSessionItem* item);

    void setRootSessionItem(QExtMvvmSessionItem* item);

    QExtMvvmViewModel* viewModel() const;

signals:
    void itemSelected(ModelView::QExtMvvmSessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    QExtUniquePointer<QExtMvvmViewModel> m_viewModel;
    QExtUniquePointer<QExtMvvmViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEW_H
