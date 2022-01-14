// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <cmath>
#include <qextMvvmBoolEditor.h>
#include <qextMvvmColorEditor.h>
#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmDoubleEditor.h>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmEditorBuilders.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmIntegerEditor.h>
#include <qextMvvmScientificDoubleEditor.h>
#include <qextMvvmScientificSpinBoxEditor.h>
#include <qextMvvmSelectableComboBoxEditor.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmRealLimits.h>

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

namespace ModelView ::QEXTMvvmEditorBuilders
{

builder_t BoolEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t { return make_unique<QEXTMvvmBoolEditor>(); };
    return builder;
}

builder_t IntegerEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = make_unique<QEXTMvvmIntegerEditor>();
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
        auto editor = make_unique<QEXTMvvmDoubleEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
            editor->setSingleStep(singleStep(QEXTMvvmConstants::default_double_decimals));
            editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
        }
        return std::move(editor);
    };
    return builder;
}

builder_t ScientificDoubleEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem* item) -> editor_t {
        auto editor = make_unique<QEXTMvvmScientificDoubleEditor>();
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
        auto editor = make_unique<QEXTMvvmScientificSpinBoxEditor>();
        if (item) {
            if (item->hasData(ItemDataRole::LIMITS)) {
                auto limits = item->data<QEXTMvvmRealLimits>(ItemDataRole::LIMITS);
                editor->setRange(limits.lowerLimit(), limits.upperLimit());
            }
            editor->setSingleStep(getStep(item->data<double>()));
        }
        editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
        return std::move(editor);
    };
    return builder;
}

builder_t ColorEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t { return make_unique<QEXTMvvmColorEditor>(); };
    return builder;
}

builder_t ComboPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return make_unique<QEXTMvvmComboPropertyEditor>();
    };
    return builder;
}

builder_t ExternalPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return make_unique<QEXTMvvmExternalPropertyEditor>();
    };
    return builder;
}

builder_t SelectableComboPropertyEditorBuilder()
{
    auto builder = [](const QEXTMvvmSessionItem*) -> editor_t {
        return make_unique<QEXTMvvmSelectableComboBoxEditor>();
    };
    return builder;
}

} // namespace ModelView::EditorBuilders
