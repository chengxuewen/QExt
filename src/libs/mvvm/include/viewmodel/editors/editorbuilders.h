// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_EDITORBUILDERS_H
#define MVVM_EDITORS_EDITORBUILDERS_H

#include <functional>
#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class CustomEditor;
class QEXTMvvmSessionItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit QEXTMvvmSessionItem data in the context of DefaultEditorFactory.

namespace EditorBuilders
{

using editor_t = std::unique_ptr<CustomEditor>;
using builder_t = std::function<editor_t(const QEXTMvvmSessionItem*)>;

//! Builder for boolean property editor.
QEXT_MVVM_API builder_t BoolEditorBuilder();

//! Builder for integer property editor.
QEXT_MVVM_API builder_t IntegerEditorBuilder();

//! Builder for double editor with limits support.
QEXT_MVVM_API builder_t DoubleEditorBuilder();

//! Builder for double editor with scientific notation based on simple text field.
QEXT_MVVM_API builder_t ScientificDoubleEditorBuilder();

//! Builder for double editor with scientific notation and spinbox functionality.
QEXT_MVVM_API builder_t ScientificSpinBoxEditorBuilder();

//! Builder for color property editor.
QEXT_MVVM_API builder_t ColorEditorBuilder();

//! Builder for QEXTMvvmComboProperty editor.
QEXT_MVVM_API builder_t ComboPropertyEditorBuilder();

//! Builder for external property editor.
QEXT_MVVM_API builder_t ExternalPropertyEditorBuilder();

//! Builder for QEXTMvvmComboProperty editor with multi-selection functionality.
QEXT_MVVM_API builder_t SelectableComboPropertyEditorBuilder();

} // namespace EditorBuilders

} // namespace ModelView

#endif // MVVM_EDITORS_EDITORBUILDERS_H
