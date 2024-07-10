#ifndef _QEXTBPUNDOCOMMONDS_H
#define _QEXTBPUNDOCOMMONDS_H

#include <qextBPTypes.h>

#include <QUndoCommand>
#include <QtCore/QJsonObject>
#include <QtCore/QPointF>

#include <unordered_set>

class QExtBPBasicGraphicsScene;

class QExtBPCreateCommand : public QUndoCommand
{
public:
    QExtBPCreateCommand(QExtBPBasicGraphicsScene *scene, QString const name, QPointF const &mouseScenePos);

    void undo() override;
    void redo() override;

private:
    QExtBPBasicGraphicsScene *_scene;
    QExtBPTypes::NodeId _nodeId;
    QJsonObject _sceneJson;
};

/**
 * Selected scene objects are serialized and then removed from the scene.
 * The deleted elements could be restored in `undo`.
 */
class QExtBPDeleteCommand : public QUndoCommand
{
public:
    QExtBPDeleteCommand(QExtBPBasicGraphicsScene *scene);

    void undo() override;
    void redo() override;

private:
    QExtBPBasicGraphicsScene *_scene;
    QJsonObject _sceneJson;
};

class CopyCommand : public QUndoCommand
{
public:
    CopyCommand(QExtBPBasicGraphicsScene *scene);
};

class QExtBPPasteCommand : public QUndoCommand
{
public:
    QExtBPPasteCommand(QExtBPBasicGraphicsScene *scene, QPointF const &mouseScenePos);

    void undo() override;
    void redo() override;

private:
    QJsonObject takeSceneJsonFromClipboard();
    QJsonObject makeNewNodeIdsInScene(QJsonObject const &sceneJson);

private:
    QExtBPBasicGraphicsScene *_scene;
    QPointF const &_mouseScenePos;
    QJsonObject _newSceneJson;
};

class QExtBPDisconnectCommand : public QUndoCommand
{
public:
    QExtBPDisconnectCommand(QExtBPBasicGraphicsScene *scene, QExtBPTypes::ConnectionId const);

    void undo() override;
    void redo() override;

private:
    QExtBPBasicGraphicsScene *_scene;

    QExtBPTypes::ConnectionId _connId;
};

class ConnectCommand : public QUndoCommand
{
public:
    ConnectCommand(QExtBPBasicGraphicsScene *scene, QExtBPTypes::ConnectionId const);

    void undo() override;
    void redo() override;

private:
    QExtBPBasicGraphicsScene *_scene;

    QExtBPTypes::ConnectionId _connId;
};

class QExtBPMoveNodeCommand : public QUndoCommand
{
public:
    QExtBPMoveNodeCommand(QExtBPBasicGraphicsScene *scene, QPointF const &diff);

    void undo() override;
    void redo() override;

    /**
   * A command ID is used in command compression. It must be an integer unique to
   * this command's class, or -1 if the command doesn't support compression.
   */
    int id() const override;

    /**
   * Several sequential movements could be merged into one command.
   */
    bool mergeWith(QUndoCommand const *c) override;

private:
    QExtBPBasicGraphicsScene *_scene;
    std::unordered_set<QExtBPTypes::NodeId> _selectedNodes;
    QPointF _diff;
};

#endif // _QEXTBPUNDOCOMMONDS_H
