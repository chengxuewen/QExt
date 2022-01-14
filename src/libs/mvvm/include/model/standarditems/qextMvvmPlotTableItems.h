#ifndef _QEXTMVVMSTANDARDITEMSPLOTTABLEITEMS_H
#define _QEXTMVVMSTANDARDITEMSPLOTTABLEITEMS_H

//! @file plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

//! Represent text item on plot.

class QEXT_MVVM_API QEXTMvvmTextItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_TEXT = "P_TEXT";
    static inline const std::string P_FONT = "P_FONT";
    static inline const std::string P_SIZE = "P_SIZE";

    QEXTMvvmTextItem();
};

//! Represents basics settings of QPen.

class QEXT_MVVM_API QEXTMvvmPenItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_STYLE = "P_STYLE";
    static inline const std::string P_WIDTH = "P_WIDTH";

    QEXTMvvmPenItem();

    void setSelected(bool is_selected);

    std::string colorName() const;
    void setNamedColor(const std::string& named_color);
};

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSPLOTTABLEITEMS_H
