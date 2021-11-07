#ifndef _QEXTMVVMSTATUSSTRINGREPORTER_H
#define _QEXTMVVMSTATUSSTRINGREPORTER_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>
#include <QString>

class QCustomPlot;

class QEXTMvvmStatusStringFormatterInterface;

//! Reports back status string composed for current mouse position in QCustomPlot.
//! Doesn't report if cursor is outside of the axes range.

class QEXT_MVVM_API QEXTMvvmStatusStringReporter
{
public:
    typedef QEXTFunction<void, const QString &> callback_t;
    QEXTMvvmStatusStringReporter(QCustomPlot* custom_plot, callback_t callback, QEXTMvvmStatusStringFormatterInterface *formatter);
    ~QEXTMvvmStatusStringReporter();

private:
    struct StatusStringReporterImpl;
    QScopedPointer<StatusStringReporterImpl> p_impl;
};

#endif // _QEXTMVVMSTATUSSTRINGREPORTER_H
