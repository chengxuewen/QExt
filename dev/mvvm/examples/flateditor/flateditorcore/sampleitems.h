// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_SAMPLEITEMS_H
#define FLATEDITORCORE_SAMPLEITEMS_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmGroupItem.h>
#include <string>

namespace FlatEditor {

//! Item to represent x-ray or neutron beam with properties to setup.

class BeamItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_BEAM_TYPE = "P_BEAM_TYPE";
    static constexpr const char *P_IS_POLARIZED = "P_IS_POLARIZED";
    static constexpr const char *P_WAVELENGTH = "P_WAVELENGTH";
    static constexpr const char *P_ANGULAR_DISTRIBUTION = "P_ANGULAR_DISTRIBUTION";
    static constexpr const char *P_ACCESS_LIGHT_BULB_COLOR = "P_COLOR";

    BeamItem();

    void activate() override;

private:
    void update_appearance();
};

//! Item to represent fixed value.

class DistributionNoneItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_MEAN = "P_MEAN";

    DistributionNoneItem();
};

//! Item to represent gaussian distribution.

class DistributionGaussianItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_MEAN = "P_MEAN";
    static constexpr const char *P_STD_DEV = "P_STD_DEV";

    DistributionGaussianItem();
};

//! Item to represent log normal distribution.

class DistributionLogNormalItem : public ModelView::QExtMvvmCompoundItem {

public:
    static constexpr const char *P_MEDIAN = "P_MEDIAN";
    static constexpr const char *P_SCALE_PAR = "P_SCALE_PAR";

    DistributionLogNormalItem();
};

//! Item to represent trapezoid distribution.

class DistributionTrapezoidItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_CENTER = "P_CENTER";
    static constexpr const char *P_LEFTWIDTH = "P_LEFTWIDTH";
    static constexpr const char *P_MIDDLEWIDTH = "P_MIDDLEWIDTH";
    static constexpr const char *P_RIGHTWIDTH = "P_RIGHTWIDTH";

    DistributionTrapezoidItem();
};

//! Group to hold probability distribution items.

class DistributionGroupItem : public ModelView::QExtMvvmGroupItem {
public:
    DistributionGroupItem();
};

} // namespace FlatEditor

#endif // FLATEDITORCORE_SAMPLEITEMS_H
