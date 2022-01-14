#ifndef _QEXTMVVMWIDGETSPROPERTYTREEVIEW_H
#define _QEXTMVVMWIDGETSPROPERTYTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

namespace ModelView
{

//! Widget holding standard QTreeView and intended for displaying all properties of given
//! QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmPropertyTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmPropertyTreeView(QWidget* parent = nullptr);
    ~QEXTMvvmPropertyTreeView();

    void setItem(QEXTMvvmSessionItem* item);
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSPROPERTYTREEVIEW_H
