#include <qextMvvmComboProperty.h>
#include <qextMvvmColorMapPlotController.h>
#include <qextMvvmData2dPlotController.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmData2dItem.h>

#include "qcustomplot.h"

#include <QMap>

namespace
{
using gradient_map_t = QMap<QString, QCPColorGradient::GradientPreset>;
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

QCPColorGradient getGradient(const QString& gradientName)
{
    static gradient_map_t gradient_map = createGradientMap();
    return gradient_map.contains(gradientName) ? QCPColorGradient(gradient_map.value(gradientName)) : QCPColorGradient::gpSpectrum;
}

} // namespace



struct QEXTMvvmColorMapPlotController::ColorMapPlotControllerImpl {
    QEXTMvvmColorMapPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    QCPColorMap* color_map{nullptr};
    QScopedPointer<QEXTMvvmData2DPlotController> data_controller;

    ColorMapPlotControllerImpl(QEXTMvvmColorMapPlotController* master, QCustomPlot* plot,
                               QCPColorScale* color_scale)
        : master(master), custom_plot(plot)
    {
        color_map = new QCPColorMap(custom_plot->xAxis, custom_plot->yAxis);
        data_controller.reset(new QEXTMvvmData2DPlotController(color_map));

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

    //! Updates QCPColorMap's interpolation when corresponding property of QEXTMvvmColorMapItem changed.

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
    : p_impl(new ColorMapPlotControllerImpl(this, custom_plot, color_scale))
{
}

QEXTMvvmColorMapPlotController::~QEXTMvvmColorMapPlotController()
{

}

void QEXTMvvmColorMapPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmItem*, QString property_name) {
        if (property_name == QEXTMvvmColorMapItem::P_INTERPOLATION)
            p_impl->update_interpolation();

        if (property_name == QEXTMvvmColorMapItem::P_GRADIENT)
            p_impl->update_gradient();

        if (property_name == QEXTMvvmColorMapItem::P_LINK)
            p_impl->update_data_controller();

        p_impl->custom_plot->replot();
    };
    this->addItemPropertyChangedListener(on_property_change);

    p_impl->update_colormap();
}

void QEXTMvvmColorMapPlotController::unsubscribe()
{
    p_impl->data_controller->setItem(nullptr);
}
