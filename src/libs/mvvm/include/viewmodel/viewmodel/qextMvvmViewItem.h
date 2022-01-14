#ifndef _QEXTMVVMVIEWMODELVIEWITEM_H
#define _QEXTMVVMVIEWMODELVIEWITEM_H

#include <qextMvvmGlobal.h>

#include <memory>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Represents the view of QEXTMvvmSessionItem's data in a single cell of ViewModel.

class QEXT_MVVM_API QEXTMvvmViewItem
{
public:
    virtual ~QEXTMvvmViewItem();

    int rowCount() const;

    int columnCount() const;

    void appendRow(std::vector<std::unique_ptr<QEXTMvvmViewItem>> items);

    void insertRow(int row, std::vector<std::unique_ptr<QEXTMvvmViewItem>> items);

    void removeRow(int row);

    void clear();

    QEXTMvvmViewItem* parent() const;

    QEXTMvvmViewItem* child(int row, int column) const;

    QEXTMvvmSessionItem* item() const;

    int item_role() const;

    int row() const;

    int column() const;

    virtual QVariant data(int qt_role) const;

    virtual bool setData(const QVariant& value, int qt_role);

    virtual Qt::ItemFlags flags() const;

    std::vector<QEXTMvvmViewItem*> children() const;

protected:
    QEXTMvvmViewItem(QEXTMvvmSessionItem* item, int role);
    void setParent(QEXTMvvmViewItem* parent);

private:
    struct ViewItemImpl;
    std::unique_ptr<ViewItemImpl> p_impl;
};

}; // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWITEM_H
