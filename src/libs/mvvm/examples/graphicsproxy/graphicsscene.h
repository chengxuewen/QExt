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

#include <qextGlobal.h>

#include <QGraphicsScene>
#include <QScopedPointer>



class QEXTMvvmColorMapCanvas;
class QEXTMvvmSceneAdapterInterface;
class QEXTMvvmCustomPlotProxyWidget;


class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject* parent);
    ~GraphicsScene() QEXT_DECL_OVERRIDE;

    void setContext(QEXTMvvmColorMapCanvas* colormap, RegionOfInterestItem* roi);

    void update_size(const QSize& newSize);

private:
    void create_colormap_proxy(QEXTMvvmColorMapCanvas* colormap);
    void create_roi_view(RegionOfInterestItem* roi_item);

    QEXTMvvmCustomPlotProxyWidget* colormap_proxy{nullptr};
    QScopedPointer<QEXTMvvmSceneAdapterInterface> scene_adapter;
};

#endif //  GRAPHICSPROXY_GRAPHICSSCENE_H
