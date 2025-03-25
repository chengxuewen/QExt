// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_GRAPHITEM_H
#define MVVM_STANDARDITEMS_GRAPHITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView {

class QExtMvvmData1DItem;
class QExtMvvmPenItem;

//! One-dimensional graph representation of QExtMvvmData1DItem.
//! Contains plot properties (i.e. color, line type etc) and link to QExtMvvmData1DItem, which will provide
//! actual data to plot. QExtMvvmGraphItem is intended for plotting only via QExtMvvmGraphViewportItem.

class QEXT_MVVM_API QExtMvvmGraphItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_LINK = "P_LINK";
    static constexpr const char *P_GRAPH_TITLE = "P_GRAPH_TITLE";
    static constexpr const char *P_PEN = "P_PEN";
    static constexpr const char *P_DISPLAYED = "P_DISPLAYED";

    QExtMvvmGraphItem(const std::string& QExtMvvmModelType = Constants::GraphItemType);

    void setDataItem(const QExtMvvmData1DItem* item);

    void setFromGraphItem(const QExtMvvmGraphItem* graph_item);

    QExtMvvmData1DItem* dataItem() const;

    std::vector<double> binCenters() const;

    std::vector<double> binValues() const;

    std::vector<double> binErrors() const;

    std::string colorName() const;
    void setNamedColor(const std::string& named_color);

    QExtMvvmPenItem* penItem() const;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_GRAPHITEM_H
