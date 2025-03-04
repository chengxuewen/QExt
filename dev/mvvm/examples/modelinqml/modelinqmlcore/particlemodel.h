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

#include "model/model/compounditem.h"
#include "model/model/groupitem.h"
#include "model/model/sessionmodel.h"

//! @file particlemodel.h
//! Collection of items and their model representing Particle.

//! A particle with position and shape group.

class ParticleItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static inline const std::string P_POSITION = "Position";
    static inline const std::string P_SHAPES = "Shapes";
    ParticleItem();
};

//! Simple cylinder with radius and height.

class CylinderItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    static inline const std::string P_HEIGHT = "Height";
    CylinderItem();
};

//! Simple spherer with radius.

class SphereItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    SphereItem();
};

//! Pyramid with 4 parameters.

class AnysoPyramidItem : public ModelView::QExtMvvmCompoundItem
{
public:
    static inline const std::string P_LENGTH = "Length";
    static inline const std::string P_WIDTH = "Width";
    static inline const std::string P_HEIGHT = "Height";
    static inline const std::string P_ALPHA = "Alpha";
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
