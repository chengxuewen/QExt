#ifndef _QEXTMVVMGRAPHINFOFORMATTER_H
#define _QEXTMVVMGRAPHINFOFORMATTER_H

#include <qextMvvmStatusStringFormatterInterface.h>

class QCustomPlot;

//! Formats status string for current mouse position in QCustomPlot with QCPGraph's.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add graph info if there is
//! one nearby.

class QEXT_MVVM_API QEXTMvvmGraphInfoFormatter : public QEXTMvvmStatusStringFormatterInterface
{
public:
    //! Returns status string representing graph nearby.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    QString statusString(QCustomPlot* custom_plot, double x, double y) const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMGRAPHINFOFORMATTER_H
