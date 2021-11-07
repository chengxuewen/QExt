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
#include <QScopedPointer>
#include <QVector>

class QTreeView;
class QBoxLayout;
class QItemSelectionModel;


class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;
class QEXTMvvmItem;


namespace DragAndView
{

class SampleModel;

//! Shows content of container and provide functionality to add, copy and move items.

class ContainerEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerEditorWidget(QWidget* parent = nullptr);
    ~ContainerEditorWidget();

    void setModel(SampleModel* model, QEXTMvvmItem* root_item = nullptr);

private slots:
    void onAdd();
    void onCopy();
    void onRemove();
    void onMoveDown();
    void onMoveUp();

private:
    QVector<QEXTMvvmItem*> selected_items() const;
    QBoxLayout* create_button_layout();

    QTreeView* m_treeView{nullptr};
    QScopedPointer<QEXTMvvmViewModel> m_viewModel;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
    QEXTMvvmItem* m_container{nullptr};
    SampleModel* m_model{nullptr};
};

} // namespace DragAndView

#endif // CONTAINEREDITORWIDGET_H
