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

#include "qextMVVMGlobal.h"
#include <QWidget>
#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView {

class SessionItem;
class ViewModel;
class ViewModelDelegate;

//! Tree view to show items of SessionModel via ViewModel mechanism.
//! Provides notification mechanism for SessionItem selections, use custom delegate.

class QEXT_MVVM_API ItemsTreeView : public QWidget {
    Q_OBJECT

public:
    explicit ItemsTreeView(QWidget* parent = nullptr);
    ~ItemsTreeView() override;

    QTreeView* treeView();

    void setViewModel(QExtUniquePointer<ViewModel> viewModel);

    void setViewModelDelegate(QExtUniquePointer<ViewModelDelegate> delegate);

    void setSelected(SessionItem* item);

    void setRootSessionItem(SessionItem* item);

    ViewModel* viewModel() const;

signals:
    void itemSelected(ModelView::SessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    QExtUniquePointer<ViewModel> m_viewModel;
    QExtUniquePointer<ViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEW_H
