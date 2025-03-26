// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisTitleController.h>
#include <qextMvvmCustomPlotUtils.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmPlotTableItems.h>
#include <qcustomplot.h>
#include <QObject>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmViewportAxisPlotController::AxesPlotControllerImpl {

    QExtMvvmViewportAxisPlotController* m_self{nullptr};
    QCPAxis* m_axis{nullptr};
    bool m_blockUpdate{false};
    QExtUniquePointer<QMetaObject::Connection> m_axisConn;
    QExtUniquePointer<QExtMvvmAxisTitleController> m_titleController;

    AxesPlotControllerImpl(QExtMvvmViewportAxisPlotController* controller, QCPAxis* axis)
        : m_self(controller), m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("AxisPlotController: axis is not initialized.");
        m_axisConn = qextMakeUnique<QMetaObject::Connection>();
    }

    //! Connects QCustomPlot signals with controller methods.
    void setConnected()
    {
        auto on_axis_range = [this](const QCPRange& newRange) {
            m_blockUpdate = true;
            auto item = m_self->currentItem();
            item->set_range(newRange.lower, newRange.upper);
            m_blockUpdate = false;
        };

        *m_axisConn = QObject::connect(
            m_axis, static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            on_axis_range);
    }

    //! Disonnects QCustomPlot signals.

    void setDisconnected() { QObject::disconnect(*m_axisConn); }

    //! Sets axesRange from QExtMvvmSessionItem.
    void setAxisRangeFromItem()
    {
        auto range = m_self->currentItem()->range();
        m_axis->setRange(QCPRange(range.first, range.second));
    }

    //! Sets log scale from item.

    void setAxisLogScaleFromItem()
    {
        Utils::SetLogarithmicScale(m_axis, m_self->currentItem()->is_in_log());
    }

    //! Init axis from item and setup connections.

    void init_axis()
    {
        m_titleController = qextMakeUnique<QExtMvvmAxisTitleController>(m_axis);
        auto text_item = m_self->currentItem()->item<QExtMvvmTextItem>(QExtMvvmViewportAxisItem::P_TITLE);
        m_titleController->setItem(text_item);
        setAxisRangeFromItem();
        setAxisLogScaleFromItem();
        setConnected();
    }

    void updateLowerRange(const QExtMvvmViewportAxisItem* item)
    {
        setDisconnected();
        m_axis->setRangeLower(item->property<double>(QExtMvvmViewportAxisItem::P_MIN));
        setConnected();
    }

    void updateUpperRange(const QExtMvvmViewportAxisItem* item)
    {
        setDisconnected();
        m_axis->setRangeUpper(item->property<double>(QExtMvvmViewportAxisItem::P_MAX));
        setConnected();
    }

    ~AxesPlotControllerImpl() { setDisconnected(); }
};

QExtMvvmViewportAxisPlotController::QExtMvvmViewportAxisPlotController(QCPAxis* axis)
    : p_impl(qextMakeUnique<AxesPlotControllerImpl>(this, axis))

{
}

QExtMvvmViewportAxisPlotController::~QExtMvvmViewportAxisPlotController() = default;

void QExtMvvmViewportAxisPlotController::subscribe()
{
    auto on_property_change = [this](QExtMvvmSessionItem*, std::string name) {
        if (p_impl->m_blockUpdate)
            return;

        if (name == QExtMvvmViewportAxisItem::P_MIN)
            p_impl->updateLowerRange(currentItem());

        if (name == QExtMvvmViewportAxisItem::P_MAX)
            p_impl->updateUpperRange(currentItem());

        if (name == QExtMvvmViewportAxisItem::P_IS_LOG)
            p_impl->setAxisLogScaleFromItem();

        p_impl->m_axis->parentPlot()->replot();
    };
    setOnPropertyChange(on_property_change);

    p_impl->init_axis();
}

void QExtMvvmViewportAxisPlotController::unsubscribe()
{
    p_impl->setDisconnected();
}
