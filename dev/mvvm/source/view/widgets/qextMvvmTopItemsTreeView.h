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

#include <qextMvvmItemsTreeView.h>

namespace ModelView {

class QExtMvvmSessionModel;

//! Widget holding standard QTreeView and intended for displaying all top level
//! items of QExtMvvmSessionModel.

//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QExtMvvmTopItemsTreeView : public QExtMvvmItemsTreeView {
    Q_OBJECT

public:
    QExtMvvmTopItemsTreeView(QExtMvvmSessionModel* model, QWidget* parent = nullptr);
    ~QExtMvvmTopItemsTreeView();
};

} // namespace ModelView

#endif // MVVM_WIDGETS_TOPITEMSTREEVIEW_H
