// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_SAMPLEWIDGET_H
#define LAYEREDITORCORE_SAMPLEWIDGET_H

#include <QWidget>

class ApplicationModels;
class QBoxLayout;
class MaterialTableWidget;
class MultiLayerTreeView;

namespace ModelView {
class QExtMvvmItemsTreeView;
}

//! Main widget with material and layer editors.

class SampleWidget : public QWidget {
    Q_OBJECT

public:
    SampleWidget(ApplicationModels* models, QWidget* parent = nullptr);

private:
    QBoxLayout* createTopLayout();
    QBoxLayout* createBottomLayout();

    ModelView::QExtMvvmItemsTreeView* m_materialTree{nullptr};
    ModelView::QExtMvvmItemsTreeView* m_sampleTree{nullptr};
    MaterialTableWidget* m_materialTableWidget{nullptr};
    MultiLayerTreeView* m_multiLayerTreeView{nullptr};
    ApplicationModels* m_models{nullptr};
};

#endif // LAYEREDITORCORE_SAMPLEWIDGET_H
