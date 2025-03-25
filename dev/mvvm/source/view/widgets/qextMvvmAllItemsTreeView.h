// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ALLITEMSTREEVIEW_H
#define MVVM_WIDGETS_ALLITEMSTREEVIEW_H

#include <qextMvvmItemsTreeView.h>

namespace ModelView {

class QExtMvvmSessionModel;

//! Widget holding standard QTreeView and intended for displaying all items of QExtMvvmSessionModel.

class QEXT_MVVM_API AllItemsTreeView : public QExtMvvmItemsTreeView {
    Q_OBJECT

public:
    AllItemsTreeView(QExtMvvmSessionModel* model, QWidget* parent = nullptr);
    ~AllItemsTreeView() override;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ALLITEMSTREEVIEW_H
