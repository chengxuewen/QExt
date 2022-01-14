#ifndef _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTER_H
#define _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTER_H

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>
#include <string>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmStatusStringFormatterInterface;

//! Reports back status string composed for current mouse position in QCustomPlot.
//! Doesn't report if cursor is outside of the axes range.

class QEXT_MVVM_API QEXTMvvmStatusStringReporter
{
public:
    using callback_t = std::function<void(const std::string&)>;
    QEXTMvvmStatusStringReporter(QCustomPlot* custom_plot, callback_t callback,
                         std::unique_ptr<QEXTMvvmStatusStringFormatterInterface> formatter);
    ~QEXTMvvmStatusStringReporter();

private:
    struct StatusStringReporterImpl;
    std::unique_ptr<StatusStringReporterImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTER_H
