#ifndef _QEXTMVVMPROPERTYTREEVIEW_H
#define _QEXTMVVMPROPERTYTREEVIEW_H

#include <qextMvvmItemsTreeView.h>


//! Widget holding standard QTreeView and intended for displaying all properties of given
//! QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmPropertyTreeView : public QEXTMvvmItemsTreeView
{
    Q_OBJECT

public:
    QEXTMvvmPropertyTreeView(QWidget* parent = nullptr);
    ~QEXTMvvmPropertyTreeView();

    void setItem(QEXTMvvmItem* item);
};


#endif // _QEXTMVVMPROPERTYTREEVIEW_H
