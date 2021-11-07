#ifndef _QEXTMVVMGRAPHITEM_H
#define _QEXTMVVMGRAPHITEM_H

#include <qextMvvmCompoundItem.h>

class QEXTMvvmData1DItem;
class QEXTMvvmPenItem;

//! One-dimensional graph representation of QEXTMvvmData1DItem.
//! Contains plot properties (i.e. color, line type etc) and link to QEXTMvvmData1DItem, which will provide
//! actual data to plot. QEXTMvvmGraphItem is intended for plotting only via QEXTMvvmGraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_LINK = "P_LINK";
    static inline const QString P_GRAPH_TITLE = "P_GRAPH_TITLE";
    static inline const QString P_PEN = "P_PEN";
    static inline const QString P_DISPLAYED = "P_DISPLAYED";

    QEXTMvvmGraphItem(const QString& QString = QEXTMvvmConstants::GraphItemType);

    void setDataItem(const QEXTMvvmData1DItem* item);

    void setFromGraphItem(const QEXTMvvmGraphItem* graph_item);

    QEXTMvvmData1DItem* dataItem() const;

    QVector<double> binCenters() const;

    QVector<double> binValues() const;

    QVector<double> binErrors() const;

    QString colorName() const;
    void setNamedColor(const QString& named_color);

    QEXTMvvmPenItem* penItem() const;
};

#endif // _QEXTMVVMGRAPHITEM_H
