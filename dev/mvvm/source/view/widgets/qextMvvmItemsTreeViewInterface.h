// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
#define MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H

#include <qextMvvmGlobal.h>
#include <QWidget>

class QTreeView;

namespace ModelView {

class QExtMvvmSessionModel;

//! Saves and restores list of QExtMvvmSessionModel's to/from disk using json format.

class QEXT_MVVM_API QExtMvvmItemsTreeViewInterface : public QWidget {
    Q_OBJECT

public:
    virtual void setSessionModel(QExtMvvmSessionModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
