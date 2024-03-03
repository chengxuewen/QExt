#include <qextGraphicsCommands.h>

#include <QDebug>

QExtGraphicsMoveShapeCommand::QExtGraphicsMoveShapeCommand(QGraphicsScene *scene, const QPointF &delta,
                                                           QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_item = QEXT_NULLPTR;
    m_items = scene->selectedItems();
    m_scene = scene;
    m_delta = delta;
    m_moved = true;
}

QExtGraphicsMoveShapeCommand::QExtGraphicsMoveShapeCommand(QGraphicsItem *item, const QPointF &delta,
                                                           QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_scene = QEXT_NULLPTR;
    m_item = item;
    m_delta = delta;
    m_moved = true;
}

void QExtGraphicsMoveShapeCommand::undo()
{
    if (m_item)
    {
        m_item->moveBy(-m_delta.x(), -m_delta.y());
    }
    else if(m_items.count() > 0)
    {
        foreach(QGraphicsItem *item, m_items)
        {
            item->moveBy(-m_delta.x(), -m_delta.y());
        }
    }
    this->setText(QObject::tr("Undo Move %1,%2").arg(-m_delta.x()).arg(-m_delta.y()));
    m_moved = false;
}

void QExtGraphicsMoveShapeCommand::redo()
{
    if (!m_moved)
    {
        if (m_item)
        {
            m_item->moveBy(m_delta.x(), m_delta.y());
            m_item->scene()->update();
        }
        else if(m_items.count() > 0)
        {
            foreach (QGraphicsItem *item, m_items)
            {
                item->moveBy(m_delta.x(), m_delta.y());
            }
            m_scene->update();
        }
    }
    this->setText(QObject::tr("Redo Move %1,%2").arg(m_delta.x()).arg(m_delta.y()));
}


QExtGraphicsRemoveShapeCommand::QExtGraphicsRemoveShapeCommand(QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_scene = scene;
    m_items = m_scene->selectedItems();
}

QExtGraphicsRemoveShapeCommand::~QExtGraphicsRemoveShapeCommand()
{

}

void QExtGraphicsRemoveShapeCommand::undo()
{
    foreach (QGraphicsItem *item, m_items)
    {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if (!group)
        {
            m_scene->addItem(item);
        }
    }
    m_scene->update();
    this->setText(QObject::tr("Undo Delete %1").arg(m_items.count()));
}

void QExtGraphicsRemoveShapeCommand::redo()
{
    foreach (QGraphicsItem *item, m_items)
    {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if (!group)
        {
            m_scene->removeItem(item);
        }
    }
    this->setText(QObject::tr("Redo Delete %1").arg(m_items.count()));
}

QExtGraphicsAddShapeCommand::QExtGraphicsAddShapeCommand(QGraphicsItem *item, QGraphicsScene *scene,
                                                         QUndoCommand *parent)
    : QUndoCommand(parent)
{
    // static int itemCount = 0;
    m_scene = scene;
    m_diagramItem = item;
    m_initPosition = item->pos();
    // ++itemCount;
}

QExtGraphicsAddShapeCommand::~QExtGraphicsAddShapeCommand()
{
    if (!m_diagramItem->scene())
    {
        delete m_diagramItem;
    }
}

void QExtGraphicsAddShapeCommand::undo()
{
    m_scene->removeItem(m_diagramItem);
    m_scene->update();
    this->setText(QObject::tr("Undo Add %1").arg(qextGraphicsCreateCommandString(m_diagramItem, m_initPosition)));
}

void QExtGraphicsAddShapeCommand::redo()
{
    if (!m_diagramItem->scene())
    {
        m_scene->addItem(m_diagramItem);
    }
    m_diagramItem->setPos(m_initPosition);
    m_scene->update();
    this->setText(QObject::tr("Redo Add %1").arg(qextGraphicsCreateCommandString(m_diagramItem, m_initPosition)));
}

QExtGraphicsRotateShapeCommand::QExtGraphicsRotateShapeCommand(QGraphicsItem *item, const qreal oldAngle,
                                                               QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_item = item;
    m_oldAngle = oldAngle;
    m_newAngle = item->rotation();
}

void QExtGraphicsRotateShapeCommand::undo()
{
    m_item->setRotation(m_oldAngle);
    m_item->scene()->update();
    this->setText(QObject::tr("Undo Rotate %1").arg(m_newAngle));
}

void QExtGraphicsRotateShapeCommand::redo()
{
    m_item->setRotation(m_newAngle);
    m_item->update();
    this->setText(QObject::tr("Redo Rotate %1").arg(m_newAngle));
}


QExtGraphicsGroupShapeCommand::QExtGraphicsGroupShapeCommand(QGraphicsItemGroup *group, QGraphicsScene *scene,
                                                             QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_scene = scene;
    m_group = group;
    m_items = group->childItems();
    m_undo = false;
}

void QExtGraphicsGroupShapeCommand::undo()
{
    m_group->setSelected(false);
    QList<QGraphicsItem*> plist = m_group->childItems();
    foreach (QGraphicsItem *item, plist)
    {
        item->setSelected(true);
        m_group->removeFromGroup(item);
    }
    m_scene->removeItem(m_group);
    m_scene->update();
    m_undo = true;
    this->setText(QObject::tr("Undo Group %1").arg(m_items.count()));
}

void QExtGraphicsGroupShapeCommand::redo()
{
    if (m_undo)
    {
        foreach (QGraphicsItem *item, m_items)
        {
            item->setSelected(false);
            QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
            if (!group)
            {
                m_group->addToGroup(item);
            }
        }
    }
    m_group->setSelected(true);
    if (!m_group->scene())
    {
        m_scene->addItem(m_group);
    }
    m_scene->update();
    this->setText(QObject::tr("Redo Group %1").arg(m_items.count()));
}


QExtGraphicsUnGroupShapeCommand::QExtGraphicsUnGroupShapeCommand(QGraphicsItemGroup *group, QGraphicsScene *scene,
                                                                 QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_scene = scene;
    m_group = group;
    m_items = group->childItems();
}

void QExtGraphicsUnGroupShapeCommand::undo()
{
    foreach (QGraphicsItem *item, m_items)
    {
        item->setSelected(false);
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup *>(item->parentItem());
        if (!group)
        {
            m_group->addToGroup(item);
        }
    }
    m_group->setSelected(true);
    if (!m_group->scene())
    {
        m_scene->addItem(m_group);
    }
    m_scene->update();
    this->setText(QObject::tr("Undo UnGroup %1").arg(m_items.count()));
}

void QExtGraphicsUnGroupShapeCommand::redo()
{
    m_group->setSelected(false);
    foreach (QGraphicsItem *item, m_group->childItems())
    {
        item->setSelected(true);
        m_group->removeFromGroup(item);
        QExtGraphicsAbstractShapeItem *shapItem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(item);
        if (shapItem && !qgraphicsitem_cast<QExtGraphicsSizeHandle *>(shapItem))
        {
            shapItem->updateCoordinate();
        }
    }
    m_scene->removeItem(m_group);
    m_scene->update();
    this->setText(QObject::tr("Redo UnGroup %1").arg(m_items.count()));
}


QExtGraphicsResizeShapeCommand::QExtGraphicsResizeShapeCommand(QGraphicsItem *item, int handle, const QPointF &scale,
                                                               QUndoCommand *parent)
{
    m_item = item;
    m_handle = handle;
    m_scale  = QPointF(scale);
    m_opposite = QExtGraphicsSizeHandle::Handle_None;
    m_resized = true;       
}

void QExtGraphicsResizeShapeCommand::undo()
{
    int handle = m_handle;
    QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(m_item);
    if (item)
    {
        if (QExtGraphicsSizeHandle::Handle_None != m_opposite)
        {
            handle = m_opposite;
        }

        item->stretch(handle, 1.0 / m_scale.x(), 1.0 / m_scale.y(), item->opposite(handle));
        item->updateCoordinate();
        item->update();
    }
    m_resized = false;
    this->setText(QObject::tr("Undo Resize %1,%2 ,handle:%3").
                  arg(1.0 / m_scale.x(), 8, 'f', 2).arg(1.0 / m_scale.y(), 8, 'f', 2).arg(handle));
}

void QExtGraphicsResizeShapeCommand::redo()
{
    int handle = m_handle;
    if (!m_resized)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(m_item);
        if (item)
        {
            item->stretch(handle, m_scale.x(), m_scale.y(), item->opposite(handle));
            item->updateCoordinate();
            item->update();
        }
    }
    this->setText(QObject::tr("Redo Resize %1,%2 ,handle:%3").
                  arg(m_scale.x(), 8, 'f', 2).arg(m_scale.y(), 8, 'f', 2).arg(handle));
}
bool QExtGraphicsResizeShapeCommand::mergeWith(const QUndoCommand *command)
{
    if (command->id() != QExtGraphicsResizeShapeCommand::Id)
    {
        return false;
    }

    const QExtGraphicsResizeShapeCommand *cmd = static_cast<const QExtGraphicsResizeShapeCommand *>(command);

    QGraphicsItem *item = cmd->m_item;
    if (m_item != item)
    {
        return false;
    }

    if (cmd->m_handle != m_handle)
    {
        return false;
    }

    QExtGraphicsAbstractShapeItem *shapItem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(item);

    m_opposite = shapItem->swapHandle(cmd->m_handle, cmd->m_scale);
    m_handle = cmd->m_handle;
    m_scale = cmd->m_scale;
    this->setText(QObject::tr(" mergeWith Resize %1,%2,%3,%4").
                  arg(m_scale.x(), 8, 'f', 2).arg(m_scale.y(), 8, 'f', 2).arg(m_handle).arg(m_opposite));
    return true;
}

QExtGraphicsControlShapeCommand::QExtGraphicsControlShapeCommand(QGraphicsItem *item, int handle, const QPointF &newPos,
                                                                 const QPointF &lastPos, QUndoCommand *parent)
{
    m_item = item;
    m_handle = handle;
    m_lastPos  = QPointF(lastPos);
    m_newPos = QPointF(newPos);
    m_controled = true;
}

void QExtGraphicsControlShapeCommand::undo()
{
    QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(m_item);
    if (item)
    {
        item->control(m_handle, m_lastPos);
        item->updateCoordinate();
        item->update();
    }
    m_controled = false;
    this->setText(QObject::tr("Undo Control %1,%2") .arg(m_lastPos.x()).arg(m_lastPos.y()));
}

void QExtGraphicsControlShapeCommand::redo()
{
    if (!m_controled)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(m_item);
        if (item)
        {
            item->control(m_handle, m_newPos);
            item->updateCoordinate();
            item->update();
        }
    }
    this->setText(QObject::tr("Redo Control %1,%2").arg(m_newPos.x()).arg(m_newPos.y()));
}

bool QExtGraphicsControlShapeCommand::mergeWith(const QUndoCommand *command)
{
    if (command->id() != QExtGraphicsControlShapeCommand::Id)
    {
        return false;
    }

    const QExtGraphicsControlShapeCommand *cmd = static_cast<const QExtGraphicsControlShapeCommand *>(command);
    QGraphicsItem *item = cmd->m_item;

    if (m_item != item)
    {
        return false;
    }
    if (cmd->m_handle != m_handle)
    {
        return false;
    }
    m_handle = cmd->m_handle;
    m_lastPos = cmd->m_lastPos;
    m_newPos  = cmd->m_newPos;
    this->setText(QObject::tr(" mergeWith Control %1,%2,%3").arg(m_newPos.x()).arg(m_newPos.y()).arg(m_handle));
    return true;
}

QString qextGraphicsCreateCommandString(QGraphicsItem *item, const QPointF &pos)
{
    return QObject::tr("Item at (%1, %2)").arg(pos.x()).arg(pos.y());
}
