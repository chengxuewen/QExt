// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_CUSTOMEDITORFACTORY_H
#define LAYEREDITORCORE_CUSTOMEDITORFACTORY_H

#include <qextMvvmDefaultEditorFactory.h>

class ApplicationModels;

//! Editor factory with custom editors.
//! Will create custom material selector for all cells containing QExtMvvmExternalProperty.

class CustomEditorFactory : public ModelView::QExtMvvmDefaultEditorFactory {
public:
    CustomEditorFactory(ApplicationModels* models);
    ~CustomEditorFactory();

    QExtUniquePointer<ModelView::QExtMvvmCustomEditor> createEditor(const QModelIndex& index) const;

private:
    ApplicationModels* m_models;
};

#endif // LAYEREDITORCORE_CUSTOMEDITORFACTORY_H
