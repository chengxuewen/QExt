// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_TOPITEMSTREEVIEW_H
#define MVVM_WIDGETS_TOPITEMSTREEVIEW_H

#include <widgets/itemstreeview.h>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Widget holding standard QTreeView and intended for displaying all top level
//! items of QEXTMvvmSessionModel.

//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API TopItemsTreeView : public ItemsTreeView
{
    Q_OBJECT

public:
    TopItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent = nullptr);
    ~TopItemsTreeView();
};

} // namespace ModelView

#endif // MVVM_WIDGETS_TOPITEMSTREEVIEW_H
