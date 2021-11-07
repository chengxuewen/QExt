#ifndef _QEXTMVVMITEMSTREEVIEW_H
#define _QEXTMVVMITEMSTREEVIEW_H

#include <qextMvvmGlobal.h>

#include <QWidget>
#include <QScopedPointer>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

class QEXTMvvmItem;
class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;

//! Tree view to show items of QEXTMvvmModel via QEXTMvvmViewModel mechanism.
//! Provides notification mechanism for QEXTMvvmItem selections, use custom delegate.

class QEXT_MVVM_API QEXTMvvmItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmItemsTreeView(QWidget* parent = nullptr);
    ~QEXTMvvmItemsTreeView() QEXT_DECL_OVERRIDE;

    QTreeView* treeView();

    void setViewModel(QEXTMvvmViewModel *viewModel);

    void setViewModelDelegate(QEXTMvvmViewModelDelegate *delegate);

    void setSelected(QEXTMvvmItem* item);

    void setRootSessionItem(QEXTMvvmItem* item);

    QEXTMvvmViewModel* viewModel() const;

signals:
    void itemSelected(QEXTMvvmItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    QScopedPointer<QEXTMvvmViewModel> m_viewModel;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
    bool m_block_selection;
};


#endif // _QEXTMVVMITEMSTREEVIEW_H
