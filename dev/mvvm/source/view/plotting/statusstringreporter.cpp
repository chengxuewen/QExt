// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/plotting/statusstringreporter.h"
#include "view/plotting/mousemovereporter.h"
#include "view/plotting/mouseposinfo.h"
#include "view/plotting/statusstringformatterinterface.h"
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmStatusStringReporter::StatusStringReporterImpl {
    QExtMvvmStatusStringReporter* parent{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    QExtUniquePointer<QExtMvvmStatusStringFormatterInterface> fmt;
    QExtUniquePointer<MouseMoveReporter> mouse_reporter;
    QExtMvvmMousePosInfo prevPos;

    StatusStringReporterImpl(QExtMvvmStatusStringReporter* parent, QCustomPlot* custom_plot,
                             callback_t callback,
                             QExtUniquePointer<QExtMvvmStatusStringFormatterInterface> formatter)
        : parent(parent)
        , custom_plot(custom_plot)
        , callback(std::move(callback))
        , fmt(std::move(formatter))
    {
        if (!custom_plot)
            throw std::runtime_error("QExtMvvmStatusStringReporter: not initialized custom plot.");

        auto on_mouse_move = [this](const QExtMvvmMousePosInfo& pos) {
            if (pos.in_axes_range) {
                notify_client(pos);
                if (!prevPos.in_axes_range)
                    entering_the_area();
            }
            else {
                if (prevPos.in_axes_range)
                    leaving_the_area();
            }

            prevPos = pos;
        };
        mouse_reporter = qextMakeUnique<MouseMoveReporter>(custom_plot, on_mouse_move);
    }

    //! Notify client about mouse move with formatted status string.

    void notify_client(const QExtMvvmMousePosInfo& pos)
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

QExtMvvmStatusStringReporter::QExtMvvmStatusStringReporter(
    QCustomPlot* custom_plot, callback_t callback,
    QExtUniquePointer<QExtMvvmStatusStringFormatterInterface> formatter)
    : p_impl(qextMakeUnique<StatusStringReporterImpl>(this, custom_plot, callback,
                                                        std::move(formatter)))
{
}

QExtMvvmStatusStringReporter::~QExtMvvmStatusStringReporter() = default;
