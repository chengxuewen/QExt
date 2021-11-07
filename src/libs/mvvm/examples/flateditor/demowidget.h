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


class QEXTMvvmModel;
class QEXTMvvmAllItemsTreeView;
class QEXTMvvmPropertyTreeView;
class QEXTMvvmPropertyFlatView;


class QBoxLayout;

//! Demonstrates usage of QEXTMvvmPropertyFlatView.

class QEXTMvvmDemoWidget : public QWidget
{
    Q_OBJECT

public:
    QEXTMvvmDemoWidget(QEXTMvvmModel* model, QWidget* parent = nullptr);
    ~QEXTMvvmDemoWidget();

private:
    QBoxLayout* create_left_layout();
    QBoxLayout* create_right_layout();

    void connect_views();

    QEXTMvvmAllItemsTreeView* m_defaultTreeView{nullptr};
    QEXTMvvmPropertyTreeView* m_propertyTreeView{nullptr};
    QEXTMvvmPropertyFlatView* m_propertyFlatView{nullptr};
    QEXTMvvmModel* m_sessionModel{nullptr};
};

#endif // FLATEDITORCORE_DEMOWIDGET_H
