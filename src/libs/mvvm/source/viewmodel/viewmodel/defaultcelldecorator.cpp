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
#include <editors/editor_constants.h>
#include <editors/scientificspinbox.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <viewmodel/defaultcelldecorator.h>

using namespace ModelView;

bool DefaultCellDecorator::hasCustomDecoration(const QModelIndex& index) const
{
    return cellText(index).has_value();
}

std::optional<std::string> DefaultCellDecorator::cellText(const QModelIndex& index) const
{
    auto variant = index.data();

    if (Utils::IsComboVariant(variant))
        return std::optional<std::string>{variant.value<QEXTMvvmComboProperty>().label()};

    else if (Utils::IsBoolVariant(variant))
        return variant.value<bool>() ? std::optional<std::string>{"True"}
                                     : std::optional<std::string>{"False"};

    else if (Utils::IsExtPropertyVariant(variant))
        return std::optional<std::string>{variant.value<QEXTMvvmExternalProperty>().text()};

    else if (Utils::IsColorVariant(variant))
        return std::optional<std::string>{std::string()};

    else if (Utils::IsDoubleVariant(variant))
        return std::optional<std::string>{
            ScientificSpinBox::toString(index.data(Qt::EditRole).value<double>(),
                                        Constants::default_double_decimals)
                .toStdString()};

    return {};
}

void DefaultCellDecorator::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)
{
    if (!hasCustomDecoration(index))
        return;

    auto value = cellText(index).value();
    option->text = QString::fromStdString(value);
    if (value.empty())
        option->features &= ~QStyleOptionViewItem::HasDisplay;
}
