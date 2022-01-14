#ifndef _QEXTMVVMPLOTTINGGRAPHINFOFORMATTER_H
#define _QEXTMVVMPLOTTINGGRAPHINFOFORMATTER_H

#include <qextMvvmStatusStringFormatterInterface.h>

class QCustomPlot;

namespace ModelView
{

//! Formats status string for current mouse position in QCustomPlot with QCPGraph's.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add graph info if there is
//! one nearby.

class QEXT_MVVM_API QEXTMvvmGraphInfoFormatter : public QEXTMvvmStatusStringFormatterInterface
{
public:
    //! Returns status string representing graph nearby.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGGRAPHINFOFORMATTER_H
