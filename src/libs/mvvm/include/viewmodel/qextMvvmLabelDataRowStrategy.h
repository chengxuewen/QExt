#ifndef _QEXTMVVMLABELDATAROWSTRATEGY_H
#define _QEXTMVVMLABELDATAROWSTRATEGY_H

#include <qextMvvmRowStrategyInterface.h>

#include <QSharedPointer>

class QStandardItem;

class QEXTMvvmItem;

//! Constructs row of QStandardItem's for given QEXTMvvmItem.
//! Row consists of two columns, QEXTMvvmViewLabelItem for QEXTMvvmItem's display role and
//! QEXTMvvmViewDataItem for Session's item data role.

class QEXT_MVVM_API QEXTMvvmLabelDataRowStrategy : public QEXTMvvmRowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const QEXT_DECL_OVERRIDE;

    QVector<QEXTMvvmViewItem *> constructRow(QEXTMvvmItem *) QEXT_DECL_OVERRIDE;
};


#endif // _QEXTMVVMLABELDATAROWSTRATEGY_H
