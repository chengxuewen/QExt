// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEWIDGETS_H
#define MATERIALTABLEWIDGETS_H

#include <QWidget>
#include <QScopedPointer>

class QTreeView;
class MaterialModel;


class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;
class QEXTMvvmItem;


//! Shows content of material container in table-like view.

class MaterialTableWidget : public QWidget
{
public:
    explicit MaterialTableWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialTableWidget() QEXT_DECL_OVERRIDE;

    void setItem(QEXTMvvmItem* material_container);

    QTreeView* treeView();

private:
    QTreeView* m_treeView;
    QScopedPointer<QEXTMvvmViewModel> m_viewModel;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
};

#endif // MATERIALTABLEWIDGETS_H
