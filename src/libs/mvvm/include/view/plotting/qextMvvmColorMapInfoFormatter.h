#ifndef _QEXTMVVMPLOTTINGCOLORMAPINFOFORMATTER_H
#define _QEXTMVVMPLOTTINGCOLORMAPINFOFORMATTER_H

#include <qextMvvmStatusStringFormatterInterface.h>

class QCustomPlot;

namespace ModelView
{

//! Formats status string for current mouse position in QCPColorMap.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add bins info for
//! QCPColorMap beneath.

class QEXT_MVVM_API QEXTMvvmColorMapInfoFormatter : public QEXTMvvmStatusStringFormatterInterface
{
public:
    //! Returns status string representing data in color map.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCOLORMAPINFOFORMATTER_H
