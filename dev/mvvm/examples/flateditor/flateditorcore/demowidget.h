// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_DEMOWIDGET_H
#define FLATEDITORCORE_DEMOWIDGET_H

#include <QWidget>
#include <memory>

class QBoxLayout;

namespace ModelView {
class QExtMvvmSessionModel;
class AllItemsTreeView;
class QExtMvvmPropertyTreeView;
class QExtMvvmPropertyFlatView;
} // namespace ModelView

namespace FlatEditor {

//! Demonstrates usage of QExtMvvmPropertyFlatView.

class DemoWidget : public QWidget {
    Q_OBJECT

public:
    DemoWidget(ModelView::QExtMvvmSessionModel* model, QWidget* parent = nullptr);
    ~DemoWidget();

private:
    QBoxLayout* createLeftLayout();
    QBoxLayout* createRightLayout();

    void connectViews();

    ModelView::AllItemsTreeView* m_default_tree_view{nullptr};
    ModelView::QExtMvvmPropertyTreeView* m_property_tree_view{nullptr};
    ModelView::QExtMvvmPropertyFlatView* m_property_flat_view{nullptr};
    ModelView::QExtMvvmSessionModel* m_sessio_model{nullptr};
};

} // namespace FlatEditor

#endif // FLATEDITORCORE_DEMOWIDGET_H
