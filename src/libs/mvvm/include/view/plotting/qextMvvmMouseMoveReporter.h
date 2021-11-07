#ifndef _QEXTMVVMMOUSEMOVEREPORTER_H
#define _QEXTMVVMMOUSEMOVEREPORTER_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCustomPlot;

struct QEXTMvvmMousePosInfo;

//! Tracks mouse moves in QCustomPlot canvas.
//! Notifies client about mouse moves and corresponding pointer coordinates expressed in axes units
//! at current zoom level.

class QEXT_MVVM_API QEXTMvvmMouseMoveReporter
{
public:
    typedef QEXTFunction<void, const QEXTMvvmMousePosInfo &> callback_t;
    QEXTMvvmMouseMoveReporter(QCustomPlot* custom_plot, callback_t callback);
    ~QEXTMvvmMouseMoveReporter();

private:
    struct MouseMoveReporterImpl;
    QScopedPointer<MouseMoveReporterImpl> p_impl;
};

#endif // _QEXTMVVMMOUSEMOVEREPORTER_H
