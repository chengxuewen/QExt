// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <cmath>
#include <editors/booleditor.h>
#include <editors/coloreditor.h>
#include <editors/combopropertyeditor.h>
#include <editors/doubleeditor.h>
#include <editors/editor_constants.h>
#include <editors/editorbuilders.h>
#include <editors/externalpropertyeditor.h>
#include <editors/integereditor.h>
#include <editors/scientificdoubleeditor.h>
#include <editors/scientificspinboxeditor.h>
#include <editors/selectablecomboboxeditor.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmSessionItem.h>
#include <utils/qextMvvmRealLimits.h>

namespace
{
double singleStep(int decimals)
{
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., decimals - 1);
}

double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

} // namespace

namespace ModelView ::EditorBuilders
{

builder_t BoolEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t { return std::make_unique<BoolEditor>(); };
    return builder;
}

builder_t IntegerEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = std::make_unique<IntegerEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return std::move(editor);
    };
    return builder;
}

builder_t DoubleEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = std::make_unique<DoubleEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
            editor->setSingleStep(singleStep(Constants::default_double_decimals));
            editor->setDecimals(Constants::default_double_decimals);
        }
        return std::move(editor);
    };
    return builder;
}

builder_t ScientificDoubleEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = std::make_unique<ScientificDoubleEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return std::move(editor);
    };
    return builder;
}

builder_t ScientificSpinBoxEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = std::make_unique<ScientificSpinBoxEditor>();
        if (item) {
            if (item->hasData(ItemDataRole::LIMITS)) {
                auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
                editor->setRange(limits.lowerLimit(), limits.upperLimit());
            }
            editor->setSingleStep(getStep(item->data<double>()));
        }
        editor->setDecimals(Constants::default_double_decimals);
        return std::move(editor);
    };
    return builder;
}

builder_t ColorEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t { return std::make_unique<ColorEditor>(); };
    return builder;
}

builder_t ComboPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return std::make_unique<ComboPropertyEditor>();
    };
    return builder;
}

builder_t ExternalPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return std::make_unique<ExternalPropertyEditor>();
    };
    return builder;
}

builder_t SelectableComboPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return std::make_unique<SelectableComboBoxEditor>();
    };
    return builder;
}

} // namespace ModelView::EditorBuilders
