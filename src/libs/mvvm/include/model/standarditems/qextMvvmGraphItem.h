#ifndef _QEXTMVVMGRAPHITEM_H
#define _QEXTMVVMGRAPHITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

class QEXTMvvmData1DItem;
class QEXTMvvmPenItem;

//! One-dimensional graph representation of QEXTMvvmData1DItem.
//! Contains plot properties (i.e. color, line type etc) and link to QEXTMvvmData1DItem, which will provide
//! actual data to plot. QEXTMvvmGraphItem is intended for plotting only via QEXTMvvmGraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_LINK = "P_LINK";
    static inline const std::string P_GRAPH_TITLE = "P_GRAPH_TITLE";
    static inline const std::string P_PEN = "P_PEN";
    static inline const std::string P_DISPLAYED = "P_DISPLAYED";

    QEXTMvvmGraphItem(const std::string& QEXTMvvmModelType = Constants::GraphItemType);

    void setDataItem(const QEXTMvvmData1DItem* item);

    void setFromGraphItem(const QEXTMvvmGraphItem* graph_item);

    QEXTMvvmData1DItem* dataItem() const;

    std::vector<double> binCenters() const;

    std::vector<double> binValues() const;

    std::vector<double> binErrors() const;

    std::string colorName() const;
    void setNamedColor(const std::string& named_color);

    QEXTMvvmPenItem* penItem() const;
};

} // namespace ModelView

#endif // _QEXTMVVMGRAPHITEM_H
