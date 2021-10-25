#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmEditorBuilders.h>
#include <qextMvvmConstants.h>

#include <cfMvvmItem.h>

#include <string>

const CFMvvmItem *qextMvvmItemFromIndex(const QModelIndex &index)
{
    const QEXTMvvmViewModel *model = dynamic_cast<const QEXTMvvmViewModel *>(index.model());
    return model ? model->itemFromIndex(index) : QEXT_DECL_NULLPTR;
}

void QEXTMvvmAbstractEditorFactory::registerBuilder(const std::string &name, QEXTMvvmEditorBuilders::Builder builder)
{
    m_nameToBuilderMap[name] = builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmAbstractEditorFactory::findBuilder(const std::string &name) const
{
    std::map<std::string, QEXTMvvmEditorBuilders::Builder>::const_iterator iter = m_nameToBuilderMap.find(name);
    return m_nameToBuilderMap.end() != iter ? iter->second : QEXTMvvmEditorBuilders::Builder();
}

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

//! Creates cell editor basing on item role. It is expected that the index belongs to a ViewModel.
CFUniquePointer<QEXTMvvmCustomEditor> QEXTMvvmRoleDependentEditorFactory::createEditor(const QModelIndex &index) const
{
    const CFMvvmItem *item = qextMvvmItemFromIndex(index);
    return item ? this->createItemEditor(item) : CFUniquePointer<QEXTMvvmCustomEditor>();
}

//! Creates cell editor basing on editor type.
CFUniquePointer<QEXTMvvmCustomEditor> QEXTMvvmRoleDependentEditorFactory::createItemEditor(const CFMvvmItem *item) const
{
    QEXTMvvmEditorBuilders::Builder builder = this->findBuilder(item->editorType());
//    return builder ? builder(const_cast<CFMvvmItem *>(item)) : CFUniquePointer<QEXTMvvmCustomEditor>();
}

QEXTMvvmVariantDependentEditorFactory::QEXTMvvmVariantDependentEditorFactory()
{
    // registering set of builders for given variant names
    this->registerBuilder(QEXTMvvmConstants::bool_type_name, QEXTMvvmEditorBuilders::boolEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::int_type_name, QEXTMvvmEditorBuilders::integerEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::double_type_name, QEXTMvvmEditorBuilders::scientificSpinBoxEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::qcolor_type_name, QEXTMvvmEditorBuilders::colorEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::comboproperty_type_name, QEXTMvvmEditorBuilders::comboPropertyEditorBuilder());
    this->registerBuilder(QEXTMvvmConstants::extproperty_type_name, QEXTMvvmEditorBuilders::externalPropertyEditorBuilder());
}

CFUniquePointer<QEXTMvvmCustomEditor> QEXTMvvmVariantDependentEditorFactory::createEditor(const QModelIndex &index) const
{
    const CFMvvmItem *item = qextMvvmItemFromIndex(index);
    QVariant value = item ? item->data<QVariant>() : index.data(Qt::EditRole);
    std::string variantName = value.isValid() ? value.typeName() : QEXTMvvmConstants::invalid_type_name;
    QEXTMvvmEditorBuilders::Builder builder = this->findBuilder(variantName);
//    return builder ? builder(const_cast<CFMvvmItem *>(item)) : CFUniquePointer<QEXTMvvmCustomEditor>();
}

//! Creates cell editor basing on variant name.
QEXTMvvmDefaultEditorFactory::QEXTMvvmDefaultEditorFactory()
    : m_roleDependentFactory(new QEXTMvvmRoleDependentEditorFactory)
    , m_variantDependentFactory(new QEXTMvvmVariantDependentEditorFactory)
{

}

//! Creates editor for given model index basing either on editorType() or specific variant name.
CFUniquePointer<QEXTMvvmCustomEditor> QEXTMvvmDefaultEditorFactory::createEditor(const QModelIndex &index) const
{
    // trying to created an editor basing on possibly defined EDITOR role
    CFUniquePointer<QEXTMvvmCustomEditor> editor = m_roleDependentFactory->createEditor(index);
    // if we do not succeed, then creating editor from variant type
    return !editor.isNull() ? editor : m_variantDependentFactory->createEditor(index);
}
