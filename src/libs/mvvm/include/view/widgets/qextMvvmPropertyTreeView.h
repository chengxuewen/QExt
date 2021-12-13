// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_PROPERTYTREEVIEW_H
#define MVVM_WIDGETS_PROPERTYTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

namespace ModelView
{

//! Widget holding standard QTreeView and intended for displaying all properties of given
//! QEXTMvvmSessionItem.

class QEXT_MVVM_API PropertyTreeView : public ItemsTreeView
{
    Q_OBJECT

public:
    PropertyTreeView(QWidget* parent = nullptr);
    ~PropertyTreeView();

    void setItem(QEXTMvvmSessionItem* item);
};

} // namespace ModelView

#endif // MVVM_WIDGETS_PROPERTYTREEVIEW_H
