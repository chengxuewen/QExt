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

namespace ModelView
{
class QEXTMvvmSessionModel;
class QEXTMvvmAllItemsTreeView;
class QEXTMvvmPropertyTreeView;
class QEXTMvvmPropertyFlatView;
} // namespace ModelView

class QBoxLayout;

//! Demonstrates usage of PropertyFlatView.

class DemoWidget : public QWidget
{
    Q_OBJECT

public:
    DemoWidget(ModelView::QEXTMvvmSessionModel* model, QWidget* parent = nullptr);
    ~DemoWidget();

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    void connect_views();

    ModelView::QEXTMvvmAllItemsTreeView* m_defaultTreeView{nullptr};
    ModelView::QEXTMvvmPropertyTreeView* m_propertyTreeView{nullptr};
    ModelView::QEXTMvvmPropertyFlatView* m_propertyFlatView{nullptr};
    ModelView::QEXTMvvmSessionModel* m_sessionModel{nullptr};
};

#endif // FLATEDITORCORE_DEMOWIDGET_H
