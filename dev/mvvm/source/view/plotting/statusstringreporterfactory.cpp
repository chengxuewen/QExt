// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/plotting/statusstringreporterfactory.h"
#include "view/plotting/colormapinfoformatter.h"
#include "view/plotting/graphinfoformatter.h"
#include "view/plotting/statusstringreporter.h"

namespace ModelView {

QExtUniquePointer<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return qextMakeUnique<StatusStringReporter>(custom_plot, callback,
                                                  qextMakeUnique<GraphInfoFormatter>());
}

QExtUniquePointer<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return qextMakeUnique<StatusStringReporter>(custom_plot, callback,
                                                  qextMakeUnique<ColorMapInfoFormatter>());
}

} // namespace ModelView
