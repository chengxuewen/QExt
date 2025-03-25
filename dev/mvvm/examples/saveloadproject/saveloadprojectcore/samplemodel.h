// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAVELOADPROJECTCORE_SAMPLEMODEL_H
#define SAVELOADPROJECTCORE_SAMPLEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>
#include <string>

//! Demo item which demonstrates all supported properties.

class DemoItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
    static constexpr const char *P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
    static constexpr const char *P_STRING_PROPERTY = "P_STRING_PROPERTY";
    static constexpr const char *P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";
    static constexpr const char *P_COLOR_PROPERTY = "P_COLOR_PROPERTY";
    static constexpr const char *P_COMBO_PROPERTY = "P_COMBO_PROPERTY";

    DemoItem();
};

//! Main application model.

class SampleModel : public ModelView::QExtMvvmSessionModel {
public:
    SampleModel();

    void appendNewItem(ModelView::QExtMvvmSessionItem* container);

private:
    void populateModel();
};

#endif // SAVELOADPROJECTCORE_SAMPLEMODEL_H
