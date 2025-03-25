// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
#define MVVM_STANDARDITEMS_PLOTTABLEITEMS_H

//! @file plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include <qextMvvmCompoundItem.h>

namespace ModelView {

//! Represent text item on plot.

class QEXT_MVVM_API QExtMvvmTextItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_TEXT = "P_TEXT";
    static constexpr const char *P_FONT = "P_FONT";
    static constexpr const char *P_SIZE = "P_SIZE";

    QExtMvvmTextItem();
};

//! Represents basics settings of QPen.

class QEXT_MVVM_API QExtMvvmPenItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_COLOR = "P_COLOR";
    static constexpr const char *P_STYLE = "P_STYLE";
    static constexpr const char *P_WIDTH = "P_WIDTH";

    QExtMvvmPenItem();

    void setSelected(bool is_selected);

    std::string colorName() const;
    void setNamedColor(const std::string& named_color);
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
