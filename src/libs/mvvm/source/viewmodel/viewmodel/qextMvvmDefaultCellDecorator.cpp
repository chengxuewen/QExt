// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmScientificSpinBox.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <viewmodel/qextMvvmDefaultCellDecorator.h>

using namespace ModelView;

bool QEXTMvvmDefaultCellDecorator::hasCustomDecoration(const QModelIndex& index) const
{
    return cellText(index).isValid();
}

QVariant QEXTMvvmDefaultCellDecorator::cellText(const QModelIndex& index) const
{
    auto variant = index.data();

    if (QEXTMvvmUtils::IsComboVariant(variant))
        return QString::fromStdString(variant.value<QEXTMvvmComboProperty>().label());

    else if (QEXTMvvmUtils::IsBoolVariant(variant))
        return variant.toBool() ? "TRUE" : "FALSE";

    else if (QEXTMvvmUtils::IsExtPropertyVariant(variant))
        return QString::fromStdString(variant.value<QEXTMvvmExternalProperty>().text());

    else if (QEXTMvvmUtils::IsColorVariant(variant))
        return QString("");

    else if (QEXTMvvmUtils::IsDoubleVariant(variant))
        return QEXTMvvmScientificSpinBox::toString(index.data(Qt::EditRole).value<double>(),
                                                   QEXTMvvmConstants::default_double_decimals);

    return {};
}

void QEXTMvvmDefaultCellDecorator::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)
{
    if (!hasCustomDecoration(index))
        return;

    auto value = cellText(index);
    option->text = value.toString();
    if (!value.isValid())
    {
        option->features &= ~QStyleOptionViewItem::HasDisplay;
    }
}
