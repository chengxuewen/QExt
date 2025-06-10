#include <private/qextPlot_p.h>
#include <qextPlotConstants.h>
#include <qextStringUtils.h>

QExtPlotPrivate::QExtPlotPrivate(QExtPlot *q)
    : q_ptr(q)
{
}

QExtPlotPrivate::~QExtPlotPrivate()
{
}

QExtPlot::QExtPlot(QWidget *parent)
    : QwtPlot(parent)
    , dd_ptr(new QExtPlotPrivate(this))
{
}

QExtPlot::QExtPlot(QExtPlotPrivate *d, QWidget *parent)
    : QwtPlot(parent)
    , dd_ptr(d)
{
}

QExtPlot::QExtPlot(const QwtText &title, QWidget *parent)
    : QwtPlot(title, parent)
    , dd_ptr(new QExtPlotPrivate(this))
{
}

QExtPlot::~QExtPlot()
{
}

void QExtPlot::serializeLoad(const SerializedItems &items)
{
    this->setVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_VISIBLE, true).toBool());
    this->setTitle(QEXT_FROM_UNICODES_STRING(items.value(QExtPlotConstants::PLOT_PROPERTY_TITLE, "").toString()));
}

QExtSerializable::SerializedItems QExtPlot::serializeSave() const
{
    QExtSerializable::SerializedItems items;
    items[QExtPlotConstants::PLOT_PROPERTY_VISIBLE] = this->isVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_TITLE] = QEXT_TO_UNICODES_STRING(this->title().text());
    return items;
}
