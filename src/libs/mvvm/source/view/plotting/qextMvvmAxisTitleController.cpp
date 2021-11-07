#include "qcustomplot.h"
#include <qextMvvmAxisTitleController.h>
#include <qextMvvmPlotTableItems.h>
#include <stdexcept>



struct QEXTMvvmAxisTitleController::AxisTitleControllerImpl {
    QCPAxis* m_axis{nullptr};

    AxisTitleControllerImpl(QCPAxis* axis) : m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("QEXTMvvmAxisTitleController: axis is not initialized.");
    }

    void updateAxisFromItem(QEXTMvvmTextItem* item)
    {
        auto font = m_axis->labelFont();
        font.setPointSize(item->property<int>(QEXTMvvmTextItem::P_SIZE));
        font.setFamily(item->property<QString>(QEXTMvvmTextItem::P_FONT));
        m_axis->setLabel(item->property<QString>(QEXTMvvmTextItem::P_TEXT));
        m_axis->setLabelFont(font);

        m_axis->parentPlot()->replot();
    }
};

QEXTMvvmAxisTitleController::QEXTMvvmAxisTitleController(QCPAxis* axis)
    : p_impl(new AxisTitleControllerImpl(axis))
{
}

QEXTMvvmAxisTitleController::~QEXTMvvmAxisTitleController()
{

}

void QEXTMvvmAxisTitleController::subscribe()
{
    auto on_property_change = [this](auto, auto) { p_impl->updateAxisFromItem(currentItem()); };
    this->addItemPropertyChangedListener(on_property_change);

    p_impl->updateAxisFromItem(currentItem());
}
