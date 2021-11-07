// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmUtils.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmVectorItem.h>
#include <sstream>



QEXTMvvmVectorItem::QEXTMvvmVectorItem()
    : QEXTMvvmCompoundItem(QEXTMvvmConstants::VectorItemType)
{
    this->addProperty(P_X, 0.0)->setDisplayName("X");
    this->addProperty(P_Y, 0.0)->setDisplayName("Y");
    this->addProperty(P_Z, 0.0)->setDisplayName("Z");

    this->setEditable(false);

    this->updateLabel();
}

void QEXTMvvmVectorItem::activate()
{
    QEXTMvvmItemPropertyFunction function(this, &QEXTMvvmVectorItem::onPropertyChanged);
    this->mapper()->addItemPropertyChangedListener(function, this);
}

void QEXTMvvmVectorItem::onPropertyChanged(QEXTMvvmItem *, QString)
{
    this->updateLabel();
}

void QEXTMvvmVectorItem::updateLabel()
{
    std::ostringstream ostr;
    ostr << "(" << property<double>(P_X) << ", " << property<double>(P_Y) << ", "
         << property<double>(P_Z) << ")";
    setDataIntern(QVariant::fromValue(QString::fromStdString(ostr.str())), QEXTMvvmItem::Role_Data);
}
