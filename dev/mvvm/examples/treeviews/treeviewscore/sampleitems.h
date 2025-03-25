// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TREEVIEWSCORE_SAMPLEITEMS_H
#define TREEVIEWSCORE_SAMPLEITEMS_H

//! @file items.h
//! Collection of test items for our sample model.

#include <qextMvvmCompoundItem.h>
#include <qextMvvmGroupItem.h>
#include <string>

namespace TreeViews {

//! A multi layer with possibility to attach layers.

class MultiLayer : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *T_LAYERS = "T_LAYERS";
    MultiLayer();
};

//! A layer with thickness, color property and possibility to attach particles.

class LayerItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_THICKNESS = "Thickness";
    static constexpr const char *P_COLOR = "Color";
    static constexpr const char *T_PARTICLES = "Particles";
    LayerItem();
};

//! A particle with position and shape group.
//! Demonstrates how to create group of properties.

class ParticleItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_POSITION = "Position";
    static constexpr const char *P_SHAPE = "Shape";
    ParticleItem();
};

//! Lattice with bool, double and combo on board.
//! Demonstrates how to syncronize properties between each other.

class LatticeItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_ROTATION_ANLE = "Rotation";
    static constexpr const char *P_INTEGRATION = "Integration";
    static constexpr const char *P_LATTICE_TYPE = "Type";

    LatticeItem();

    void activate() override;

private:
    void update_appearance();
};

//! Simple cylinder with radius and height.

class CylinderItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_RADIUS = "Radius";
    static constexpr const char *P_HEIGHT = "Height";
    CylinderItem();
};

//! Simple spherer with radius.

class SphereItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_RADIUS = "Radius";
    SphereItem();
};

//! Pyramid with 4 parameters.

class AnysoPyramidItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_LENGTH = "Length";
    static constexpr const char *P_WIDTH = "Width";
    static constexpr const char *P_HEIGHT = "Height";
    static constexpr const char *P_ALPHA = "Alpha";
    AnysoPyramidItem();
};

//! Special group of shapes.

class ShapeGroupItem : public ModelView::QExtMvvmGroupItem {
public:
    ShapeGroupItem();
};

} // namespace TreeViews

#endif // TREEVIEWSCORE_SAMPLEITEMS_H
