// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MULTILAYERTREEVIEW_H
#define MULTILAYERTREEVIEW_H

#include <QWidget>
#include <QScopedPointer>

class QTreeView;
class ApplicationModels;


class QEXTMvvmViewModel;
class QEXTMvvmItem;
class QEXTMvvmViewModelDelegate;


//! Shows content of multi layer in a tree view in special "flat" form.

class MultiLayerTreeView : public QWidget
{
public:
    explicit MultiLayerTreeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~MultiLayerTreeView();

    void setItem(QEXTMvvmItem* multilayer);

private:
    QTreeView* m_treeView;
    QScopedPointer<QEXTMvvmViewModel> m_viewModel;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
};

#endif // MULTILAYERTREEVIEW_H
