#ifndef _QEXTMVVMDEFAULTEDITORFACTORY_H
#define _QEXTMVVMDEFAULTEDITORFACTORY_H

#include <qextMvvmGlobal.h>
#include <qextMvvmEditorBuilders.h>
#include <qextMvvmEditorFactoryInterface.h>

#include <cfUniquePointer.h>

#include <QModelIndex>

#include <map>
#include <string>

CF_USE_NAMESPACE

//! Abstract editor factory for ViewModelDelegate.
//! Creates cell editors for Qt trees and tables from model index. Cell editor is
//! Qt widget intended for editing DATA role of some SessionItem.
class QEXT_MVVM_API QEXTMvvmAbstractEditorFactory : public QEXTMvvmEditorFactoryInterface
{
protected:
    void registerBuilder(const std::string &name, QEXTMvvmEditorBuilders::Builder builder);
    QEXTMvvmEditorBuilders::Builder findBuilder(const std::string &name) const;

    std::map<std::string, QEXTMvvmEditorBuilders::Builder> m_nameToBuilderMap;
};

//! Editor factory for cell editors in Qt trees and tables, relies on EDITORTYPE role stored
//! on board of SessionItem.

class QEXT_MVVM_API QEXTMvvmRoleDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmRoleDependentEditorFactory();

    CFUniquePointer<QEXTMvvmCustomEditor> createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

protected:
    CFUniquePointer<QEXTMvvmCustomEditor> createItemEditor(const CFMvvmItem *item) const;
};

//! Editor factory for cell editors in Qt trees and tables, relies on variant type stored as
//! DATA role on board of SessionItem.

class QEXT_MVVM_API QEXTMvvmVariantDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmVariantDependentEditorFactory();

    CFUniquePointer<QEXTMvvmCustomEditor> createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;
};

//! Default editor factory for cell editors in Qt trees and tables.
//! Internaly it uses two factories

class QEXT_MVVM_API QEXTMvvmDefaultEditorFactory : public QEXTMvvmEditorFactoryInterface
{
public:
    QEXTMvvmDefaultEditorFactory();

    CFUniquePointer<QEXTMvvmCustomEditor> createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

private:
    CFUniquePointer<QEXTMvvmRoleDependentEditorFactory> m_roleDependentFactory;
    CFUniquePointer<QEXTMvvmVariantDependentEditorFactory> m_variantDependentFactory;
};

#endif // _QEXTMVVMDEFAULTEDITORFACTORY_H
