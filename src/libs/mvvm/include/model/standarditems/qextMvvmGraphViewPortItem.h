#ifndef _QEXTMVVMGRAPHVIEWPORTITEM_H
#define _QEXTMVVMGRAPHVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

class QEXTMvvmGraphItem;

//! 2D viewport specialized for showing multiple QEXTMvvmGraphItem's.
//! Provides calculation of viewport's x-axis and y-axis range basing on QEXTMvvmGraphItem data.
//! Provides functionality to hide selected graphs.

class QEXT_MVVM_API QEXTMvvmGraphViewportItem : public QEXTMvvmViewportItem
{
public:
    QEXTMvvmGraphViewportItem(const QString& QString = QEXTMvvmConstants::GraphViewportItemType);

    QVector<QEXTMvvmGraphItem*> graphItems() const;

    QVector<QEXTMvvmGraphItem*> visibleGraphItems() const;

    void setVisible(const QVector<QEXTMvvmGraphItem*>& visible_graph_items);

    void setAllVisible();

protected:
    QPair<double, double> dataXAxisRange() const QEXT_DECL_OVERRIDE;
    QPair<double, double> dataYAxisRange() const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMGRAPHVIEWPORTITEM_H
