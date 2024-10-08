#ifndef _QEXTBPABSTRACTGRAPHMODEL_P_H
#define _QEXTBPABSTRACTGRAPHMODEL_P_H

#include <qextBPAbstractGraphModel.h>

#include <QVector>

class QExtBPAbstractGraphModelPrivate
{
public:
    explicit QExtBPAbstractGraphModelPrivate(QExtBPAbstractGraphModel *q);
    virtual ~QExtBPAbstractGraphModelPrivate();

    QExtBPAbstractGraphModel * const q_ptr;

    QVector<QExtBPTypes::ConnectionId> m_shiftedByDynamicPortsConnections;

private:
    QEXT_DECL_PUBLIC(QExtBPAbstractGraphModel)
    QEXT_DISABLE_COPY_MOVE(QExtBPAbstractGraphModelPrivate)
};

#endif // _QEXTBPABSTRACTGRAPHMODEL_P_H
