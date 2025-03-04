// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPINFOFORMATTER_H
#define MVVM_PLOTTING_COLORMAPINFOFORMATTER_H

#include "view/plotting/statusstringformatterinterface.h"

class QCustomPlot;

namespace ModelView {

//! Formats status string for current mouse position in QCPColorMap.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add bins info for
//! QCPColorMap beneath.

class QEXT_MVVM_API QExtMvvmColorMapInfoFormatter : public QExtMvvmStatusStringFormatterInterface {
public:
    //! Returns status string representing data in color map.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPINFOFORMATTER_H
