#ifndef _QEXTGUIITEMCHANGELISTENER_H
#define _QEXTGUIITEMCHANGELISTENER_H

#include <qextGuiGlobal.h>

class QRectF;
class QEXTGuiGVItem;
class QEXTGuiAnchors;
class QDeclarativeItemChangeListener
{
public:
    virtual void itemGeometryChanged(QEXTGuiGVItem *, const QRectF &, const QRectF &) {}
    virtual void itemSiblingOrderChanged(QEXTGuiGVItem *) {}
    virtual void itemVisibilityChanged(QEXTGuiGVItem *) {}
    virtual void itemOpacityChanged(QEXTGuiGVItem *) {}
    virtual void itemDestroyed(QEXTGuiGVItem *) {}
    virtual QEXTGuiAnchors *anchor() { return QEXT_DECL_NULLPTR; }
};

#endif // _QEXTGUIITEMCHANGELISTENER_H
