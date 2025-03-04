// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_DEFAULTEDITORFACTORY_H
#define MVVM_EDITORS_DEFAULTEDITORFACTORY_H

//! @file defaulteditorfactory.h
//! Defines QExtMvvmDefaultEditorFactory and auxiliary classes for custom view model delegates.

#include "viewmodel/editors/editorbuilders.h"
#include "viewmodel/interfaces/editorfactoryinterface.h"
#include <map>
#include <memory>

namespace ModelView {

//! Abstract editor factory for QExtMvvmViewModelDelegate.
//! Creates cell editors for Qt trees and tables from model index. Cell editor is
//! Qt widget intended for editing DATA role of some QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmAbstractEditorFactory : public QExtMvvmEditorFactoryInterface {
protected:
    void registerBuilder(const std::string& name, EditorBuilders::builder_t builder);
    EditorBuilders::builder_t findBuilder(const std::string& name) const;

    std::map<std::string, EditorBuilders::builder_t> m_nameToBuilderMap;
};

//! Editor factory for cell editors in Qt trees and tables, relies on EDITORTYPE role stored
//! on board of QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmRoleDependentEditorFactory : public QExtMvvmAbstractEditorFactory {
public:
    QExtMvvmRoleDependentEditorFactory();

    QExtUniquePointer<QExtMvvmCustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    QExtUniquePointer<QExtMvvmCustomEditor> createItemEditor(const QExtMvvmSessionItem* item) const;
};

//! Editor factory for cell editors in Qt trees and tables, relies on variant type stored as
//! DATA role on board of QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmVariantDependentEditorFactory : public QExtMvvmAbstractEditorFactory {
public:
    QExtMvvmVariantDependentEditorFactory();

    QExtUniquePointer<QExtMvvmCustomEditor> createEditor(const QModelIndex& index) const override;
};

//! Default editor factory for cell editors in Qt trees and tables.
//! Internaly it uses two factories

class QEXT_MVVM_API QExtMvvmDefaultEditorFactory : public QExtMvvmEditorFactoryInterface {
public:
    QExtMvvmDefaultEditorFactory();

    QExtUniquePointer<QExtMvvmCustomEditor> createEditor(const QModelIndex& index) const override;

private:
    QExtUniquePointer<QExtMvvmRoleDependentEditorFactory> m_roleDependentFactory;
    QExtUniquePointer<QExtMvvmVariantDependentEditorFactory> m_variantDependentFactory;
};

} // namespace ModelView

#endif // MVVM_EDITORS_DEFAULTEDITORFACTORY_H
