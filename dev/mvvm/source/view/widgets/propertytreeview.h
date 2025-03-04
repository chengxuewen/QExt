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

#include "view/widgets/itemstreeview.h"

namespace ModelView {

//! Widget holding standard QTreeView and intended for displaying all properties of given
//! QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmPropertyTreeView : public QExtMvvmItemsTreeView {
    Q_OBJECT

public:
    QExtMvvmPropertyTreeView(QWidget* parent = nullptr);
    ~QExtMvvmPropertyTreeView();

    void setItem(QExtMvvmSessionItem* item);
};

} // namespace ModelView

#endif // MVVM_WIDGETS_PROPERTYTREEVIEW_H
