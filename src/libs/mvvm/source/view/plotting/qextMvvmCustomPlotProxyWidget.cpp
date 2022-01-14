// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QWidget>
#include <plotting/qextMvvmCustomPlotProxyWidget.h>

using namespace ModelView;

QEXTMvvmCustomPlotProxyWidget::QEXTMvvmCustomPlotProxyWidget(QWidget* colormap)
{
    setWidget(colormap);
    colormap->installEventFilter(this);
}

//! Notifies all graphics items about axes viewport change in QCustomPlot.
//! Used in RegionOfInterestView to recalculate bounding box and scene positions depending on
//! current state of CustomPlotSceneAdapter.

bool QEXTMvvmCustomPlotProxyWidget::eventFilter(QObject* /*object*/, QEvent* event)
{
    // catching zoom/resize events in QCustomPlot
    if (event->type() == QEvent::Resize || event->type() == QEvent::UpdateRequest) {
        scene()->advance(); // notifying all graphics items
        return false;
    }
    return true;
}

void QEXTMvvmCustomPlotProxyWidget::setBlockSignalsToProxy(bool value)
{
    block_signals_to_proxy = value;
}

void QEXTMvvmCustomPlotProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mousePressEvent(event);
}

void QEXTMvvmCustomPlotProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseMoveEvent(event);
}

void QEXTMvvmCustomPlotProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void QEXTMvvmCustomPlotProxyWidget::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::wheelEvent(event);
}
