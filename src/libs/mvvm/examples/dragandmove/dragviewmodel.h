// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGVIEWMODEL_H
#define DRAGVIEWMODEL_H

#include <qextMvvmPropertyTableViewModel.h>


class QEXTMvvmModel;


namespace DragAndView
{

//! View model with drag-and-drop support. Relies on QEXTMvvmPropertyTableViewModel to show
//! properties of DemoItem in table-like views.

class DragViewModel : public QEXTMvvmPropertyTableViewModel
{
    Q_OBJECT

public:
    DragViewModel(QEXTMvvmModel* model, QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const QEXT_DECL_OVERRIDE;
    QMimeData* mimeData(const QModelIndexList& index_list) const QEXT_DECL_OVERRIDE;
    Qt::DropActions supportedDragActions() const QEXT_DECL_OVERRIDE;
    Qt::DropActions supportedDropActions() const QEXT_DECL_OVERRIDE;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                         const QModelIndex&) const QEXT_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) QEXT_DECL_OVERRIDE;
};

} // namespace DragAndView

#endif // DRAGVIEWMODEL_H
