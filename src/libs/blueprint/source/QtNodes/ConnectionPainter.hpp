#pragma once

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

#include "qextBPTypes.h"

class QExtBPConnectionGraphicsObject;

class QExtBPConnectionPainter
{
public:
    static void paint(QPainter *painter, QExtBPConnectionGraphicsObject const &cgo);

    static QPainterPath getPainterStroke(QExtBPConnectionGraphicsObject const &cgo);
};

