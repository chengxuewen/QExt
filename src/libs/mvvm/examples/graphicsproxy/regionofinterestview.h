// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
#define GRAPHICSPROXY_REGIONOFINTERESTVIEW_H

#include <qextGlobal.h>

#include <QGraphicsItem>
#include <QScopedPointer>
#include <QVector>



class QEXTMvvmSceneAdapterInterface;


class RegionOfInterestItem;
class RegionOfInterestController;
class SizeHandleElement;

//! Graphics object to represent RegionOfInterestItem on graphics scene.
//! Follows standard QGraphicsScene notations: (x,y) origin is top left corner.

class RegionOfInterestView : public QGraphicsItem
{
public:
    RegionOfInterestView(RegionOfInterestItem* item,
                         const QEXTMvvmSceneAdapterInterface* scene_adapter);
    ~RegionOfInterestView() QEXT_DECL_OVERRIDE;

    QRectF boundingRect() const QEXT_DECL_OVERRIDE;

    void advance(int phase) QEXT_DECL_OVERRIDE;

    void setActiveHandle(SizeHandleElement* element);

    void update_geometry();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) QEXT_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) QEXT_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) QEXT_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) QEXT_DECL_OVERRIDE;

private:
    void create_size_handle_elements();
    SizeHandleElement* findOpposite(SizeHandleElement* element);
    QScopedPointer<RegionOfInterestController> controller;
    QVector<SizeHandleElement*> handles;
    SizeHandleElement* active_handle{nullptr}; //!
    QPointF opposite_origin; //! coordinate of opposite corner at the moment of click
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTVIEW_H
