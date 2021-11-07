#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmScientificSpinbox.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmUtils.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmDefaultCellDecorator.h>



bool QEXTMvvmDefaultCellDecorator::hasCustomDecoration(const QModelIndex& index) const
{
    return this->cellText(index).isEmpty();
}

QString QEXTMvvmDefaultCellDecorator::cellText(const QModelIndex &index) const
{
    auto variant = index.data();

    if (QEXTMvvmUtils::IsComboVariant(variant))
        return variant.value<QEXTMvvmComboProperty>().label();

    else if (QEXTMvvmUtils::IsBoolVariant(variant))
        return variant.value<bool>() ? "True" : "False";

    else if (QEXTMvvmUtils::IsExtPropertyVariant(variant))
        return variant.value<QEXTMvvmExternalProperty>().text();

    else if (QEXTMvvmUtils::IsColorVariant(variant))
        return QString();

    else if (QEXTMvvmUtils::IsDoubleVariant(variant))
        return QEXTMvvmScientificSpinBox::toString(index.data(Qt::EditRole).value<double>(), QEXTMvvmConstants::default_double_decimals);

    return {};
}

void QEXTMvvmDefaultCellDecorator::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)
{
    if (this->hasCustomDecoration(index))
    {
        QString value = this->cellText(index);
        option->text = value;
        if (value.isEmpty())
        {
            option->features &= ~QStyleOptionViewItem::HasDisplay;
        }
    }
}
