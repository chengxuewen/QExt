// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <plotting/qextMvvmColorMapInfoFormatter.h>
#include <plotting/qextMvvmGraphInfoFormatter.h>
#include <plotting/qextMvvmStatusStringReporter.h>
#include <plotting/qextMvvmStatusStringReporterFactory.h>

namespace ModelView
{

std::unique_ptr<QEXTMvvmStatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return make_unique<QEXTMvvmStatusStringReporter>(custom_plot, callback,
                                                  make_unique<QEXTMvvmGraphInfoFormatter>());
}

std::unique_ptr<QEXTMvvmStatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return make_unique<QEXTMvvmStatusStringReporter>(custom_plot, callback,
                                                  make_unique<QEXTMvvmColorMapInfoFormatter>());
}

} // namespace ModelView
