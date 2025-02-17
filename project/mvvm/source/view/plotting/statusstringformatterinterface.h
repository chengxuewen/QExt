// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H
#define MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H

#include "qextMVVMGlobal.h"
#include <string>

class QCustomPlot;

namespace ModelView {

//! Pure virtual interface to format string with status info corresponding to the current mouse
//! position on QCustomPlot.

class QEXT_MVVM_API StatusStringFormatterInterface {
public:
    virtual ~StatusStringFormatterInterface() = default;

    virtual std::string status_string(QCustomPlot* custom_plot, double x, double y) const = 0;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H
