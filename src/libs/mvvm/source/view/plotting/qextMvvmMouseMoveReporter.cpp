// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QMouseEvent>
#include <plotting/qextMvvmMouseMoveReporter.h>
#include <plotting/qextMvvmMousePosInfo.h>
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTMvvmMouseMoveReporter::MouseMoveReporterImpl {
    QEXTMvvmMouseMoveReporter* reporter{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    MouseMoveReporterImpl(QEXTMvvmMouseMoveReporter* reporter, QCustomPlot* custom_plot,
                          callback_t callback)
        : reporter(reporter), custom_plot(custom_plot), callback(std::move(callback))
    {
        if (!custom_plot)
            throw std::runtime_error("MouseMoveReporter: not initialized custom plot.");

        custom_plot->setMouseTracking(true);
        set_connected();
    }

    void set_connected()
    {
        auto on_mouse_move = [this](QMouseEvent* event) {
            double x = pixelToXaxisCoord(event->pos().x());
            double y = pixelToYaxisCoord(event->pos().y());
            if (callback)
            {
                QEXTMvvmMousePosInfo info;
                info.xpos = x;
                info.ypos = y;
                info.in_axes_range = axesRangeContains(x, y);
                callback(info);
            }
        };

        QObject::connect(custom_plot, &QCustomPlot::mouseMove, on_mouse_move);
    }

    double pixelToXaxisCoord(double pixel) const { return custom_plot->xAxis->pixelToCoord(pixel); }

    double pixelToYaxisCoord(double pixel) const { return custom_plot->yAxis->pixelToCoord(pixel); }

    bool axesRangeContains(double xpos, double ypos) const
    {
        return custom_plot->xAxis->range().contains(xpos)
               && custom_plot->yAxis->range().contains(ypos);
    }
};

QEXTMvvmMouseMoveReporter::QEXTMvvmMouseMoveReporter(QCustomPlot* custom_plot, callback_t callback)
    : p_impl(make_unique<MouseMoveReporterImpl>(this, custom_plot, callback))
{
}

QEXTMvvmMouseMoveReporter::~QEXTMvvmMouseMoveReporter() = default;
