#include <qextMvvmCustomEditor.h>
#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmConstants.h>
#include <qextMvvmViewModel.h>



namespace
{
    QEXTMvvmItem *qextMvvmItemFromIndex(const QModelIndex &index)
    {
        const QEXTMvvmViewModel *model = dynamic_cast<const QEXTMvvmViewModel *>(index.model());
        return model ? model->itemFromIndex(index) : QEXT_DECL_NULLPTR;
    }
} // namespace

// ----------------------------------------------------------------------------

void QEXTMvvmAbstractEditorFactory::registerBuilder(const QString &name, QEXTMvvmEditorBuilders::EditorBuilder builder)
{
    m_nameToBuilderMap[name] = builder;
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmAbstractEditorFactory::findBuilder(const QString &name) const
{
    return m_nameToBuilderMap.contains(name) ? m_nameToBuilderMap.value(name) : QEXTMvvmEditorBuilders::EditorBuilder();
}

// ----------------------------------------------------------------------------

QEXTMvvmRoleDependentEditorFactory::QEXTMvvmRoleDependentEditorFactory()
{
    // registering set of builders for given editor types
    this->registerBuilder(QEXTMvvmConstants::BoolEditorType, QEXTMvvmEditorBuilders::boolEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::ColorEditorType, QEXTMvvmEditorBuilders::colorEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::ComboPropertyEditorType, QEXTMvvmEditorBuilders::comboPropertyEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::DoubleEditorType, QEXTMvvmEditorBuilders::doubleEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::ExternalPropertyEditorType, QEXTMvvmEditorBuilders::externalPropertyEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::IntegerEditorType, QEXTMvvmEditorBuilders::integerEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::ScientficDoubleEditorType, QEXTMvvmEditorBuilders::scientificDoubleEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::ScientficSpinBoxEditorType, QEXTMvvmEditorBuilders::scientificSpinBoxEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::SelectableComboPropertyEditorType, QEXTMvvmEditorBuilders::selectableComboPropertyEditorBuilder());
}

//! Creates cell editor basing on item role. It is expected that the index belongs to a QEXTMvvmViewModel.

QEXTMvvmCustomEditor *QEXTMvvmRoleDependentEditorFactory::createEditor(const QModelIndex &index) const
{
    QEXTMvvmItem *item = qextMvvmItemFromIndex(index);
    return item ? this->createItemEditor(item) : QEXT_DECL_NULLPTR;
}

//! Creates cell editor basing on editor type.

QEXTMvvmCustomEditor *QEXTMvvmRoleDependentEditorFactory::createItemEditor(const QEXTMvvmItem *item) const
{
    QEXTMvvmEditorBuilders::EditorBuilder builder = this->findBuilder(item->editorType());
    return builder.isValid() ? builder(item) : QEXT_DECL_NULLPTR;
}

// ----------------------------------------------------------------------------

QEXTMvvmVariantDependentEditorFactory::QEXTMvvmVariantDependentEditorFactory()
{
    // registering set of builders for given variant names
    this->registerBuilder(QEXTMvvmConstants::bool_type_name, QEXTMvvmEditorBuilders::boolEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::int_type_name, QEXTMvvmEditorBuilders::integerEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::double_type_name, QEXTMvvmEditorBuilders::scientificSpinBoxEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::color_type_name, QEXTMvvmEditorBuilders::colorEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::comboproperty_type_name, QEXTMvvmEditorBuilders::comboPropertyEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::extproperty_type_name, QEXTMvvmEditorBuilders::externalPropertyEditorBuilder());
}

QEXTMvvmCustomEditor *QEXTMvvmVariantDependentEditorFactory::createEditor(const QModelIndex &index) const
{
    QEXTMvvmItem *item = qextMvvmItemFromIndex(index);
    QVariant value = item ? item->data<QVariant>() : index.data(Qt::EditRole);
    QEXTMvvmEditorBuilders::EditorBuilder builder = this->findBuilder(QEXTMvvmUtils::VariantName(value));
    return builder.isValid() ? builder(item) : QEXT_DECL_NULLPTR;
}



QEXTMvvmDefaultEditorFactory::QEXTMvvmDefaultEditorFactory()
    : m_roleDependentFactory(new QEXTMvvmRoleDependentEditorFactory)
    , m_variantDependentFactory(new QEXTMvvmVariantDependentEditorFactory)
{
}

QEXTMvvmCustomEditor *QEXTMvvmDefaultEditorFactory::createEditor(const QModelIndex &index) const
{
    // trying to created an editor basing on possibly defined EDITOR role
    QEXTMvvmCustomEditor *editor = m_roleDependentFactory->createEditor(index);
    // if we do not succeed, then creating editor from variant type
    return editor ? editor : m_variantDependentFactory->createEditor(index);
}
