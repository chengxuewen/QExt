#ifndef _QEXTMVVMPLOTTINGMOUSEPOSINFO_H
#define _QEXTMVVMPLOTTINGMOUSEPOSINFO_H

#include <qextMvvmGlobal.h>

class QCustomPlot;

namespace ModelView
{

//! Aggregate to hold mouse position info in QCustomPlot context.
//! Position is given in axis coordinates corresponding to the current zoom level.

struct QEXT_MVVM_API QEXTMvvmMousePosInfo
{
    double xpos{0.0};
    double ypos{0.0};
    bool in_axes_range{false};
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGMOUSEPOSINFO_H
