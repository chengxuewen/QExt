// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sceneitems.h"
#include <utils/qextMvvmRealLimits.h>

namespace
{
const std::string RegionOfInterestItemType = "RegionOfInterest";
}

using namespace ModelView;

RegionOfInterestItem::RegionOfInterestItem() : QEXTMvvmCompoundItem(RegionOfInterestItemType)
{
    addProperty(P_XLOW, 0.0)->setDisplayName("Xlow")->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_YLOW, 0.0)->setDisplayName("Ylow")->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_XUP, 0.0)->setDisplayName("Xup")->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_YUP, 0.0)->setDisplayName("Yup")->setLimits(QEXTMvvmRealLimits::limitless());
}
