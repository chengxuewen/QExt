#ifndef _QEXTNATIVEWINDOWTESTER_H
#define _QEXTNATIVEWINDOWTESTER_H

#include <QMargins>
#include <QPoint>

class QEXTNativeWindowTester
{
public:
    virtual QMargins draggableMargins() const = 0;
    virtual QMargins maximizedMargins() const = 0;

    virtual bool hitTest(const QPoint &pos) const = 0;
};

#endif // _QEXTNATIVEWINDOWTESTER_H
