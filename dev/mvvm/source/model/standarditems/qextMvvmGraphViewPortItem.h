// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
#define MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

namespace ModelView {

class QExtMvvmGraphItem;

//! 2D viewport specialized for showing multiple QExtMvvmGraphItem's.
//! Provides calculation of viewport's x-axis and y-axis range basing on QExtMvvmGraphItem data.
//! Provides functionality to hide selected graphs.

class QEXT_MVVM_API QExtMvvmGraphViewportItem : public QExtMvvmViewportItem {
public:
    QExtMvvmGraphViewportItem(const std::string& QExtMvvmModelType = Constants::GraphViewportItemType);

    std::vector<QExtMvvmGraphItem*> graphItems() const;

    std::vector<QExtMvvmGraphItem*> visibleGraphItems() const;

    void setVisible(const std::vector<QExtMvvmGraphItem*>& visible_graph_items);

    void setAllVisible();

protected:
    std::pair<double, double> data_xaxis_range() const override;
    std::pair<double, double> data_yaxis_range() const override;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
