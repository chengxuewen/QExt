// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomEditor.h>
#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmVariantConstants.h>
#include <viewmodel/qextMvvmViewModel.h>

using namespace ModelView;

namespace
{

const QEXTMvvmSessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const QEXTMvvmViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

} // namespace

// ----------------------------------------------------------------------------

void QEXTMvvmAbstractEditorFactory::registerBuilder(const std::string& name,
                                            QEXTMvvmEditorBuilders::builder_t builder)
{
    m_nameToBuilderMap[name] = std::move(builder);
}

QEXTMvvmEditorBuilders::builder_t QEXTMvvmAbstractEditorFactory::findBuilder(const std::string& name) const
{
    auto it = m_nameToBuilderMap.find(name);
    return it != m_nameToBuilderMap.end() ? it->second : QEXTMvvmEditorBuilders::builder_t();
}

// ----------------------------------------------------------------------------

QEXTMvvmRoleDependentEditorFactory::QEXTMvvmRoleDependentEditorFactory()
{
    // registering set of builders for given editor types
    registerBuilder(QEXTMvvmConstants::BoolEditorType, QEXTMvvmEditorBuilders::BoolEditorBuilder());
    registerBuilder(QEXTMvvmConstants::ColorEditorType, QEXTMvvmEditorBuilders::ColorEditorBuilder());
    registerBuilder(QEXTMvvmConstants::ComboPropertyEditorType,
                    QEXTMvvmEditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(QEXTMvvmConstants::DoubleEditorType, QEXTMvvmEditorBuilders::DoubleEditorBuilder());
    registerBuilder(QEXTMvvmConstants::ExternalPropertyEditorType,
                    QEXTMvvmEditorBuilders::ExternalPropertyEditorBuilder());
    registerBuilder(QEXTMvvmConstants::IntegerEditorType, QEXTMvvmEditorBuilders::IntegerEditorBuilder());
    registerBuilder(QEXTMvvmConstants::ScientficDoubleEditorType,
                    QEXTMvvmEditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilder(QEXTMvvmConstants::ScientficSpinBoxEditorType,
                    QEXTMvvmEditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilder(QEXTMvvmConstants::SelectableComboPropertyEditorType,
                    QEXTMvvmEditorBuilders::SelectableComboPropertyEditorBuilder());
}

//! Creates cell editor basing on item role. It is expected that the index belongs to a ViewModel.

std::unique_ptr<QEXTMvvmCustomEditor>
QEXTMvvmRoleDependentEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    return item ? createItemEditor(item) : std::unique_ptr<QEXTMvvmCustomEditor>();
}

//! Creates cell editor basing on editor type.

std::unique_ptr<QEXTMvvmCustomEditor>
QEXTMvvmRoleDependentEditorFactory::createItemEditor(const QEXTMvvmSessionItem* item) const
{
    auto builder = findBuilder(item->editorType());
    return builder ? builder(item) : std::unique_ptr<QEXTMvvmCustomEditor>();
}

// ----------------------------------------------------------------------------

QEXTMvvmVariantDependentEditorFactory::QEXTMvvmVariantDependentEditorFactory()
{
    // registering set of builders for given variant names
    registerBuilder(QEXTMvvmConstants::bool_type_name, QEXTMvvmEditorBuilders::BoolEditorBuilder());
    registerBuilder(QEXTMvvmConstants::int_type_name, QEXTMvvmEditorBuilders::IntegerEditorBuilder());
    registerBuilder(QEXTMvvmConstants::double_type_name, QEXTMvvmEditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilder(QEXTMvvmConstants::qcolor_type_name, QEXTMvvmEditorBuilders::ColorEditorBuilder());
    registerBuilder(QEXTMvvmConstants::comboproperty_type_name,
                    QEXTMvvmEditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(QEXTMvvmConstants::extproperty_type_name,
                    QEXTMvvmEditorBuilders::ExternalPropertyEditorBuilder());
}

//! Creates cell editor basing on variant name.

std::unique_ptr<QEXTMvvmCustomEditor>
QEXTMvvmVariantDependentEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    auto value = item ? item->data<QVariant>() : index.data(Qt::EditRole);
    auto builder = findBuilder(QEXTMvvmUtils::VariantName(value));
    return builder ? builder(item) : std::unique_ptr<QEXTMvvmCustomEditor>();
}

// ----------------------------------------------------------------------------

QEXTMvvmDefaultEditorFactory::QEXTMvvmDefaultEditorFactory()
    : m_roleDependentFactory(make_unique<QEXTMvvmRoleDependentEditorFactory>())
    , m_variantDependentFactory(make_unique<QEXTMvvmVariantDependentEditorFactory>())
{
}

//! Creates editor for given model index basing either on editorType() or specific variant name.

std::unique_ptr<QEXTMvvmCustomEditor> QEXTMvvmDefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    // trying to created an editor basing on possibly defined EDITOR role
    auto editor = m_roleDependentFactory->createEditor(index);
    // if we do not succeed, then creating editor from variant type
    return editor ? std::move(editor) : m_variantDependentFactory->createEditor(index);
}
