// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_MULTILAYERTREEVIEW_H
#define LAYEREDITORCORE_MULTILAYERTREEVIEW_H

#include <QWidget>
#include <qextMemory.h>

class QTreeView;
class ApplicationModels;

namespace ModelView {
class QExtMvvmViewModel;
class QExtMvvmSessionItem;
class QExtMvvmViewModelDelegate;
} // namespace ModelView

//! Shows content of multi layer in a tree view in special "flat" form.

class MultiLayerTreeView : public QWidget {
public:
    explicit MultiLayerTreeView(ApplicationModels* models, QWidget* parent = nullptr);
    ~MultiLayerTreeView();

    void setItem(ModelView::QExtMvvmSessionItem* multilayer);

private:
    QTreeView* m_treeView{nullptr};
    QExtUniquePointer<ModelView::QExtMvvmViewModel> m_viewModel;
    QExtUniquePointer<ModelView::QExtMvvmViewModelDelegate> m_delegate;
};

#endif // LAYEREDITORCORE_MULTILAYERTREEVIEW_H
