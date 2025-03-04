// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/plotting/axistitlecontroller.h"
#include "model/standarditems/plottableitems.h"
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmAxisTitleController::AxisTitleControllerImpl {
    QCPAxis* m_axis{nullptr};

    AxisTitleControllerImpl(QCPAxis* axis) : m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("QExtMvvmAxisTitleController: axis is not initialized.");
    }

    void updateAxisFromItem(QExtMvvmTextItem* item)
    {
        auto font = m_axis->labelFont();
        font.setPointSize(item->property<int>(QExtMvvmTextItem::P_SIZE));
        font.setFamily(QString::fromStdString(item->property<std::string>(QExtMvvmTextItem::P_FONT)));
        m_axis->setLabel(QString::fromStdString(item->property<std::string>(QExtMvvmTextItem::P_TEXT)));
        m_axis->setLabelFont(font);

        m_axis->parentPlot()->replot();
    }
};

QExtMvvmAxisTitleController::QExtMvvmAxisTitleController(QCPAxis* axis)
    : p_impl(qextMakeUnique<AxisTitleControllerImpl>(axis))

{
}

QExtMvvmAxisTitleController::~QExtMvvmAxisTitleController() = default;

void QExtMvvmAxisTitleController::subscribe()
{
    auto on_property_change = [this](QExtMvvmSessionItem*, std::string) { p_impl->updateAxisFromItem(currentItem()); };
    setOnPropertyChange(on_property_change);

    p_impl->updateAxisFromItem(currentItem());
}
