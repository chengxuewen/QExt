#ifndef _QEXTMVVMEDITORSDEFAULTEDITORFACTORY_H
#define _QEXTMVVMEDITORSDEFAULTEDITORFACTORY_H

//! @file defaulteditorfactory.h
//! Defines DefaultEditorFactory and auxiliary classes for custom view model delegates.

#include <qextMvvmEditorBuilders.h>
#include <qextMvvmEditorFactoryInterface.h>
#include <qextMvvmGlobal.h>

#include <map>
#include <memory>

namespace ModelView
{

//! Abstract editor factory for ViewModelDelegate.
//! Creates cell editors for Qt trees and tables from model index. Cell editor is
//! Qt widget intended for editing DATA role of some QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmAbstractEditorFactory : public QEXTMvvmEditorFactoryInterface
{
protected:
    void registerBuilder(const std::string& name, QEXTMvvmEditorBuilders::builder_t builder);
    QEXTMvvmEditorBuilders::builder_t findBuilder(const std::string& name) const;

    std::map<std::string, QEXTMvvmEditorBuilders::builder_t> m_nameToBuilderMap;
};

//! Editor factory for cell editors in Qt trees and tables, relies on EDITORTYPE role stored
//! on board of QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmRoleDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmRoleDependentEditorFactory();

    std::unique_ptr<QEXTMvvmCustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    std::unique_ptr<QEXTMvvmCustomEditor> createItemEditor(const QEXTMvvmSessionItem* item) const;
};

//! Editor factory for cell editors in Qt trees and tables, relies on variant type stored as
//! DATA role on board of QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmVariantDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmVariantDependentEditorFactory();

    std::unique_ptr<QEXTMvvmCustomEditor> createEditor(const QModelIndex& index) const override;
};

//! Default editor factory for cell editors in Qt trees and tables.
//! Internaly it uses two factories

class QEXT_MVVM_API QEXTMvvmDefaultEditorFactory : public QEXTMvvmEditorFactoryInterface
{
public:
    QEXTMvvmDefaultEditorFactory();

    std::unique_ptr<QEXTMvvmCustomEditor> createEditor(const QModelIndex& index) const override;

private:
    std::unique_ptr<QEXTMvvmRoleDependentEditorFactory> m_roleDependentFactory;
    std::unique_ptr<QEXTMvvmVariantDependentEditorFactory> m_variantDependentFactory;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSDEFAULTEDITORFACTORY_H
