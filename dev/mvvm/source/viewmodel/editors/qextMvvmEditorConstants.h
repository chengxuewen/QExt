// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_EDITOR_CONSTANTS_H
#define MVVM_EDITORS_EDITOR_CONSTANTS_H

//! @file editor_constants.h
//! Collection of constants specific for cell editing.

#include <string>

namespace ModelView
{
namespace Constants
{

static constexpr const char *BoolEditorType = "QExtMvvmBoolEditor";
static constexpr const char *ColorEditorType = "QExtMvvmColorEditor";
static constexpr const char *ComboPropertyEditorType = "QExtMvvmComboPropertyEditor";
static constexpr const char *DoubleEditorType = "QExtMvvmDoubleEditor";
static constexpr const char *ExternalPropertyEditorType = "QExtMvvmExternalPropertyEditor";
static constexpr const char *IntegerEditorType = "QExtMvvmIntegerEditor";
static constexpr const char *ScientficDoubleEditorType = "ScientficDoubleEditor";
static constexpr const char *ScientficSpinBoxEditorType = "ScientficSpinBoxEditor";
static constexpr const char *SelectableComboPropertyEditorType = "SelectableComboPropertyEditor";

const int default_double_decimals = 4; //! number of digits after decimal points

}
} // namespace ModelView::Constants

#endif // MVVM_EDITORS_EDITOR_CONSTANTS_H
