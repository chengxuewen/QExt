// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TREEVIEWSCORE_SAMPLEEDITORWIDGET_H
#define TREEVIEWSCORE_SAMPLEEDITORWIDGET_H

#include <QWidget>

class QTreeView;
class QUndoView;
class QBoxLayout;

namespace ModelView {
class QExtMvvmSessionItem;
class QExtMvvmSessionModel;
class AllItemsTreeView;
class QExtMvvmPropertyTreeView;
class QExtMvvmTopItemsTreeView;
} // namespace ModelView

namespace TreeViews {

//! Collection of tree editors.

class SampleEditorWdiget : public QWidget {
    Q_OBJECT

public:
    SampleEditorWdiget(ModelView::QExtMvvmSessionModel* model, QWidget* parent = nullptr);
    ~SampleEditorWdiget();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    ModelView::QExtMvvmSessionItem* itemFromView(QTreeView* view, const QPoint& point);

    QBoxLayout* createLeftLayout();
    QBoxLayout* createMiddleLayout();
    QBoxLayout* createRightLayout();

    void setupConnections();

    QUndoView* m_undoView{nullptr};
    ModelView::AllItemsTreeView* m_defaultTreeView{nullptr};
    ModelView::QExtMvvmTopItemsTreeView* m_topItemView{nullptr};
    ModelView::AllItemsTreeView* m_subsetTreeView{nullptr};
    ModelView::QExtMvvmPropertyTreeView* m_propertyTreeView{nullptr};
    ModelView::QExtMvvmSessionModel* m_sessionModel{nullptr};
};

} // namespace TreeViews

#endif // TREEVIEWSCORE_SAMPLEEDITORWIDGET_H
