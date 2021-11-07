#include <qextMvvmMouseMoveReporter.h>
#include <qextMvvmMousePosInfo.h>
#include <qextMvvmStatusStringFormatterInterface.h>
#include <qextMvvmStatusStringReporter.h>
#include <stdexcept>



struct QEXTMvvmStatusStringReporter::StatusStringReporterImpl {
    QEXTMvvmStatusStringReporter* parent{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    QScopedPointer<QEXTMvvmStatusStringFormatterInterface> fmt;
    QScopedPointer<QEXTMvvmMouseMoveReporter> mouse_reporter;
    QEXTMvvmMousePosInfo prevPos;

    StatusStringReporterImpl(QEXTMvvmStatusStringReporter* parent, QCustomPlot* custom_plot,
                             callback_t callback, QEXTMvvmStatusStringFormatterInterface *formatter)
        : parent(parent)
        , custom_plot(custom_plot)
        , callback(callback)
        , fmt(formatter)
    {
        if (!custom_plot)
            throw std::runtime_error("QEXTMvvmStatusStringReporter: not initialized custom plot.");

        auto on_mouse_move = [this](const QEXTMvvmMousePosInfo& pos) {
            if (pos.in_axes_range) {
                notify_client(pos);
                if (!prevPos.in_axes_range)
                    entering_the_area();
            } else {
                if (prevPos.in_axes_range)
                    leaving_the_area();
            }

            prevPos = pos;
        };
        mouse_reporter.reset(new QEXTMvvmMouseMoveReporter(custom_plot, on_mouse_move));
    }

    //! Notify client about mouse move with formatted status string.

    void notify_client(const QEXTMvvmMousePosInfo& pos)
    {
        callback(fmt->statusString(this->custom_plot, pos.xpos, pos.ypos));
    }

    //! Notify client on leaving axes area.

    void leaving_the_area()
    {
        // notifying client with empty string as a sign that we have left the area
        callback({});
    }

    //! Notify client on entering axes area.

    void entering_the_area()
    {
        // for future improvements
    }
};

QEXTMvvmStatusStringReporter::QEXTMvvmStatusStringReporter(QCustomPlot* custom_plot, callback_t callback,
    QEXTMvvmStatusStringFormatterInterface *formatter)
    : p_impl(new StatusStringReporterImpl(this, custom_plot, callback, formatter))
{
}

QEXTMvvmStatusStringReporter::~QEXTMvvmStatusStringReporter() = default;
