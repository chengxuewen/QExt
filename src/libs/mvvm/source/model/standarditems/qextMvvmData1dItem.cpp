// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmAxisItems.h>
#include <qextMvvmData1dItem.h>
#include <stdexcept>



namespace
{
size_t total_bin_count(QEXTMvvmData1DItem* item)
{
    auto axis = item->item<QEXTMvvmBinnedAxisItem>(QEXTMvvmData1DItem::T_AXIS);
    return axis ? static_cast<size_t>(axis->size()) : 0;
}
} // namespace

QEXTMvvmData1DItem::QEXTMvvmData1DItem() : QEXTMvvmCompoundItem(QEXTMvvmConstants::Data1DItemType)
{
    // prevent editing in widgets, since there is no corresponding editor
    addProperty(P_VALUES, QVector<double>())->setDisplayName("Values")->setEditable(false);

    addProperty(P_ERRORS, QVector<double>())->setDisplayName("Errors")->setEditable(false);

    registerTag(
        QEXTMvvmTagInfo(T_AXIS, 0, 1, {QEXTMvvmConstants::FixedBinAxisItemType, QEXTMvvmConstants::PointwiseAxisItemType}),
        true);
    setValues(QVector<double>());
}

void QEXTMvvmData1DItem::setAxis(QEXTMvvmBinnedAxisItem *axis)
{
    // we disable possibility to re-create axis to facilitate undo/redo

    if (this->item(T_AXIS, 0))
        throw std::runtime_error("Axis was already set. Currently we do not support axis change");

    insertItem(axis, {T_AXIS, 0});
    setValues(QVector<double>(total_bin_count(this), 0.0));
}

//! Returns coordinates of bin centers.

QVector<double> QEXTMvvmData1DItem::binCenters() const
{
    auto axis = item<QEXTMvvmBinnedAxisItem>(T_AXIS);
    return axis ? axis->binCenters() : QVector<double>{};
}

//! Sets internal data buffer to given data. If size of axis doesn't match the size of the data,
//! exception will be thrown.

void QEXTMvvmData1DItem::setValues(const QVector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("QEXTMvvmData1DItem::setValues() -> Data doesn't match size of axis");

    setProperty(P_VALUES, data);
}

//! Returns values stored in bins.

QVector<double> QEXTMvvmData1DItem::binValues() const
{
    return property<QVector<double>>(P_VALUES);
}

//! Sets errors on values in bins.

void QEXTMvvmData1DItem::setErrors(const QVector<double>& errors)
{
    if (total_bin_count(this) != errors.size())
        throw std::runtime_error("QEXTMvvmData1DItem::setErrors() -> Data doesn't match size of axis");

    setProperty(P_ERRORS, errors);
}

//! Returns value errors stored in bins.

QVector<double> QEXTMvvmData1DItem::binErrors() const
{
    return property<QVector<double>>(P_ERRORS);
}
