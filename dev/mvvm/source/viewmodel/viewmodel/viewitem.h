// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWITEM_H
#define MVVM_VIEWMODEL_VIEWITEM_H

#include "model/core/variant.h"
#include <qextMvvmGlobal.h>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItem;

//! Represents the view of QExtMvvmSessionItem's data in a single cell of QExtMvvmViewModel.

class QEXT_MVVM_API QExtMvvmViewItem {
public:
    virtual ~QExtMvvmViewItem();

    int rowCount() const;

    int columnCount() const;

    void appendRow(std::vector<QExtUniquePointer<QExtMvvmViewItem>> items);

    void insertRow(int row, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items);

    void removeRow(int row);

    void clear();

    QExtMvvmViewItem* parent() const;

    QExtMvvmViewItem* child(int row, int column) const;

    QExtMvvmSessionItem* item() const;

    int item_role() const;

    int row() const;

    int column() const;

    virtual QVariant data(int qt_role) const;

    virtual bool setData(const QVariant& value, int qt_role);

    virtual Qt::ItemFlags flags() const;

    std::vector<QExtMvvmViewItem*> children() const;

protected:
    QExtMvvmViewItem(QExtMvvmSessionItem* item, int role);
    void setParent(QExtMvvmViewItem* parent);

private:
    struct ViewItemImpl;
    QExtUniquePointer<ViewItemImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWITEM_H
