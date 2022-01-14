#ifndef _QEXTMVVMWIDGETSITEMSTREEVIEW_H
#define _QEXTMVVMWIDGETSITEMSTREEVIEW_H

#include <qextMvvmGlobal.h>

#include <QWidget>

#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;

//! Tree view to show items of SessionModel via ViewModel mechanism.
//! Provides notification mechanism for QEXTMvvmSessionItem selections, use custom delegate.

class QEXT_MVVM_API QEXTMvvmItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmItemsTreeView(QWidget* parent = nullptr);
    ~QEXTMvvmItemsTreeView() override;

    QTreeView* treeView();

    void setViewModel(std::unique_ptr<QEXTMvvmViewModel> viewModel);

    void setViewModelDelegate(std::unique_ptr<QEXTMvvmViewModelDelegate> delegate);

    void setSelected(QEXTMvvmSessionItem* item);

    void setRootSessionItem(QEXTMvvmSessionItem* item);

    QEXTMvvmViewModel* viewModel() const;

signals:
    void itemSelected(ModelView::QEXTMvvmSessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    std::unique_ptr<QEXTMvvmViewModel> m_viewModel;
    std::unique_ptr<QEXTMvvmViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSITEMSTREEVIEW_H
