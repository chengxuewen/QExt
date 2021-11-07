#include "qcustomplot.h"
#include <QObject>
#include <qextMvvmAxisTitleController.h>
#include <qextMvvmCustomPlotUtils.h>
#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmPlotTableItems.h>
#include <stdexcept>



struct QEXTMvvmViewportAxisPlotController::AxesPlotControllerImpl {

    QEXTMvvmViewportAxisPlotController* m_self{nullptr};
    QCPAxis* m_axis{nullptr};
    bool m_blockUpdate{false};
    QScopedPointer<QMetaObject::Connection> m_axisConn;
    QScopedPointer<QEXTMvvmAxisTitleController> m_titleController;

    AxesPlotControllerImpl(QEXTMvvmViewportAxisPlotController* controller, QCPAxis* axis)
        : m_self(controller), m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("AxisPlotController: axis is not initialized.");
        m_axisConn.reset(new QMetaObject::Connection);
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

    //! Sets axesRange from QEXTMvvmItem.
    void setAxisRangeFromItem()
    {
        auto [lower, upper] = m_self->currentItem()->range();
        m_axis->setRange(QCPRange(lower, upper));
    }

    //! Sets log scale from item.

    void setAxisLogScaleFromItem()
    {
        QEXTMvvmCustomPlotUtils::SetLogarithmicScale(m_axis, m_self->currentItem()->is_in_log());
    }

    //! Init axis from item and setup connections.

    void init_axis()
    {
        m_titleController.reset(new QEXTMvvmAxisTitleController(m_axis));
        auto text_item = m_self->currentItem()->item<QEXTMvvmTextItem>(QEXTMvvmViewportAxisItem::P_TITLE);
        m_titleController->setItem(text_item);
        setAxisRangeFromItem();
        setAxisLogScaleFromItem();
        setConnected();
    }

    void updateLowerRange(const QEXTMvvmViewportAxisItem* item)
    {
        setDisconnected();
        m_axis->setRangeLower(item->property<double>(QEXTMvvmViewportAxisItem::P_MIN));
        setConnected();
    }

    void updateUpperRange(const QEXTMvvmViewportAxisItem* item)
    {
        setDisconnected();
        m_axis->setRangeUpper(item->property<double>(QEXTMvvmViewportAxisItem::P_MAX));
        setConnected();
    }

    ~AxesPlotControllerImpl() { setDisconnected(); }
};

QEXTMvvmViewportAxisPlotController::QEXTMvvmViewportAxisPlotController(QCPAxis* axis)
    : p_impl(new AxesPlotControllerImpl(this, axis))

{
}

QEXTMvvmViewportAxisPlotController::~QEXTMvvmViewportAxisPlotController() = default;

void QEXTMvvmViewportAxisPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmItem*, QString name) {
        if (p_impl->m_blockUpdate)
            return;

        if (name == QEXTMvvmViewportAxisItem::P_MIN)
            p_impl->updateLowerRange(currentItem());

        if (name == QEXTMvvmViewportAxisItem::P_MAX)
            p_impl->updateUpperRange(currentItem());

        if (name == QEXTMvvmViewportAxisItem::P_IS_LOG)
            p_impl->setAxisLogScaleFromItem();

        p_impl->m_axis->parentPlot()->replot();
    };
    addItemPropertyChangedListener(on_property_change);

    p_impl->init_axis();
}

void QEXTMvvmViewportAxisPlotController::unsubscribe()
{
    p_impl->setDisconnected();
}
