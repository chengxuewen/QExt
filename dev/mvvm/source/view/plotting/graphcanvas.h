// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHCANVAS_H
#define MVVM_PLOTTING_GRAPHCANVAS_H

#include <qextMvvmGlobal.h>
#include <QWidget>
#include <memory>

namespace ModelView {

class QExtMvvmGraphViewportItem;
class QExtMvvmSceneAdapterInterface;

//! Widget to show scientific figure with multiple 1D graphs.
//! Contains embedded QCustomPlot widget, shows content of QExtMvvmGraphViewportItem.

class QEXT_MVVM_API QExtMvvmGraphCanvas : public QWidget {
    Q_OBJECT

public:
    explicit QExtMvvmGraphCanvas(QWidget* parent = nullptr);
    ~QExtMvvmGraphCanvas() override;

    void setItem(QExtMvvmGraphViewportItem* viewport_item);

    QExtUniquePointer<QExtMvvmSceneAdapterInterface> createSceneAdapter() const;

    void setViewportToContent(double left, double top, double right, double bottom);

    void setViewportToContent();

    void setAxisMargins(int left, int top, int right, int bottom);

signals:
    void axisMarginsChanged(int left, int top, int right, int bottom);

private:
    struct GraphCanvasImpl;
    QExtUniquePointer<GraphCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHCANVAS_H
