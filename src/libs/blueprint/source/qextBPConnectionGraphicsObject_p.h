#ifndef _QEXTBPCONNECTIONGRAPHICSOBJECT_P_H
#define _QEXTBPCONNECTIONGRAPHICSOBJECT_P_H

#include <qextBPConnectionGraphicsObject.h>

class QExtBPConnectionGraphicsObjectPrivate
{
public:
    QExtBPConnectionGraphicsObjectPrivate(QExtBPConnectionGraphicsObject *q, QExtBPAbstractGraphModel &graphModel);
    virtual ~QExtBPConnectionGraphicsObjectPrivate();

    QExtBPConnectionGraphicsObject * q_ptr;

    mutable QPointF m_in;
    mutable QPointF m_out;
    QExtBPAbstractGraphModel &m_graphModel;
    QExtBPConnectionState m_connectionState;
    QExtBPTypes::ConnectionId m_connectionId;

private:
    QEXT_DECL_PUBLIC(QExtBPConnectionGraphicsObject)
    QEXT_DISABLE_COPY_MOVE(QExtBPConnectionGraphicsObjectPrivate)
};

#endif // _QEXTBPCONNECTIONGRAPHICSOBJECT_P_H
