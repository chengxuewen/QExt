#ifndef _QEXTMVVMSTANDARDITEMSGRAPHVIEWPORTITEM_H
#define _QEXTMVVMSTANDARDITEMSGRAPHVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

namespace ModelView
{

class QEXTMvvmGraphItem;

//! 2D viewport specialized for showing multiple GraphItem's.
//! Provides calculation of viewport's x-axis and y-axis range basing on GraphItem data.
//! Provides functionality to hide selected graphs.

class QEXT_MVVM_API QEXTMvvmGraphViewportItem : public QEXTMvvmViewportItem
{
public:
    QEXTMvvmGraphViewportItem(const std::string& model_type = QEXTMvvmConstants::GraphViewportItemType);

    std::vector<QEXTMvvmGraphItem*> graphItems() const;

    std::vector<QEXTMvvmGraphItem*> visibleGraphItems() const;

    void setVisible(const std::vector<QEXTMvvmGraphItem*>& visible_graph_items);

    void setAllVisible();

protected:
    std::pair<double, double> data_xaxis_range() const override;
    std::pair<double, double> data_yaxis_range() const override;
};

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSGRAPHVIEWPORTITEM_H
