// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/editors/defaulteditorfactory.h"
#include "viewmodel/editors/customeditor.h"
#include "viewmodel/editors/editor_constants.h"
#include "model/model/customvariants.h"
#include "model/model/sessionitem.h"
#include "model/model/variant_constants.h"
#include "viewmodel/viewmodel/viewmodel.h"

using namespace ModelView;

namespace {

const QExtMvvmSessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const QExtMvvmViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

} // namespace

// ----------------------------------------------------------------------------

void QExtMvvmAbstractEditorFactory::registerBuilder(const std::string& name,
                                            EditorBuilders::builder_t builder)
{
    m_nameToBuilderMap[name] = std::move(builder);
}

EditorBuilders::builder_t QExtMvvmAbstractEditorFactory::findBuilder(const std::string& name) const
{
    auto it = m_nameToBuilderMap.find(name);
    return it != m_nameToBuilderMap.end() ? it->second : EditorBuilders::builder_t();
}

// ----------------------------------------------------------------------------

QExtMvvmRoleDependentEditorFactory::QExtMvvmRoleDependentEditorFactory()
{
    // registering set of builders for given editor types
    registerBuilder(Constants::BoolEditorType, EditorBuilders::BoolEditorBuilder());
    registerBuilder(Constants::ColorEditorType, EditorBuilders::ColorEditorBuilder());
    registerBuilder(Constants::ComboPropertyEditorType,
                    EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(Constants::DoubleEditorType, EditorBuilders::DoubleEditorBuilder());
    registerBuilder(Constants::ExternalPropertyEditorType,
                    EditorBuilders::ExternalPropertyEditorBuilder());
    registerBuilder(Constants::IntegerEditorType, EditorBuilders::IntegerEditorBuilder());
    registerBuilder(Constants::ScientficDoubleEditorType,
                    EditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilder(Constants::ScientficSpinBoxEditorType,
                    EditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilder(Constants::SelectableComboPropertyEditorType,
                    EditorBuilders::SelectableComboPropertyEditorBuilder());
}

//! Creates cell editor basing on item role. It is expected that the index belongs to a QExtMvvmViewModel.

QExtUniquePointer<QExtMvvmCustomEditor>
QExtMvvmRoleDependentEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    return item ? createItemEditor(item) : QExtUniquePointer<QExtMvvmCustomEditor>();
}

//! Creates cell editor basing on editor type.

QExtUniquePointer<QExtMvvmCustomEditor>
QExtMvvmRoleDependentEditorFactory::createItemEditor(const QExtMvvmSessionItem* item) const
{
    auto builder = findBuilder(item->editorType());
    return builder ? builder(item) : QExtUniquePointer<QExtMvvmCustomEditor>();
}

// ----------------------------------------------------------------------------

QExtMvvmVariantDependentEditorFactory::QExtMvvmVariantDependentEditorFactory()
{
    // registering set of builders for given variant names
    registerBuilder(Constants::bool_type_name, EditorBuilders::BoolEditorBuilder());
    registerBuilder(Constants::int_type_name, EditorBuilders::IntegerEditorBuilder());
    registerBuilder(Constants::double_type_name, EditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilder(Constants::qcolor_type_name, EditorBuilders::ColorEditorBuilder());
    registerBuilder(Constants::comboproperty_type_name,
                    EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(Constants::extproperty_type_name,
                    EditorBuilders::ExternalPropertyEditorBuilder());
}

//! Creates cell editor basing on variant name.

QExtUniquePointer<QExtMvvmCustomEditor>
QExtMvvmVariantDependentEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    auto value = item ? item->data<QVariant>() : index.data(Qt::EditRole);
    auto builder = findBuilder(Utils::VariantName(value));
    return builder ? builder(item) : QExtUniquePointer<QExtMvvmCustomEditor>();
}

// ----------------------------------------------------------------------------

QExtMvvmDefaultEditorFactory::QExtMvvmDefaultEditorFactory()
    : m_roleDependentFactory(qextMakeUnique<QExtMvvmRoleDependentEditorFactory>())
    , m_variantDependentFactory(qextMakeUnique<QExtMvvmVariantDependentEditorFactory>())
{
}

//! Creates editor for given model index basing either on editorType() or specific variant name.

QExtUniquePointer<QExtMvvmCustomEditor> QExtMvvmDefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    // trying to created an editor basing on possibly defined EDITOR role
    auto editor = m_roleDependentFactory->createEditor(index);
    // if we do not succeed, then creating editor from variant type
    return editor ? std::move(editor) : m_variantDependentFactory->createEditor(index);
}
