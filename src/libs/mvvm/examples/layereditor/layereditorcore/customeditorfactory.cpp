// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QModelIndex>
#include <layereditorcore/applicationmodels.h>
#include <layereditorcore/customeditorfactory.h>
#include <layereditorcore/materialmodel.h>
#include <qextMvvmExternalPropertyComboEditor.h>
#include <qextMvvmExternalProperty.h>

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

std::unique_ptr<QEXTMvvmCustomEditor> CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (QEXTMvvmUtils::IsExtPropertyVariant(value))
        return make_unique<QEXTMvvmExternalPropertyComboEditor>(
            [this]() { return m_models->materialModel()->material_data(); });
    else
        return QEXTMvvmDefaultEditorFactory::createEditor(index);
}
