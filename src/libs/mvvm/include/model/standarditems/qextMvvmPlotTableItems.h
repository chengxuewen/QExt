#ifndef _QEXTMVVMPLOTTABLEITEMS_H
#define _QEXTMVVMPLOTTABLEITEMS_H

//! @file plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include <qextMvvmCompoundItem.h>


//! Represent text item on plot.

class QEXT_MVVM_API QEXTMvvmTextItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_TEXT = "P_TEXT";
    static inline const QString P_FONT = "P_FONT";
    static inline const QString P_SIZE = "P_SIZE";

    QEXTMvvmTextItem();
};

//! Represents basics settings of QPen.

class QEXT_MVVM_API QEXTMvvmPenItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_COLOR = "P_COLOR";
    static inline const QString P_STYLE = "P_STYLE";
    static inline const QString P_WIDTH = "P_WIDTH";

    QEXTMvvmPenItem();

    void setSelected(bool is_selected);

    QString colorName() const;
    void setNamedColor(const QString& named_color);
};

#endif // _QEXTMVVMPLOTTABLEITEMS_H
