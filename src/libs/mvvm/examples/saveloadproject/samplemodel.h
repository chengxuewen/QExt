// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <qextMvvmModel.h>
#include <qextMvvmCompoundItem.h>
#include <string>

//! Demo item which demonstrates all supported properties.

class DemoItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
    static inline const QString P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
    static inline const QString P_STRING_PROPERTY = "P_STRING_PROPERTY";
    static inline const QString P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";
    static inline const QString P_COLOR_PROPERTY = "P_COLOR_PROPERTY";
    static inline const QString P_COMBO_PROPERTY = "P_COMBO_PROPERTY";

    DemoItem();
};

//! Main application model.

class SampleModel : public QEXTMvvmModel
{
public:
    SampleModel();

    void appendNewItem(QEXTMvvmItem* container);

private:
    void initModelContent();
};

#endif
