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

#include <qextGlobal.h>

#include <QWidget>
#include <QScopedPointer>
#include <QVector>

class SampleModel;
class QTreeView;
class QBoxLayout;
class QItemSelectionModel;


class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;
class QEXTMvvmItem;


//! Shows content of container and provide functionality to add, copy and move items.

class ContainerEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerEditorWidget(QWidget* parent = nullptr);
    ~ContainerEditorWidget();

    void setModel(SampleModel* model, QEXTMvvmItem* root_item = nullptr);

    QSize sizeHint() const QEXT_DECL_OVERRIDE;

    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

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
    SampleModel* m_model{nullptr};
};

#endif // CONTAINEREDITORWIDGET_H
