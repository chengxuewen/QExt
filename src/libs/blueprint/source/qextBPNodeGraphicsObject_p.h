#ifndef _QEXTBPNODEGRAPHICSOBJECT_P_H
#define _QEXTBPNODEGRAPHICSOBJECT_P_H

#include <qextBPNodeGraphicsObject.h>

class QExtBPNodeGraphicsObjectPrivate
{
public:
    QExtBPNodeGraphicsObjectPrivate(QExtBPNodeGraphicsObject *q, QExtBPAbstractGraphModel &graphModel);
    virtual ~QExtBPNodeGraphicsObjectPrivate();

    QExtBPNodeGraphicsObject * const q_ptr;

    QExtBPNodeState m_nodeState;
    QExtBPTypes::NodeId m_nodeId;
    QGraphicsProxyWidget *m_proxyWidget; // either QEXT_NULLPTR or owned by parent QGraphicsItem
    QExtBPAbstractGraphModel &m_graphModel;

private:
    QEXT_DECL_PUBLIC(QExtBPNodeGraphicsObject)
    QEXT_DISABLE_COPY_MOVE(QExtBPNodeGraphicsObjectPrivate)
};

#endif // _QEXTBPNODEGRAPHICSOBJECT_P_H
