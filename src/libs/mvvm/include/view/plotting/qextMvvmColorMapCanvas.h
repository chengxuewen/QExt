#ifndef _QEXTMVVMCOLORMAPCANVAS_H
#define _QEXTMVVMCOLORMAPCANVAS_H

#include <qextMvvmGlobal.h>

#include <QWidget>
#include <QScopedPointer>

class QEXTMvvmColorMapViewportItem;
class QEXTMvvmSceneAdapterInterface;

//! Widget to show 2D data as color map.
//! Contains embedded QCustomPlot widget, shows content of QEXTMvvmColorMapViewportItem.

class QEXT_MVVM_API QEXTMvvmColorMapCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmColorMapCanvas(QWidget* parent = nullptr);
    ~QEXTMvvmColorMapCanvas() QEXT_DECL_OVERRIDE;

    void setItem(QEXTMvvmColorMapViewportItem* viewport_item);

    QEXTMvvmSceneAdapterInterface *createSceneAdapter() const;

private:
    struct ColorMapCanvasImpl;
    QScopedPointer<ColorMapCanvasImpl> p_impl;
};


#endif // _QEXTMVVMCOLORMAPCANVAS_H
