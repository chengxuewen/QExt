// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGANDMOVECORE_CONTAINEREDITORWIDGET_H
#define DRAGANDMOVECORE_CONTAINEREDITORWIDGET_H

#include <QWidget>
#include <qextMemory.h>
#include <vector>

class QTreeView;
class QBoxLayout;
class QItemSelectionModel;

namespace ModelView {
class QExtMvvmViewModel;
class QExtMvvmViewModelDelegate;
class QExtMvvmSessionItem;
} // namespace ModelView

namespace DragAndMove {

class SampleModel;

//! Shows content of container and provide functionality to add, copy and move items.

class ContainerEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ContainerEditorWidget(QWidget* parent = nullptr);
    ~ContainerEditorWidget();

    void setModel(SampleModel* model, ModelView::QExtMvvmSessionItem* root_item = nullptr);

private slots:
    void onAdd();
    void onCopy();
    void onRemove();
    void onMoveDown();
    void onMoveUp();

private:
    std::vector<ModelView::QExtMvvmSessionItem*> selected_items() const;
    QBoxLayout* create_button_layout();

    QTreeView* m_treeView{nullptr};
    QExtUniquePointer<ModelView::QExtMvvmViewModel> m_viewModel;
    QExtUniquePointer<ModelView::QExtMvvmViewModelDelegate> m_delegate;
    ModelView::QExtMvvmSessionItem* m_container{nullptr};
    SampleModel* m_model{nullptr};
};

} // namespace DragAndMove

#endif // DRAGANDMOVECORE_CONTAINEREDITORWIDGET_H
