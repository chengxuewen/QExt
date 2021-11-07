// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmModel.h>

//! Layer with name, thickness and reference to material.

class LayerItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_NAME = "P_NAME";
    static inline const QString P_MATERIAL = "P_MATERIAL";
    static inline const QString P_THICKNESS = "P_THICKNESS";
    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class MultiLayerItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString T_LAYERS = "T_LAYERS";
    static inline const QString P_NREPETITIONS = "P_NREPETITIONS";
    MultiLayerItem();
};

//! Model to hold layers and multi-layers.

class SampleModel : public QEXTMvvmModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif //  SAMPLEMODEL_H
