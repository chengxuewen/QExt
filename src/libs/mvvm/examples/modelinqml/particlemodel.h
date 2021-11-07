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
#include <qextMvvmModel.h>

//! @file particlemodel.h
//! Collection of items and their model representing Particle.

//! A particle with position and shape group.

class ParticleItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_POSITION = "Position";
    static inline const QString P_SHAPES = "Shapes";
    ParticleItem();
};

//! Simple cylinder with radius and height.

class CylinderItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_RADIUS = "Radius";
    static inline const QString P_HEIGHT = "Height";
    CylinderItem();
};

//! Simple spherer with radius.

class SphereItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_RADIUS = "Radius";
    SphereItem();
};

//! Pyramid with 4 parameters.

class AnysoPyramidItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_LENGTH = "Length";
    static inline const QString P_WIDTH = "Width";
    static inline const QString P_HEIGHT = "Height";
    static inline const QString P_ALPHA = "Alpha";
    AnysoPyramidItem();
};

//! Special group of shapes.

class ShapeGroupItem : public QEXTMvvmGroupItem
{
public:
    ShapeGroupItem();
};

//! Main application model.

class ParticleModel : public QEXTMvvmModel
{
public:
    ParticleModel();
};

#endif // MODELINQMLCORE_PARTICLEMODEL_H
