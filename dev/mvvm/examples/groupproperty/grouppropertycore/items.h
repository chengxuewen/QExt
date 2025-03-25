// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GROUPPROPERTYCORE_ITEMS_H
#define GROUPPROPERTYCORE_ITEMS_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmSessionModel.h>

namespace GroupProperty {

//! Represents undefined shape.

class UndefinedShapeItem : public ModelView::QExtMvvmCompoundItem {
public:
    UndefinedShapeItem();
};

//! Represents a shpere.

class SphereItem : public ModelView::QExtMvvmCompoundItem {
public:
    SphereItem();
};

//! Represents a cylindrical shape.

class CylinderItem : public ModelView::QExtMvvmCompoundItem {
public:
    CylinderItem();
};

//! Represents a box.

class BoxItem : public ModelView::QExtMvvmCompoundItem {
public:
    BoxItem();
};

//! Represents a group of possible shapes.

class ShapeGroupItem : public ModelView::QExtMvvmGroupItem {
public:
    ShapeGroupItem();
};

//! Represents a particle. Particle has a color, position, and a selection of possible shapes.

class ParticleItem : public ModelView::QExtMvvmCompoundItem {
public:
    ParticleItem();
};

//! Main model of the application.

class Model : public ModelView::QExtMvvmSessionModel {
public:
    Model();
};

} // namespace GroupProperty

#endif // GROUPPROPERTYCORE_ITEMS_H
