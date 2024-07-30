#ifndef _QEXTBPBASICGRAPHICSSCENE_P_H
#define _QEXTBPBASICGRAPHICSSCENE_P_H

#include <qextBPBasicGraphicsScene.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPConnectionIdHash.h>
#include <qextBPQUuidStdHash.h>

class QExtBPBasicGraphicsScenePrivate
{
public:
    using UniqueNodeGraphicsObject = QScopedPointer<QExtBPNodeGraphicsObject>;
    using UniqueConnectionGraphicsObject = QScopedPointer<QExtBPConnectionGraphicsObject>;

    explicit QExtBPBasicGraphicsScenePrivate(QExtBPBasicGraphicsScene *q, QExtBPAbstractGraphModel &graphModel);
    virtual ~QExtBPBasicGraphicsScenePrivate();

    void initBasicGraphicsScene();

    QExtBPBasicGraphicsScene * const q_ptr;

    QExtBPAbstractGraphModel &m_graphModel;

    QScopedPointer<QExtBPAbstractNodePainter> m_nodePainter;
    QScopedPointer<QExtBPAbstractNodeGeometry> m_nodeGeometry;
    QScopedPointer<QExtBPConnectionGraphicsObject> m_draftConnection;

    std::unordered_map<QExtBPTypes::NodeId, UniqueNodeGraphicsObject> m_nodeGraphicsObjects;
    std::unordered_map<QExtBPTypes::ConnectionId, UniqueConnectionGraphicsObject> m_connectionGraphicsObjects;

    bool m_nodeDrag;
    Qt::Orientation m_orientation;
    QScopedPointer<QUndoStack> m_undoStack;

private:
    QEXT_DECL_PUBLIC(QExtBPBasicGraphicsScene)
    QEXT_DISABLE_COPY_MOVE(QExtBPBasicGraphicsScenePrivate)
};


#endif // _QEXTBPBASICGRAPHICSSCENE_P_H
