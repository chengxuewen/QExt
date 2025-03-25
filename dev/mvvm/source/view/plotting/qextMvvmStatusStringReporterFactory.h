// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
#define MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H

//! Contains factory methods to create QExtMvvmStatusStringReporter

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView {

class QExtMvvmStatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmStatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmStatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

} // namespace ModelView

#endif // MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
