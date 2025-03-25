// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customeditorfactory.h"
#include "applicationmodels.h"
#include "materialmodel.h"
#include <qextMvvmExternalPropertyComboEditor.h>
#include <qextMvvmExternalProperty.h>
#include <QModelIndex>

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

QExtUniquePointer<QExtMvvmCustomEditor> CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value))
        return qextMakeUnique<QExtMvvmExternalPropertyComboEditor>(
            [this]() { return m_models->materialModel()->material_data(); });
    else
        return QExtMvvmDefaultEditorFactory::createEditor(index);
}
