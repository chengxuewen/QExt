// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CONTAINEREDITORWIDGET_H
#define CONTAINEREDITORWIDGET_H

#include <QWidget>

#include <memory>
#include <vector>

class SampleModel;
class QTreeView;
class QBoxLayout;
class QItemSelectionModel;

namespace ModelView
{
class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;
class QEXTMvvmSessionItem;
} // namespace ModelView

//! Shows content of container and provide functionality to add, copy and move items.

class ContainerEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerEditorWidget(QWidget* parent = nullptr);
    ~ContainerEditorWidget();

    void setModel(SampleModel* model, ModelView::QEXTMvvmSessionItem* root_item = nullptr);

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

private slots:
    void onAdd();
    void onCopy();
    void onRemove();
    void onMoveDown();
    void onMoveUp();

private:
    std::vector<ModelView::QEXTMvvmSessionItem*> selected_items() const;
    QBoxLayout* create_button_layout();

    QTreeView* m_treeView{nullptr};
    std::unique_ptr<ModelView::QEXTMvvmViewModel> m_viewModel;
    std::unique_ptr<ModelView::QEXTMvvmViewModelDelegate> m_delegate;
    SampleModel* m_model{nullptr};
};

#endif // CONTAINEREDITORWIDGET_H
