// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <plotting/qextMvvmColorMapInfoFormatter.h>
#include <qextMvvmStringUtils.h>
#include <qcustomplot.h>

#include <sstream>

using namespace ModelView;

namespace
{
QCPColorMap* find_colormap(QCustomPlot* custom_plot)
{
    for (int i = 0; i < custom_plot->plottableCount(); ++i) {
        if (auto plottable = dynamic_cast<QCPColorMap*>(custom_plot->plottable()); plottable)
            return plottable;
    }

    return nullptr;
}

struct Context {
    double xpos{0.0};
    double ypos{0.0};
    int nx{0};
    int ny{0};
    double value{0.0};
};

std::string compose_string(const Context& context)
{
    std::ostringstream ostr;
    ostr << "[x: " << QEXTMvvmUtils::DoubleToString(context.xpos, 3) << ", ";
    ostr << "y: " << QEXTMvvmUtils::DoubleToString(context.ypos, 3) << "] ";
    ostr << "[binx: " << context.nx << ", ";
    ostr << "biny: " << context.ny << "] ";
    ostr << "[value: " << QEXTMvvmUtils::ScientificDoubleToString(context.value) << "]";
    return ostr.str();
}

} // namespace

std::string QEXTMvvmColorMapInfoFormatter::status_string(QCustomPlot* custom_plot, double x, double y) const
{
    // shall we provide caching here?
    auto color_map = find_colormap(custom_plot);
    Context context;
    context.xpos = x;
    context.ypos = y;

    color_map->data()->coordToCell(x, y, &context.nx, &context.ny);
    context.value = color_map->data()->cell(context.nx, context.ny);

    return compose_string(context);
}
