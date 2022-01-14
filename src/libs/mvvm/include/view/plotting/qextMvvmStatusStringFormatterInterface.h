#ifndef _QEXTMVVMPLOTTINGSTATUSSTRINGFORMATTERINTERFACE_H
#define _QEXTMVVMPLOTTINGSTATUSSTRINGFORMATTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <string>

class QCustomPlot;

namespace ModelView
{

//! Pure virtual interface to format string with status info corresponding to the current mouse
//! position on QCustomPlot.

class QEXT_MVVM_API QEXTMvvmStatusStringFormatterInterface
{
public:
    virtual ~QEXTMvvmStatusStringFormatterInterface() = default;

    virtual std::string status_string(QCustomPlot* custom_plot, double x, double y) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGSTATUSSTRINGFORMATTERINTERFACE_H
