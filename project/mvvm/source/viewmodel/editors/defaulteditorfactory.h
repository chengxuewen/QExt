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
//! Defines DefaultEditorFactory and auxiliary classes for custom view model delegates.

#include "viewmodel/editors/editorbuilders.h"
#include "viewmodel/interfaces/editorfactoryinterface.h"
#include <map>
#include <memory>

namespace ModelView {

//! Abstract editor factory for ViewModelDelegate.
//! Creates cell editors for Qt trees and tables from model index. Cell editor is
//! Qt widget intended for editing DATA role of some SessionItem.

class QEXT_MVVM_API AbstractEditorFactory : public EditorFactoryInterface {
protected:
    void registerBuilder(const std::string& name, EditorBuilders::builder_t builder);
    EditorBuilders::builder_t findBuilder(const std::string& name) const;

    std::map<std::string, EditorBuilders::builder_t> m_nameToBuilderMap;
};

//! Editor factory for cell editors in Qt trees and tables, relies on EDITORTYPE role stored
//! on board of SessionItem.

class QEXT_MVVM_API RoleDependentEditorFactory : public AbstractEditorFactory {
public:
    RoleDependentEditorFactory();

    QExtUniquePointer<CustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    QExtUniquePointer<CustomEditor> createItemEditor(const SessionItem* item) const;
};

//! Editor factory for cell editors in Qt trees and tables, relies on variant type stored as
//! DATA role on board of SessionItem.

class QEXT_MVVM_API VariantDependentEditorFactory : public AbstractEditorFactory {
public:
    VariantDependentEditorFactory();

    QExtUniquePointer<CustomEditor> createEditor(const QModelIndex& index) const override;
};

//! Default editor factory for cell editors in Qt trees and tables.
//! Internaly it uses two factories

class QEXT_MVVM_API DefaultEditorFactory : public EditorFactoryInterface {
public:
    DefaultEditorFactory();

    QExtUniquePointer<CustomEditor> createEditor(const QModelIndex& index) const override;

private:
    QExtUniquePointer<RoleDependentEditorFactory> m_roleDependentFactory;
    QExtUniquePointer<VariantDependentEditorFactory> m_variantDependentFactory;
};

} // namespace ModelView

#endif // MVVM_EDITORS_DEFAULTEDITORFACTORY_H
