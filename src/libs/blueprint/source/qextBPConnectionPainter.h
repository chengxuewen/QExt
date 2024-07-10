#ifndef _QEXTBPCONNECTIONPAINTER_H
#define _QEXTBPCONNECTIONPAINTER_H

#include <qextBPTypes.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

class QExtBPConnectionGraphicsObject;

class QExtBPConnectionPainter
{
public:
    static void paint(QPainter *painter, QExtBPConnectionGraphicsObject const &cgo);

    static QPainterPath getPainterStroke(QExtBPConnectionGraphicsObject const &cgo);
};

#endif // _QEXTBPCONNECTIONPAINTER_H
