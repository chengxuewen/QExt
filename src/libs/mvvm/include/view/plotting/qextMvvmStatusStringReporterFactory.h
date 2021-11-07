#ifndef _QEXTMVVMSTATUSSTRINGREPORTERFACTORY_H
#define _QEXTMVVMSTATUSSTRINGREPORTERFACTORY_H

//! Contains factory methods to create QEXTMvvmStatusStringReporter

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

class QCustomPlot;

class QEXTMvvmStatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
QEXT_MVVM_API QEXTMvvmStatusStringReporter *CreateGraphReporter(QCustomPlot* custom_plot, QEXTFunction<void, const QString &> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
QEXT_MVVM_API QEXTMvvmStatusStringReporter *CreateColorMapReporter(QCustomPlot* custom_plot, QEXTFunction<void, const QString &> callback);

#endif // _QEXTMVVMSTATUSSTRINGREPORTERFACTORY_H
