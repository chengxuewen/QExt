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

#include <QWidget>
#include <memory>
#include <qextMvvmGlobal.h>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView
{

class QEXTMvvmSessionItem;
class ViewModel;
class ViewModelDelegate;

//! Tree view to show items of QEXTMvvmSessionModel via ViewModel mechanism.
//! Provides notification mechanism for QEXTMvvmSessionItem selections, use custom delegate.

class QEXT_MVVM_API ItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsTreeView(QWidget* parent = nullptr);
    ~ItemsTreeView() override;

    QTreeView* treeView();

    void setViewModel(std::unique_ptr<ViewModel> viewModel);

    void setViewModelDelegate(std::unique_ptr<ViewModelDelegate> delegate);

    void setSelected(QEXTMvvmSessionItem* item);

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    ViewModel* viewModel() const;

signals:
    void itemSelected(ModelView::QEXTMvvmSessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    std::unique_ptr<ViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEW_H
