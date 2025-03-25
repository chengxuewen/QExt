// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CELLEDITORSCORE_SAMPLEMODEL_H
#define CELLEDITORSCORE_SAMPLEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>
#include <string>

namespace CellEditors {

//! Demo item demonstrating supported properties.

class DemoPropertiesItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
    static constexpr const char *P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
    static constexpr const char *P_STRING_PROPERTY = "P_STRING_PROPERTY";
    static constexpr const char *P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";
    static constexpr const char *P_COLOR_PROPERTY = "P_COLOR_PROPERTY";
    static constexpr const char *P_COMBO_PROPERTY = "P_COMBO_PROPERTY";
    static constexpr const char *P_SELECTABLE_COMBO_PROPERTY = "P_SELECTABLE_COMBO_PROPERTY";
    static constexpr const char *P_EXTERNAL_PROPERTY = "P_EXTERNAL_PROPERTY";

    DemoPropertiesItem();
};

//! Main application model.

class SampleModel : public ModelView::QExtMvvmSessionModel {
public:
    SampleModel();
};

} // namespace CellEditors

#endif // CELLEDITORSCORE_SAMPLEMODEL_H
