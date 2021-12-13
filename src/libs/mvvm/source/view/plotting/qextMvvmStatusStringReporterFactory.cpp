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

std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<GraphInfoFormatter>());
}

std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<ColorMapInfoFormatter>());
}

} // namespace ModelView
