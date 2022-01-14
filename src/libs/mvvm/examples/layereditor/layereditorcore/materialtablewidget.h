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
#include <memory>

class QTreeView;
class MaterialModel;

namespace ModelView
{
class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;
class QEXTMvvmSessionItem;
} // namespace ModelView

//! Shows content of material container in table-like view.

class MaterialTableWidget : public QWidget
{
public:
    explicit MaterialTableWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialTableWidget() override;

    void setItem(ModelView::QEXTMvvmSessionItem* material_container);

    QTreeView* treeView();

private:
    QTreeView* m_treeView;
    std::unique_ptr<ModelView::QEXTMvvmViewModel> m_viewModel;
    std::unique_ptr<ModelView::QEXTMvvmViewModelDelegate> m_delegate;
};

#endif // MATERIALTABLEWIDGETS_H
