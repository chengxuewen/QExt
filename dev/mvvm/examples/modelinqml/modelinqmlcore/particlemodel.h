// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_PARTICLEMODEL_H
#define MODELINQMLCORE_PARTICLEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmSessionModel.h>

//! @file particlemodel.h
//! Collection of items and their model representing Particle.

//! A particle with position and shape group.

class ParticleItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static constexpr const char *P_POSITION = "Position";
    static constexpr const char *P_SHAPES = "Shapes";
    ParticleItem();
};

//! Simple cylinder with radius and height.

class CylinderItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static constexpr const char *P_RADIUS = "Radius";
    static constexpr const char *P_HEIGHT = "Height";
    CylinderItem();
};

//! Simple spherer with radius.

class SphereItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static constexpr const char *P_RADIUS = "Radius";
    SphereItem();
};

//! Pyramid with 4 parameters.

class AnysoPyramidItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static constexpr const char *P_LENGTH = "Length";
    static constexpr const char *P_WIDTH = "Width";
    static constexpr const char *P_HEIGHT = "Height";
    static constexpr const char *P_ALPHA = "Alpha";
    AnysoPyramidItem();
};

//! Special group of shapes.

class ShapeGroupItem : public ModelView::QExtMvvmGroupItem
{
public:
    ShapeGroupItem();
};

//! Main application model.

class ParticleModel : public ModelView::QExtMvvmSessionModel
{
public:
    ParticleModel();
};

#endif // MODELINQMLCORE_PARTICLEMODEL_H
