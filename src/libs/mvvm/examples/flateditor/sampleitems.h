// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_ITEMS_H
#define FLATEDITORCORE_ITEMS_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmGroupItem.h>
#include <string>

namespace Constants
{

const QString BeamItemType = "Beam";
const QString DistributionNoneItemType = "DistributionNone";
const QString DistributionGaussianItemType = "DistributionGaussian";
const QString DistributionLogNormalItemType = "DistributionLogNormal";
const QString DistributionTrapezoidItemType = "DistributionTrapezoid";
const QString DistributionGroupItemType = "DistributionGroup";

} // namespace Constants

//! Item to represent x-ray or neutron beam with properties to setup.

class BeamItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_BEAM_TYPE = "P_BEAM_TYPE";
    static inline const QString P_IS_POLARIZED = "P_IS_POLARIZED";
    static inline const QString P_WAVELENGTH = "P_WAVELENGTH";
    static inline const QString P_ANGULAR_DISTRIBUTION = "P_ANGULAR_DISTRIBUTION";
    static inline const QString P_ACCESS_LIGHT_BULB_COLOR = "P_COLOR";
    BeamItem();

    void activate() QEXT_DECL_OVERRIDE;

private:
    void update_appearance();
};

//! Item to represent fixed value.

class DistributionNoneItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_MEAN = "P_MEAN";
    DistributionNoneItem();
};

//! Item to represent gaussian distribution.

class DistributionGaussianItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_MEAN = "P_MEAN";
    static inline const QString P_STD_DEV = "P_STD_DEV";

    DistributionGaussianItem();
};

//! Item to represent log normal distribution.

class DistributionLogNormalItem : public QEXTMvvmCompoundItem
{

public:
    static inline const QString P_MEDIAN = "P_MEDIAN";
    static inline const QString P_SCALE_PAR = "P_SCALE_PAR";

    DistributionLogNormalItem();
};

//! Item to represent trapezoid distribution.

class DistributionTrapezoidItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_CENTER = "P_CENTER";
    static inline const QString P_LEFTWIDTH = "P_LEFTWIDTH";
    static inline const QString P_MIDDLEWIDTH = "P_MIDDLEWIDTH";
    static inline const QString P_RIGHTWIDTH = "P_RIGHTWIDTH";

    DistributionTrapezoidItem();
};

//! Group to hold probability distribution items.

class DistributionGroupItem : public QEXTMvvmGroupItem
{
public:
    DistributionGroupItem();
};

#endif // FLATEDITORCORE_ITEMS_H
