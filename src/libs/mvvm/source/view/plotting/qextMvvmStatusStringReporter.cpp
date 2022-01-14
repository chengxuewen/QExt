// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <plotting/qextMvvmMouseMoveReporter.h>
#include <plotting/qextMvvmMousePosInfo.h>
#include <plotting/qextMvvmStatusStringFormatterInterface.h>
#include <plotting/qextMvvmStatusStringReporter.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTMvvmStatusStringReporter::StatusStringReporterImpl {
    QEXTMvvmStatusStringReporter* parent{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    std::unique_ptr<QEXTMvvmStatusStringFormatterInterface> fmt;
    std::unique_ptr<QEXTMvvmMouseMoveReporter> mouse_reporter;
    QEXTMvvmMousePosInfo prevPos;

    StatusStringReporterImpl(QEXTMvvmStatusStringReporter* parent, QCustomPlot* custom_plot,
                             callback_t callback,
                             std::unique_ptr<QEXTMvvmStatusStringFormatterInterface> formatter)
        : parent(parent)
        , custom_plot(custom_plot)
        , callback(std::move(callback))
        , fmt(std::move(formatter))
    {
        if (!custom_plot)
            throw std::runtime_error("StatusStringReporter: not initialized custom plot.");

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
        mouse_reporter = make_unique<QEXTMvvmMouseMoveReporter>(custom_plot, on_mouse_move);
    }

    //! Notify client about mouse move with formatted status string.

    void notify_client(const QEXTMvvmMousePosInfo& pos)
    {
        callback(fmt->status_string(this->custom_plot, pos.xpos, pos.ypos));
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

QEXTMvvmStatusStringReporter::QEXTMvvmStatusStringReporter(
    QCustomPlot* custom_plot, callback_t callback,
    std::unique_ptr<QEXTMvvmStatusStringFormatterInterface> formatter)
    : p_impl(make_unique<StatusStringReporterImpl>(this, custom_plot, callback,
                                                        std::move(formatter)))
{
}

QEXTMvvmStatusStringReporter::~QEXTMvvmStatusStringReporter() = default;
