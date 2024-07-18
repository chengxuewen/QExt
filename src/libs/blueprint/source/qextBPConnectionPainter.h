#ifndef _QEXTBPCONNECTIONPAINTER_H
#define _QEXTBPCONNECTIONPAINTER_H

#include <qextBPTypes.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

class QExtBPConnectionGraphicsObject;

class QExtBPConnectionPainter
{
public:
    static void paint(QPainter *painter, const QExtBPConnectionGraphicsObject &cgo);

    static QPainterPath getPainterStroke(const QExtBPConnectionGraphicsObject &cgo);
};

#endif // _QEXTBPCONNECTIONPAINTER_H
