#ifndef _QEXTMVVMCOLORMAPINFOFORMATTER_H
#define _QEXTMVVMCOLORMAPINFOFORMATTER_H

#include <qextMvvmStatusStringFormatterInterface.h>

class QCustomPlot;


//! Formats status string for current mouse position in QCPColorMap.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add bins info for
//! QCPColorMap beneath.

class QEXT_MVVM_API QEXTMvvmColorMapInfoFormatter : public QEXTMvvmStatusStringFormatterInterface
{
public:
    //! Returns status string representing data in color map.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    QString statusString(QCustomPlot* customPlot, double x, double y) const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMCOLORMAPINFOFORMATTER_H
