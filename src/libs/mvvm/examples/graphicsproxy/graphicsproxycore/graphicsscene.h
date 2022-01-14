// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_GRAPHICSSCENE_H
#define GRAPHICSPROXY_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <memory>

namespace ModelView
{
class QEXTMvvmColorMapCanvas;
class QEXTMvvmSceneAdapterInterface;
class QEXTMvvmCustomPlotProxyWidget;
} // namespace ModelView

class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent);
    ~GraphicsScene() override;

    void setContext(ModelView::QEXTMvvmColorMapCanvas* colormap, RegionOfInterestItem* roi);

    void update_size(const QSize& newSize);

private:
    void create_colormap_proxy(ModelView::QEXTMvvmColorMapCanvas* colormap);
    void create_roi_view(RegionOfInterestItem* roi_item);

    ModelView::QEXTMvvmCustomPlotProxyWidget* colormap_proxy{nullptr};
    std::unique_ptr<ModelView::QEXTMvvmSceneAdapterInterface> scene_adapter;
};

#endif //  GRAPHICSPROXY_GRAPHICSSCENE_H
