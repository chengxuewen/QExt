#ifndef _QEXTBPUNDOCOMMONDS_H
#define _QEXTBPUNDOCOMMONDS_H

#include <qextBPTypes.h>

#include <QUndoCommand>
#include <QtCore/QPointF>
#include <QtCore/QJsonObject>

#include <unordered_set>

class QExtBPBasicGraphicsScene;

class QExtBPCreateCommand : public QUndoCommand
{
public:
    QExtBPCreateCommand(QExtBPBasicGraphicsScene *scene, const QString name, const QPointF &mouseScenePos);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QExtBPBasicGraphicsScene *m_scene;
    QExtBPTypes::NodeId m_nodeId;
    QJsonObject m_sceneJson;
};

/**
 * Selected scene objects are serialized and then removed from the scene.
 * The deleted elements could be restored in `undo`.
 */
class QExtBPDeleteCommand : public QUndoCommand
{
public:
    QExtBPDeleteCommand(QExtBPBasicGraphicsScene *scene);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QExtBPBasicGraphicsScene *m_scene;
    QJsonObject m_sceneJson;
};

class CopyCommand : public QUndoCommand
{
public:
    CopyCommand(QExtBPBasicGraphicsScene *scene);
};

class QExtBPPasteCommand : public QUndoCommand
{
public:
    QExtBPPasteCommand(QExtBPBasicGraphicsScene *scene, const QPointF &mouseScenePos);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QJsonObject takeSceneJsonFromClipboard();
    QJsonObject makeNewNodeIdsInScene(const QJsonObject &sceneJson);

private:
    QExtBPBasicGraphicsScene *m_scene;
    const QPointF &m_mouseScenePos;
    QJsonObject m_newSceneJson;
};

class QExtBPDisconnectCommand : public QUndoCommand
{
public:
    QExtBPDisconnectCommand(QExtBPBasicGraphicsScene *scene, const QExtBPTypes::ConnectionId);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QExtBPBasicGraphicsScene *m_scene;
    QExtBPTypes::ConnectionId m_connId;
};

class ConnectCommand : public QUndoCommand
{
public:
    ConnectCommand(QExtBPBasicGraphicsScene *scene, const QExtBPTypes::ConnectionId);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QExtBPBasicGraphicsScene *m_scene;
    QExtBPTypes::ConnectionId m_connId;
};

class QExtBPMoveNodeCommand : public QUndoCommand
{
public:
    QExtBPMoveNodeCommand(QExtBPBasicGraphicsScene *scene, const QPointF &diff);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

    /**
   * A command ID is used in command compression. It must be an integer unique to
   * this command's class, or -1 if the command doesn't support compression.
   */
    int id() const QEXT_OVERRIDE;

    /**
   * Several sequential movements could be merged into one command.
   */
    bool mergeWith(QUndoCommand const *c) QEXT_OVERRIDE;

private:
    QPointF m_diff;
    QExtBPBasicGraphicsScene *m_scene;
    std::unordered_set<QExtBPTypes::NodeId> m_selectedNodes;
};

#endif // _QEXTBPUNDOCOMMONDS_H
