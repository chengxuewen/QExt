#ifndef _QEXTMVVMPLOTTINGCUSTOMPLOTPROXYWIDGET_H
#define _QEXTMVVMPLOTTINGCUSTOMPLOTPROXYWIDGET_H

#include <qextMvvmGlobal.h>

#include <QGraphicsProxyWidget>

class QWidget;

namespace ModelView
{

//! Custom proxy widget to embed color map in graphics scene.

class QEXT_MVVM_API QEXTMvvmCustomPlotProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    QEXTMvvmCustomPlotProxyWidget(QWidget* colormap);

    bool eventFilter(QObject* object, QEvent* event);

    void setBlockSignalsToProxy(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void wheelEvent(QGraphicsSceneWheelEvent* event);

private:
    bool block_signals_to_proxy{false};
};

} // namespace ModelView

#endif //  _QEXTMVVMPLOTTINGCUSTOMPLOTPROXYWIDGET_H
