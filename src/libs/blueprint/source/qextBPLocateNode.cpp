#include <qextBPLocateNode.h>
#include <qextBPNodeGraphicsObject.h>

#include <QtCore/QList>
#include <QtWidgets/QGraphicsScene>

#include <vector>

QExtBPNodeGraphicsObject *locateNodeAt(QPointF scenePoint,
                                       QGraphicsScene &scene,
                                       QTransform const &viewTransform)
{
    // items under cursor
    QList<QGraphicsItem *> items = scene.items(scenePoint,
                                               Qt::IntersectsItemShape,
                                               Qt::DescendingOrder,
                                               viewTransform);

    // items convertable to NodeGraphicsObject
    std::vector<QGraphicsItem *> filteredItems;

    std::copy_if(items.begin(),
                 items.end(),
                 std::back_inserter(filteredItems),
                 [](QGraphicsItem *item) {
        return (qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item) != QEXT_NULLPTR);
    });

    QExtBPNodeGraphicsObject *node = QEXT_NULLPTR;

    if (!filteredItems.empty()) {
        QGraphicsItem *graphicsItem = filteredItems.front();
        node = dynamic_cast<QExtBPNodeGraphicsObject *>(graphicsItem);
    }

    return node;
}
