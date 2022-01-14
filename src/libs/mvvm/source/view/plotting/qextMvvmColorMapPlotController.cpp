// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <map>
#include <qextMvvmComboProperty.h>
#include <plotting/qextMvvmColorMapPlotController.h>
#include <plotting/qextMvvmData2DPlotController.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmData2DItem.h>

namespace
{
using gradient_map_t = std::map<std::string, QCPColorGradient::GradientPreset>;
gradient_map_t createGradientMap()
{
    gradient_map_t result;

    result["Grayscale"] = QCPColorGradient::gpGrayscale;
    result["Hot"] = QCPColorGradient::gpHot;
    result["Cold"] = QCPColorGradient::gpCold;
    result["Night"] = QCPColorGradient::gpNight;
    result["Candy"] = QCPColorGradient::gpCandy;
    result["Geography"] = QCPColorGradient::gpGeography;
    result["Ion"] = QCPColorGradient::gpIon;
    result["Thermal"] = QCPColorGradient::gpThermal;
    result["Polar"] = QCPColorGradient::gpPolar;
    result["Spectrum"] = QCPColorGradient::gpSpectrum;
    result["Jet"] = QCPColorGradient::gpJet;
    result["Hues"] = QCPColorGradient::gpHues;

    return result;
}

QCPColorGradient getGradient(const std::string& gradientName)
{
    static gradient_map_t gradient_map = createGradientMap();
    auto it = gradient_map.find(gradientName);
    return it != gradient_map.end() ? QCPColorGradient(it->second) : QCPColorGradient::gpSpectrum;
}

} // namespace

using namespace ModelView;

struct QEXTMvvmColorMapPlotController::ColorMapPlotControllerImpl {
    QEXTMvvmColorMapPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPColorMap* color_map{nullptr};
    std::unique_ptr<QEXTMvvmData2DPlotController> data_controller;

    ColorMapPlotControllerImpl(QEXTMvvmColorMapPlotController* master, QCustomPlot* plot,
                               QCPColorScale* color_scale)
        : master(master), custom_plot(plot)
    {
        color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);
        data_controller = make_unique<QEXTMvvmData2DPlotController>(color_map);

        if (color_scale)
            color_map->setColorScale(color_scale);
    }

    ~ColorMapPlotControllerImpl() { custom_plot->removePlottable(color_map); }

    QEXTMvvmColorMapItem* colormap_item() { return master->currentItem(); }

    void update_colormap()
    {
        update_data_controller();
        update_interpolation();
        update_gradient();
        custom_plot->replot();
    }

    void update_data_controller() { data_controller->setItem(colormap_item()->dataItem()); }

    //! Updates QCPColorMap's interpolation when corresponding property of ColorMapItem changed.

    void update_interpolation()
    {
        auto is_interpolated = colormap_item()->property<bool>(QEXTMvvmColorMapItem::P_INTERPOLATION);
        color_map->setInterpolate(is_interpolated);
    }

    void update_gradient()
    {
        auto combo = colormap_item()->property<QEXTMvvmComboProperty>(QEXTMvvmColorMapItem::P_GRADIENT);
        color_map->setGradient(getGradient(combo.value()));
    }
};

QEXTMvvmColorMapPlotController::QEXTMvvmColorMapPlotController(QCustomPlot* custom_plot, QCPColorScale* color_scale)
    : p_impl(make_unique<ColorMapPlotControllerImpl>(this, custom_plot, color_scale))
{
}

void QEXTMvvmColorMapPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmSessionItem*, std::string property_name) {
        if (property_name == QEXTMvvmColorMapItem::P_INTERPOLATION)
            p_impl->update_interpolation();

        if (property_name == QEXTMvvmColorMapItem::P_GRADIENT)
            p_impl->update_gradient();

        if (property_name == QEXTMvvmColorMapItem::P_LINK)
            p_impl->update_data_controller();

        p_impl->custom_plot->replot();
    };
    setOnPropertyChange(on_property_change);

    p_impl->update_colormap();
}

void QEXTMvvmColorMapPlotController::unsubscribe()
{
    p_impl->data_controller->setItem(nullptr);
}

QEXTMvvmColorMapPlotController::~QEXTMvvmColorMapPlotController() = default;
