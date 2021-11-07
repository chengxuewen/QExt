#include "qcustomplot.h"
#include <algorithm>
#include <qextMvvmData2dPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmData2dItem.h>
#include <stdexcept>



namespace
{
//! Returns QCPRange of axis.
QCPRange qcpRange(const QEXTMvvmBinnedAxisItem* axis)
{
    auto centers = axis->binCenters(); // QCPColorMapData expects centers of bin
    return centers.empty() ? QCPRange() : QCPRange(centers.front(), centers.back());
}
} // namespace

struct QEXTMvvmData2DPlotController::QEXTMvvmData2DPlotControllerImpl {
    QEXTMvvmData2DPlotController* master{nullptr};
    QCPColorMap* color_map{nullptr};
    QEXTMvvmData2DPlotControllerImpl(QEXTMvvmData2DPlotController* master, QCPColorMap* color_map)
        : master(master), color_map(color_map)
    {
        if (!color_map)
            throw std::runtime_error("Uninitialised colormap in QEXTMvvmData2DPlotController");
    }

    QEXTMvvmData2DItem* dataItem() { return master->currentItem(); }

    void update_data_points()
    {
        reset_colormap();

        if (auto data_item = dataItem(); data_item) {
            auto xAxis = data_item->xAxis();
            auto yAxis = data_item->yAxis();
            if (xAxis && yAxis) {
                const int nbinsx = xAxis->size();
                const int nbinsy = yAxis->size();

                color_map->data()->setSize(nbinsx, nbinsy);
                color_map->data()->setRange(qcpRange(xAxis), qcpRange(yAxis));

                auto values = data_item->content();
                for (int ix = 0; ix < nbinsx; ++ix)
                    for (int iy = 0; iy < nbinsy; ++iy)
                        color_map->data()->setCell(ix, iy,
                                                   values[static_cast<size_t>(ix + iy * nbinsx)]);

                auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
                color_map->setDataRange(QCPRange(*min, *max));
            }
        }
        color_map->parentPlot()->replot();
    }

    void reset_colormap() { color_map->data()->clear(); }
};

QEXTMvvmData2DPlotController::QEXTMvvmData2DPlotController(QCPColorMap* color_map)
    : p_impl(new QEXTMvvmData2DPlotControllerImpl(this, color_map))
{
}

QEXTMvvmData2DPlotController::~QEXTMvvmData2DPlotController()
{

}

void QEXTMvvmData2DPlotController::subscribe()
{
    auto on_data_change = [this](QEXTMvvmItem*, int) { p_impl->update_data_points(); };
    addItemDataChangedListener(on_data_change);

    p_impl->update_data_points();
}

void QEXTMvvmData2DPlotController::unsubscribe()
{
    p_impl->reset_colormap();
}
