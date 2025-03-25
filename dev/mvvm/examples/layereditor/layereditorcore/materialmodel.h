// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_MATERIALMODEL_H
#define LAYEREDITORCORE_MATERIALMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>
#include <vector>

class QColor;

namespace ModelView {
class QExtMvvmExternalProperty;
}

//! Represents material based on scattering length density.

class SLDMaterialItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_NAME = "P_NAME";
    static constexpr const char *P_COLOR = "P_COLOR";
    static constexpr const char *P_SLD_REAL = "P_SLD_REAL";
    static constexpr const char *P_SLD_IMAG = "P_SLD_IMAG";

    SLDMaterialItem();

    void set_properties(const std::string& name, const QColor& color, double real, double imag);
};

//! Model to hold MaterialItems.

class MaterialModel : public ModelView::QExtMvvmSessionModel {
public:
    MaterialModel();

    static ModelView::QExtMvvmExternalProperty undefined_material();

    std::vector<ModelView::QExtMvvmExternalProperty> material_data();

    ModelView::QExtMvvmExternalProperty material_property(const std::string& id);

private:
    void populateModel();
};

#endif // LAYEREDITORCORE_MATERIALMODEL_H
