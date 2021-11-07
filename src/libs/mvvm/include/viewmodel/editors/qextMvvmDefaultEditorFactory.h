#ifndef _QEXTMVVMDEFAULTEDITORFACTORY_H
#define _QEXTMVVMDEFAULTEDITORFACTORY_H

#include <qextMvvmEditorBuilders.h>
#include <qextMvvmEditorFactoryInterface.h>

#include <QMap>
#include <QScopedPointer>

//! Abstract editor factory for QEXTMvvmViewModelDelegate.
//! Creates cell editors for Qt trees and tables from model index. Cell editor is
//! Qt widget intended for editing DATA role of some QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmAbstractEditorFactory : public QEXTMvvmEditorFactoryInterface
{
protected:
    void registerBuilder(const QString &name, QEXTMvvmEditorBuilders::EditorBuilder builder);
    QEXTMvvmEditorBuilders::EditorBuilder findBuilder(const QString &name) const;

    QMap<QString, QEXTMvvmEditorBuilders::EditorBuilder> m_nameToBuilderMap;
};

//! Editor factory for cell editors in Qt trees and tables, relies on EDITORTYPE role stored
//! on board of QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmRoleDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmRoleDependentEditorFactory();

    QEXTMvvmCustomEditor *createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

protected:
    QEXTMvvmCustomEditor *createItemEditor(const QEXTMvvmItem *item) const;
};

//! Editor factory for cell editors in Qt trees and tables, relies on variant type stored as
//! DATA role on board of QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmVariantDependentEditorFactory : public QEXTMvvmAbstractEditorFactory
{
public:
    QEXTMvvmVariantDependentEditorFactory();

    QEXTMvvmCustomEditor *createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;
};

//! Default editor factory for cell editors in Qt trees and tables.
//! Internaly it uses two factories

class QEXT_MVVM_API QEXTMvvmDefaultEditorFactory : public QEXTMvvmEditorFactoryInterface
{
public:
    QEXTMvvmDefaultEditorFactory();

    QEXTMvvmCustomEditor *createEditor(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

private:
    QScopedPointer<QEXTMvvmRoleDependentEditorFactory> m_roleDependentFactory;
    QScopedPointer<QEXTMvvmVariantDependentEditorFactory> m_variantDependentFactory;
};

#endif // _QEXTMVVMDEFAULTEDITORFACTORY_H
