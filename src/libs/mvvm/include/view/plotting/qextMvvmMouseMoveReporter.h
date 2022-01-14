#ifndef _QEXTMVVMPLOTTINGMOUSEMOVEREPORTER_H
#define _QEXTMVVMPLOTTINGMOUSEMOVEREPORTER_H

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView
{

struct QEXTMvvmMousePosInfo;

//! Tracks mouse moves in QCustomPlot canvas.
//! Notifies client about mouse moves and corresponding pointer coordinates expressed in axes units
//! at current zoom level.

class QEXT_MVVM_API QEXTMvvmMouseMoveReporter
{
public:
    using callback_t = std::function<void(const QEXTMvvmMousePosInfo& pos_info)>;
    QEXTMvvmMouseMoveReporter(QCustomPlot* custom_plot, callback_t callback);
    ~QEXTMvvmMouseMoveReporter();

private:
    struct MouseMoveReporterImpl;
    std::unique_ptr<MouseMoveReporterImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGMOUSEMOVEREPORTER_H
