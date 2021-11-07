#include <qextMvvmLabelDataRowStrategy.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmItem.h>

//! Example:
//! For LayerItem two items will be generated: QEXTMvvmViewLabelItem and QEXTMvvmViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: QEXTMvvmViewLabelItem and QEXTMvvmViewDataItem.

QStringList QEXTMvvmLabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name" << "Value";
}

QVector<QEXTMvvmViewItem *> QEXTMvvmLabelDataRowStrategy::constructRow(QEXTMvvmItem *item)
{
    QVector<QEXTMvvmViewItem *> result;
    if (item)
    {
        result.append(new QEXTMvvmViewLabelItem(item));
        result.append(new QEXTMvvmViewDataItem(item));
    }
    return result;
}
