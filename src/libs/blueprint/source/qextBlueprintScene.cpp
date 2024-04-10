#include <private/qextBlueprintScene_p.h>

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <vector>

QExtBlueprintScenePrivate::QExtBlueprintScenePrivate(QExtBlueprintScene *q)
    : q_ptr(q)
    , m_view(QEXT_NULLPTR)
{

}

QExtBlueprintScenePrivate::~QExtBlueprintScenePrivate()
{

}



QExtBlueprintScene::QExtBlueprintScene(QObject *parent)
    : QGraphicsScene(parent)
    , dd_ptr(new QExtBlueprintScenePrivate(this))
{

}

QExtBlueprintScene::~QExtBlueprintScene()
{
}

QGraphicsView *QExtBlueprintScene::view() const
{
    Q_D(const QExtBlueprintScene);
    return d->m_view;
}

void QExtBlueprintScene::setView(QGraphicsView *view)
{
    Q_D(QExtBlueprintScene);
    d->m_view = view;
}

void QExtBlueprintScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
}

void QExtBlueprintScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void QExtBlueprintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void QExtBlueprintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void QExtBlueprintScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvet)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvet);
}

void QExtBlueprintScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
}

void QExtBlueprintScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

