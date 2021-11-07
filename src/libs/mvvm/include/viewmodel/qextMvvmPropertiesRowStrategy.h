#ifndef _QEXTMVVMPROPERTIESROWSTRATEGY_H
#define _QEXTMVVMPROPERTIESROWSTRATEGY_H

#include <qextMvvmRowStrategyInterface.h>

class QStandardItem;


class QEXTMvvmItem;

//! Constructs row of QStandardItem's for given QEXTMvvmItem.
//! Row consists of columns with all QEXTMvvmPropertyItem's of given QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmPropertiesRowStrategy : public QEXTMvvmRowStrategyInterface
{
public:
    QEXTMvvmPropertiesRowStrategy(QVector<QString> labels = QVector<QString>());

    QStringList horizontalHeaderLabels() const QEXT_DECL_OVERRIDE;

    QVector<QEXTMvvmViewItem *> constructRow(QEXTMvvmItem *item) QEXT_DECL_OVERRIDE;

private:
    void updateColumnLabels(QVector<QEXTMvvmItem *> items);

    QVector<QString> m_currentColumnLabels;
    QVector<QString> m_userDefinedColumnLabels;
};


#endif // _QEXTMVVMPROPERTIESROWSTRATEGY_H
