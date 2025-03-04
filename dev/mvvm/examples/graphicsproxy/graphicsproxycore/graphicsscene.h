// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_GRAPHICSSCENE_H
#define GRAPHICSPROXYCORE_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <qextMemory.h>

namespace ModelView {
class QExtMvvmColorMapCanvas;
class QExtMvvmSceneAdapterInterface;
class QExtMvvmCustomPlotProxyWidget;
} // namespace ModelView

namespace GraphicsProxy {

class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent);
    ~GraphicsScene() override;

    void setContext(ModelView::QExtMvvmColorMapCanvas* colormap, RegionOfInterestItem* roi);

    void update_size(const QSize& newSize);

private:
    void create_colormap_proxy(ModelView::QExtMvvmColorMapCanvas* colormap);
    void create_roi_view(RegionOfInterestItem* roi_item);

    ModelView::QExtMvvmCustomPlotProxyWidget* m_colormapProxy{nullptr};
    QExtUniquePointer<ModelView::QExtMvvmSceneAdapterInterface> m_sceneAdapter;
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_GRAPHICSSCENE_H
