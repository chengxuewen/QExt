// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_STATUSSTRINGREPORTER_H
#define MVVM_PLOTTING_STATUSSTRINGREPORTER_H

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>
#include <string>

class QCustomPlot;

namespace ModelView {

class QExtMvvmStatusStringFormatterInterface;

//! Reports back status string composed for current mouse position in QCustomPlot.
//! Doesn't report if cursor is outside of the axes range.

class QEXT_MVVM_API QExtMvvmStatusStringReporter {
public:
    using callback_t = std::function<void(const std::string&)>;
    QExtMvvmStatusStringReporter(QCustomPlot* custom_plot, callback_t callback,
                         QExtUniquePointer<QExtMvvmStatusStringFormatterInterface> formatter);
    ~QExtMvvmStatusStringReporter();

private:
    struct StatusStringReporterImpl;
    QExtUniquePointer<StatusStringReporterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_STATUSSTRINGREPORTER_H
