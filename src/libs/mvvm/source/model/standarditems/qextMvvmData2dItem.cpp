// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmAxisItems.h>
#include <qextMvvmData2dItem.h>
#include <stdexcept>



namespace
{
size_t total_bin_count(QEXTMvvmData2DItem* item)
{
    if (auto xaxis = item->xAxis(); xaxis)
        if (auto yaxis = item->yAxis(); yaxis)
            return static_cast<size_t>(xaxis->size() * yaxis->size());
    return 0;
}
} // namespace

QEXTMvvmData2DItem::QEXTMvvmData2DItem() : QEXTMvvmCompoundItem(QEXTMvvmConstants::Data2DItemType)
{
    registerTag(QEXTMvvmTagInfo(T_XAXIS, 0, 1, {QEXTMvvmConstants::FixedBinAxisItemType}));
    registerTag(QEXTMvvmTagInfo(T_YAXIS, 0, 1, {QEXTMvvmConstants::FixedBinAxisItemType}));
    setContent(QVector<double>()); // prevent editing in widgets, since there is no
                                       // corresponding editor
}

//! Sets axes and put data points to zero.

void QEXTMvvmData2DItem::setAxes(QEXTMvvmBinnedAxisItem *xAxis,
                         QEXTMvvmBinnedAxisItem *yAxis)
{
    insertAxis(xAxis, T_XAXIS);
    insertAxis(yAxis, T_YAXIS);
    setContent(QVector<double>(total_bin_count(this), 0.0));
}

//! Returns x-axis (nullptr if it doesn't exist).

QEXTMvvmBinnedAxisItem* QEXTMvvmData2DItem::xAxis() const
{
    return item<QEXTMvvmBinnedAxisItem>(T_XAXIS);
}

//! Returns y-axis (nullptr if it doesn't exist).

QEXTMvvmBinnedAxisItem* QEXTMvvmData2DItem::yAxis() const
{
    return item<QEXTMvvmBinnedAxisItem>(T_YAXIS);
}

void QEXTMvvmData2DItem::setContent(const QVector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("QEXTMvvmData1DItem::setContent() -> Data doesn't match size of axis");

    setData(data);
}

//! Returns 2d vector representing 2d data.

QVector<double> QEXTMvvmData2DItem::content() const
{
    return this->data<QVector<double>>();
}

//! Insert axis under given tag. Previous axis will be deleted and data points invalidated.

void QEXTMvvmData2DItem::insertAxis(QEXTMvvmBinnedAxisItem *axis, const QString &tag)
{
    // removing previous axis
    if (auto axis = item(tag, 0))
        delete takeItem({tag, 0});

    insertItem(axis, {tag, 0});
}
