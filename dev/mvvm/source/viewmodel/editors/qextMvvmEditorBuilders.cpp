// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmEditorBuilders.h>
#include <qextMvvmBoolEditor.h>
#include <qextMvvmColorEditor.h>
#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmDoubleEditor.h>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmIntegerEditor.h>
#include <qextMvvmScientificDoubleEditor.h>
#include <qextMvvmScientificSpinBoxEditor.h>
#include <qextMvvmSelectableComboBoxEditor.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmRealLimits.h>
#include <cmath>

namespace {
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

namespace ModelView ::EditorBuilders {

builder_t BoolEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem*) -> editor_t { return qextMakeUnique<QExtMvvmBoolEditor>(); };
    return builder;
}

builder_t IntegerEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem* item) -> editor_t {
        auto editor = qextMakeUnique<QExtMvvmIntegerEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QExtMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return editor;
    };
    return builder;
}

builder_t DoubleEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem* item) -> editor_t {
        auto editor = qextMakeUnique<QExtMvvmDoubleEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QExtMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
            editor->setSingleStep(singleStep(Constants::default_double_decimals));
            editor->setDecimals(Constants::default_double_decimals);
        }
        return editor;
    };
    return builder;
}

builder_t ScientificDoubleEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem* item) -> editor_t {
        auto editor = qextMakeUnique<ScientificDoubleEditor>();
        if (item && item->hasData(ItemDataRole::LIMITS)) {
            auto limits = item->data<QExtMvvmRealLimits>(ItemDataRole::LIMITS);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return editor;
    };
    return builder;
}

builder_t ScientificSpinBoxEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem* item) -> editor_t {
        auto editor = qextMakeUnique<QExtMvvmScientificSpinBoxEditor>();
        if (item) {
            if (item->hasData(ItemDataRole::LIMITS)) {
                auto limits = item->data<QExtMvvmRealLimits>(ItemDataRole::LIMITS);
                editor->setRange(limits.lowerLimit(), limits.upperLimit());
            }
            editor->setSingleStep(getStep(item->data<double>()));
        }
        editor->setDecimals(Constants::default_double_decimals);
        return editor;
    };
    return builder;
}

builder_t ColorEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem*) -> editor_t { return qextMakeUnique<QExtMvvmColorEditor>(); };
    return builder;
}

builder_t ComboPropertyEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem*) -> editor_t {
        return qextMakeUnique<QExtMvvmComboPropertyEditor>();
    };
    return builder;
}

builder_t ExternalPropertyEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem*) -> editor_t {
        return qextMakeUnique<QExtMvvmExternalPropertyEditor>();
    };
    return builder;
}

builder_t SelectableComboPropertyEditorBuilder()
{
    auto builder = [](const QExtMvvmSessionItem*) -> editor_t {
        return qextMakeUnique<QExtMvvmSelectableComboBoxEditor>();
    };
    return builder;
}

} // namespace ModelView::EditorBuilders
