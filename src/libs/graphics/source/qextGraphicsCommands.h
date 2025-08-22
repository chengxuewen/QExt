#ifndef _QEXTGRAPHICSCOMMANDS_H
#define _QEXTGRAPHICSCOMMANDS_H

#include "qextGraphicsScene.h"

#include <QUndoCommand>

class QEXT_GRAPHICS_API QExtGraphicsMoveShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsMoveShapeCommand(QGraphicsScene *scene, const QPointF &delta, QUndoCommand *parent = QEXT_NULLPTR);
    QExtGraphicsMoveShapeCommand(QGraphicsItem *item, const QPointF &delta , QUndoCommand *parent = QEXT_NULLPTR);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsMoveShapeCommand)
    QList<QGraphicsItem *> m_items;
    QGraphicsScene *m_scene;
    QGraphicsItem  *m_item;
    QPointF m_delta;
    bool m_moved;
};


class QEXT_GRAPHICS_API QExtGraphicsResizeShapeCommand : public QUndoCommand
{
public:
    enum { Id = 1234, };

    QExtGraphicsResizeShapeCommand(QGraphicsItem *item, int handle, const QPointF &scale,
                                   QUndoCommand *parent = QEXT_NULLPTR);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

    bool mergeWith(const QUndoCommand *command) QEXT_OVERRIDE;
    int id() const QEXT_OVERRIDE { return Id; }

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsResizeShapeCommand)
    QGraphicsItem *m_item;
    QPointF m_scale;
    bool m_resized;
    int m_opposite;
    int m_handle;
};


class QEXT_GRAPHICS_API QExtGraphicsControlShapeCommand : public QUndoCommand
{
public:
    enum { Id = 1235, };

    QExtGraphicsControlShapeCommand(QGraphicsItem *item, int handle, const QPointF &newPos, const QPointF &lastPos,
                                    QUndoCommand *parent = QEXT_NULLPTR);
    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

    bool mergeWith(const QUndoCommand *command) QEXT_OVERRIDE;
    int id() const QEXT_OVERRIDE { return Id; }

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsControlShapeCommand)
    QGraphicsItem *m_item;
    QPointF m_lastPos;
    QPointF m_newPos;
    bool m_controled;
    int m_handle;
};


class QEXT_GRAPHICS_API QExtGraphicsRotateShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsRotateShapeCommand(QGraphicsItem *item , const qreal oldAngle, QUndoCommand *parent = QEXT_NULLPTR);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsRotateShapeCommand)
    QGraphicsItem *m_item;
    qreal m_oldAngle;
    qreal m_newAngle;
};


class QEXT_GRAPHICS_API QExtGraphicsRemoveShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsRemoveShapeCommand(QGraphicsScene *scene, QUndoCommand *parent = QEXT_NULLPTR);
    ~QExtGraphicsRemoveShapeCommand() QEXT_OVERRIDE;

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsRemoveShapeCommand)
    QList<QGraphicsItem *> m_items;
    QGraphicsScene *m_scene;
};


class QEXT_GRAPHICS_API QExtGraphicsGroupShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsGroupShapeCommand(QGraphicsItemGroup *group, QGraphicsScene *scene,
                                  QUndoCommand *parent = QEXT_NULLPTR);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsGroupShapeCommand)
    QList<QGraphicsItem *> m_items;
    QGraphicsItemGroup * m_group;
    QGraphicsScene *m_scene;
    bool m_undo;
};


class QEXT_GRAPHICS_API QExtGraphicsUnGroupShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsUnGroupShapeCommand(QGraphicsItemGroup *group, QGraphicsScene *scene,
                                    QUndoCommand *parent = QEXT_NULLPTR);

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsUnGroupShapeCommand)
    QList<QGraphicsItem *> m_items;
    QGraphicsItemGroup * m_group;
    QGraphicsScene *m_scene;
};

class QEXT_GRAPHICS_API QExtGraphicsAddShapeCommand : public QUndoCommand
{
public:
    QExtGraphicsAddShapeCommand(QGraphicsItem *item , QGraphicsScene *scene,
                                QUndoCommand *parent = QEXT_NULLPTR);
    ~QExtGraphicsAddShapeCommand() QEXT_OVERRIDE;

    void undo() QEXT_OVERRIDE;
    void redo() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsAddShapeCommand)
    QGraphicsItem *m_diagramItem;
    QGraphicsScene *m_scene;
    QPointF m_initPosition;
};

QString QEXT_GRAPHICS_API qextGraphicsCreateCommandString(QGraphicsItem *item, const QPointF &point);

#endif // _QEXTGRAPHICSCOMMANDS_H

