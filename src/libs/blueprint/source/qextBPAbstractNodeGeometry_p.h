#ifndef _QEXTBPABSTRACTNODEGEOMETRY_P_H
#define _QEXTBPABSTRACTNODEGEOMETRY_P_H

#include <qextBPAbstractNodeGeometry.h>

class QExtBPAbstractNodeGeometryPrivate
{
public:
    QExtBPAbstractNodeGeometryPrivate(QExtBPAbstractNodeGeometry *q, QExtBPAbstractGraphModel &graphModel);
    virtual ~QExtBPAbstractNodeGeometryPrivate();

    QExtBPAbstractNodeGeometry * const q_ptr;

    QExtBPAbstractGraphModel &m_graphModel;

private:
    QEXT_DECLARE_PUBLIC(QExtBPAbstractNodeGeometry)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPAbstractNodeGeometryPrivate)
};

#endif // _QEXTBPABSTRACTNODEGEOMETRY_P_H
