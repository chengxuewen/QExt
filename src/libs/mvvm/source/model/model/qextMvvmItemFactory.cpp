#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmSessionItem.h>

using namespace ModelView;

QEXTMvvmItemFactory::QEXTMvvmItemFactory(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

QEXTMvvmItemFactory::~QEXTMvvmItemFactory() = default;

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemFactory::createItem(const QEXTMvvmModelType& modelType) const
{
    return m_catalogue->create(modelType);
}

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemFactory::createEmptyItem() const
{
    return std::make_unique<QEXTMvvmSessionItem>();
}
