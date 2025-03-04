// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CELLEDITORSCORE_MODELEDITORWIDGET_H
#define CELLEDITORSCORE_MODELEDITORWIDGET_H

#include <QWidget>
#include <qextMemory.h>

class QBoxLayout;
class QTreeView;
class QTableView;

namespace ModelView {
class QExtMvvmViewModel;
class QExtMvvmViewModelDelegate;
} // namespace ModelView

namespace CellEditors {

class SampleModel;

//! Shows content of the model as vertical tree, horizontal tree and table.

class ModelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    virtual ~ModelEditorWidget() override;

    void setModel(SampleModel* model);

private:
    QBoxLayout* createLeftLayout();
    QBoxLayout* createRightLayout();

    QTreeView* m_verticalTree{nullptr};
    QTreeView* m_horizontalTree{nullptr};
    QTableView* m_tableView{nullptr};

    QExtUniquePointer<ModelView::QExtMvvmViewModel> m_verticalViewModel;
    QExtUniquePointer<ModelView::QExtMvvmViewModel> m_horizontalViewModel;
    QExtUniquePointer<ModelView::QExtMvvmViewModelDelegate> m_delegate;
};

} // namespace CellEditors

#endif // CELLEDITORSCORE_MODELEDITORWIDGET_H
