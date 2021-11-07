// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <qextGlobal.h>

#include <QWidget>
#include <QScopedPointer>

class QBoxLayout;
class QTreeView;
class QTableView;

class QEXTMvvmViewModel;
class QEXTMvvmViewModelDelegate;


namespace CellEditors
{

class SampleModel;

//! Shows content of the model as vertical tree, horizontal tree and table.

class ModelEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelEditorWidget(SampleModel* model = nullptr, QWidget* parent = nullptr);
    virtual ~ModelEditorWidget() QEXT_DECL_OVERRIDE;

    void setModel(SampleModel* model);

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    QTreeView* m_verticalTree{nullptr};
    QTreeView* m_horizontalTree{nullptr};
    QTableView* m_tableView{nullptr};

    QScopedPointer<QEXTMvvmViewModel> m_verticalViewModel;
    QScopedPointer<QEXTMvvmViewModel> m_horizontalViewModel;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
};

} // namespace CellEditors

#endif // MODELEDITORWIDGET_H
