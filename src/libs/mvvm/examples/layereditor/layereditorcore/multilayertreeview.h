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
#include <memory>

class QTreeView;
class ApplicationModels;

namespace ModelView
{
class QEXTMvvmViewModel;
class QEXTMvvmSessionItem;
class QEXTMvvmViewModelDelegate;
} // namespace ModelView

//! Shows content of multi layer in a tree view in special "flat" form.

class MultiLayerTreeView : public QWidget
{
public:
    explicit MultiLayerTreeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~MultiLayerTreeView();

    void setItem(ModelView::QEXTMvvmSessionItem* multilayer);

private:
    QTreeView* m_treeView;
    std::unique_ptr<ModelView::QEXTMvvmViewModel> m_viewModel;
    std::unique_ptr<ModelView::QEXTMvvmViewModelDelegate> m_delegate;
};

#endif // MULTILAYERTREEVIEW_H
