// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmModel.h>
#include <QVector>

class QColor;


class QEXTMvvmExternalProperty;


//! Represents material based on scattering length density.

class SLDMaterialItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_NAME = "P_NAME";
    static inline const QString P_COLOR = "P_COLOR";
    static inline const QString P_SLD_REAL = "P_SLD_REAL";
    static inline const QString P_SLD_IMAG = "P_SLD_IMAG";

    SLDMaterialItem();

    void set_properties(const QString& name, const QColor& color, double real, double imag);
};

//! Model to hold MaterialItems.

class MaterialModel : public QEXTMvvmModel
{
public:
    MaterialModel();

    static QEXTMvvmExternalProperty undefined_material();

    QVector<QEXTMvvmExternalProperty> material_data();

    QEXTMvvmExternalProperty material_property(const QString& id);

private:
    void init_model();
};

#endif //  MATERIALMODEL_H
