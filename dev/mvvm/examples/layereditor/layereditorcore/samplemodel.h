// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_SAMPLEMODEL_H
#define LAYEREDITORCORE_SAMPLEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>

//! Layer with name, thickness and reference to material.

class LayerItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_NAME = "P_NAME";
    static constexpr const char *P_MATERIAL = "P_MATERIAL";
    static constexpr const char *P_THICKNESS = "P_THICKNESS";
    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class MultiLayerItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *T_LAYERS = "T_LAYERS";
    static constexpr const char *P_NREPETITIONS = "P_NREPETITIONS";
    MultiLayerItem();
};

//! Model to hold layers and multi-layers.

class SampleModel : public ModelView::QExtMvvmSessionModel {
public:
    SampleModel();

private:
    void populateModel();
};

#endif // LAYEREDITORCORE_SAMPLEMODEL_H
