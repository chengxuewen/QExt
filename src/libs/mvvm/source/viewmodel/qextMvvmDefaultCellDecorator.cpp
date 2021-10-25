#include <qextMvvmDefaultCellDecorator.h>
#include <qextMvvmScientificSpinBox.h>
#include <qextMvvmConstants.h>

#include <cfMvvmComboProperty.h>
#include <cfMvvmExternalProperty.h>

CF_USE_NAMESPACE

Q_DECLARE_METATYPE(CFMvvmComboProperty)
Q_DECLARE_METATYPE(CFMvvmExternalProperty)

bool QEXTMvvmDefaultCellDecorator::hasCustomDecoration(const QModelIndex &index) const
{
    return this->cellText(index).empty();
}

void QEXTMvvmDefaultCellDecorator::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index)
{
    if (!this->hasCustomDecoration(index))
    {
        return;
    }

    std::string value = this->cellText(index);
//    option->text = QString::fromStdString(value);
    if (value.empty())
    {
//        option->features &= ~QStyleOptionViewItem::HasDisplay;
    }
}

std::string QEXTMvvmDefaultCellDecorator::cellText(const QModelIndex &index) const
{
    QVariant variant = index.data();

    if (variant.canConvert<CFMvvmComboProperty>())
    {
        return variant.value<CFMvvmComboProperty>().label();
    }
    else if (variant.canConvert<CFMvvmExternalProperty>())
    {
        return variant.value<CFMvvmExternalProperty>().text();
    }
    else if (variant.type() == QVariant::Bool)
    {
        return variant.value<bool>() ? std::string("True") : std::string("False");
    }
    else if (variant.type() == QVariant::Color)
    {
        return std::string();
    }
    else if (variant.type() == QVariant::Double)
    {
        return QEXTMvvmScientificSpinBox::toString(index.data(Qt::EditRole).value<double>(), QEXTMvvmConstants::default_double_decimals).toStdString();
    };

    return std::string();
}
