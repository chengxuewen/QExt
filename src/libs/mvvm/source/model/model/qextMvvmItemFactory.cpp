// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmSessionItem.h>

using namespace ModelView;

QEXTMvvmItemFactory::QEXTMvvmItemFactory(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

QEXTMvvmItemFactory::~QEXTMvvmItemFactory() = default;

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemFactory::createItem(const model_type& modelType) const
{
    return m_catalogue->create(modelType);
}

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemFactory::createEmptyItem() const
{
    return make_unique<QEXTMvvmSessionItem>();
}
