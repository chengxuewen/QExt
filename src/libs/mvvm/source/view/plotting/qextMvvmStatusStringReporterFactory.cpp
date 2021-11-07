#include <qextMvvmColorMapInfoFormatter.h>
#include <qextMvvmGraphInfoFormatter.h>
#include <qextMvvmStatusStringReporter.h>
#include <qextMvvmStatusStringReporterFactory.h>

QEXTMvvmStatusStringReporter *CreateGraphReporter(QCustomPlot* custom_plot, QEXTFunction<void, const QString &> callback)
{
    return new QEXTMvvmStatusStringReporter(custom_plot, callback, new QEXTMvvmGraphInfoFormatter);
}

QEXTMvvmStatusStringReporter *CreateColorMapReporter(QCustomPlot* custom_plot, QEXTFunction<void, const QString &> callback)
{
    return new QEXTMvvmStatusStringReporter(custom_plot, callback, new QEXTMvvmColorMapInfoFormatter);
}

