#include <QMouseEvent>
#include <qextMvvmMouseMoveReporter.h>
#include <qextMvvmMousePosInfo.h>
#include <qcustomplot.h>
#include <stdexcept>



struct QEXTMvvmMouseMoveReporter::MouseMoveReporterImpl {
    QEXTMvvmMouseMoveReporter* reporter{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    MouseMoveReporterImpl(QEXTMvvmMouseMoveReporter* reporter, QCustomPlot* custom_plot,
                          callback_t callback)
        : reporter(reporter), custom_plot(custom_plot), callback(callback)
    {
        if (!custom_plot)
            throw std::runtime_error("QEXTMvvmMouseMoveReporter: not initialized custom plot.");

        custom_plot->setMouseTracking(true);
        set_connected();
    }

    void set_connected()
    {
        auto on_mouse_move = [this](QMouseEvent* event) {
            double x = pixelToXaxisCoord(event->pos().x());
            double y = pixelToYaxisCoord(event->pos().y());
            if (callback.isValid())
                callback({x, y, axesRangeContains(x, y)});
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
    : p_impl(new MouseMoveReporterImpl(this, custom_plot, callback))
{
}

QEXTMvvmMouseMoveReporter::~QEXTMvvmMouseMoveReporter() = default;
