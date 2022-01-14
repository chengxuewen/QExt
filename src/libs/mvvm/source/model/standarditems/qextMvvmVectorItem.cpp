// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomVariants.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmVectorItem.h>
#include <sstream>

using namespace ModelView;

QEXTMvvmVectorItem::QEXTMvvmVectorItem() : QEXTMvvmCompoundItem(QEXTMvvmConstants::VectorItemType)
{
    addProperty(P_X, 0.0)->setDisplayName("X");
    addProperty(P_Y, 0.0)->setDisplayName("Y");
    addProperty(P_Z, 0.0)->setDisplayName("Z");

    setEditable(false);

    update_label();
}

void QEXTMvvmVectorItem::activate()
{
    auto on_property_change = [this](QEXTMvvmSessionItem*, const std::string&) { update_label(); };
    mapper()->setOnPropertyChange(on_property_change, this);
}

void QEXTMvvmVectorItem::update_label()
{
    std::ostringstream ostr;
    ostr << "(" << property<double>(P_X) << ", " << property<double>(P_Y) << ", "
         << property<double>(P_Z) << ")";
    setDataIntern(QVariant::fromValue(ostr.str()), ItemDataRole::DATA);
}
