// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmVectorItem.h>
#include <qextMvvmItemMapper.h>
#include <sstream>

using namespace ModelView;

QExtMvvmVectorItem::QExtMvvmVectorItem() : QExtMvvmCompoundItem(Constants::VectorItemType)
{
    addProperty(P_X, 0.0)->setDisplayName("X");
    addProperty(P_Y, 0.0)->setDisplayName("Y");
    addProperty(P_Z, 0.0)->setDisplayName("Z");

    setEditable(false);

    update_label();
}

void QExtMvvmVectorItem::activate()
{
    auto on_property_change = [this](QExtMvvmSessionItem*, const std::string&) { update_label(); };
    mapper()->setOnPropertyChange(on_property_change, this);
}

double QExtMvvmVectorItem::x() const
{
    return property<double>(P_X);
}

void QExtMvvmVectorItem::setX(double value)
{
    setProperty(P_X, value);
}

double QExtMvvmVectorItem::y() const
{
    return property<double>(P_Y);
}

void QExtMvvmVectorItem::setY(double value)
{
    setProperty(P_Y, value);
}

double QExtMvvmVectorItem::z() const
{
    return property<double>(P_Z);
}

void QExtMvvmVectorItem::setZ(double value)
{
    setProperty(P_Z, value);
}

void QExtMvvmVectorItem::update_label()
{
    std::ostringstream ostr;
    ostr << "(" << x() << ", " << y() << ", " << z() << ")";
    setData(QVariant::fromValue(ostr.str()), ItemDataRole::DATA, /*direct*/ true);
}
