#ifndef _QEXTMVVMEDITORSEDITORBUILDERS_H
#define _QEXTMVVMEDITORSEDITORBUILDERS_H

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>

namespace ModelView
{

class QEXTMvvmCustomEditor;
class QEXTMvvmSessionItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit QEXTMvvmSessionItem data in the context of DefaultEditorFactory.

namespace QEXTMvvmEditorBuilders
{

using editor_t = std::unique_ptr<QEXTMvvmCustomEditor>;
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

//! Builder for ComboProperty editor.
QEXT_MVVM_API builder_t ComboPropertyEditorBuilder();

//! Builder for external property editor.
QEXT_MVVM_API builder_t ExternalPropertyEditorBuilder();

//! Builder for ComboProperty editor with multi-selection functionality.
QEXT_MVVM_API builder_t SelectableComboPropertyEditorBuilder();

} // namespace EditorBuilders

} // namespace ModelView

#endif // _QEXTMVVMEDITORSEDITORBUILDERS_H
