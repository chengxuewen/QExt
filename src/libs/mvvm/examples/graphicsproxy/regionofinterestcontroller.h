// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H
#define GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H

#include <qextMvvmItemListener.h>

#include <QScopedPointer>

class QEXTMvvmSceneAdapterInterface;


class RegionOfInterestItem;
class RegionOfInterestView;
class QRectF;

//! Establishes communications between RegionOfInterestItem and RegionOfInterestView.
//! Provides updates of view position/appearance on graphics scene, when underlying item changes.
//! Similarly, provides update of item's properties when view is moved/resized by the user.

class RegionOfInterestController : public QEXTMvvmItemListener<RegionOfInterestItem>
{
public:
    RegionOfInterestController(RegionOfInterestItem* item,
                               const QEXTMvvmSceneAdapterInterface* scene_adapter,
                               RegionOfInterestView* view);
    ~RegionOfInterestController() QEXT_DECL_OVERRIDE;

    QRectF roi_rectangle() const;

    void update_view_from_item();

    void update_item_from_view();

    void update_item_from_corner(double left, double right, double top, double bottom);

    void update_item_from_vertical_handle(double top, double bottom);

    void update_item_from_horizontal_handle(double left, double right);

protected:
    void subscribe() QEXT_DECL_OVERRIDE;

private:
    struct RegionOfInterestControllerImpl;
    QScopedPointer<RegionOfInterestControllerImpl> p_impl;
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H
