// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEEDITORWIDGET_H
#define SAMPLEEDITORWIDGET_H

#include <QWidget>
#include <memory>


class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmAllItemsTreeView;
class QEXTMvvmPropertyTreeView;
class QEXTMvvmTopItemsTreeView;


class QTreeView;
class QUndoView;
class QBoxLayout;

namespace TreeViews
{

//! Collection of tree editors.

class SampleEditorWdiget : public QWidget
{
    Q_OBJECT

public:
    SampleEditorWdiget(QEXTMvvmModel* model, QWidget* parent = nullptr);
    ~SampleEditorWdiget();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    QEXTMvvmItem* item_from_view(QTreeView* view, const QPoint& point);

    QBoxLayout* createLeftLayout();
    QBoxLayout* createMiddleLayout();
    QBoxLayout* createRightLayout();

    void connect_views();

    QUndoView* m_undoView{nullptr};
    QEXTMvvmAllItemsTreeView* m_defaultTreeView{nullptr};
    QEXTMvvmTopItemsTreeView* m_topItemView{nullptr};
    QEXTMvvmAllItemsTreeView* m_subsetTreeView{nullptr};
    QEXTMvvmPropertyTreeView* m_propertyTreeView{nullptr};
    QEXTMvvmModel* m_sessionModel{nullptr};
};

} // namespace TreeViews

#endif // SAMPLEEDITORWIDGET_H
