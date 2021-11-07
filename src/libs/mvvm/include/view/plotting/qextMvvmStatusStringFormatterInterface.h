#ifndef _QEXTMVVMSTATUSSTRINGFORMATTERINTERFACE_H
#define _QEXTMVVMSTATUSSTRINGFORMATTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QString>

class QCustomPlot;

//! Pure virtual interface to format string with status info corresponding to the current mouse
//! position on QCustomPlot.

class QEXT_MVVM_API QEXTMvvmStatusStringFormatterInterface
{
public:
    virtual ~QEXTMvvmStatusStringFormatterInterface() { }

    virtual QString statusString(QCustomPlot *customPlot, double x, double y) const = 0;
};

#endif // _QEXTMVVMSTATUSSTRINGFORMATTERINTERFACE_H
