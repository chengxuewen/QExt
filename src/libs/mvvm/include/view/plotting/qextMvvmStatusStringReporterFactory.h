#ifndef _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTERFACTORY_H
#define _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTERFACTORY_H

//! Contains factory methods to create StatusStringReporter

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmStatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmStatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmStatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGSTATUSSTRINGREPORTERFACTORY_H
