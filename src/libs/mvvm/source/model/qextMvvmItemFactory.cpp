#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItem.h>


QEXTMvvmItemFactory::QEXTMvvmItemFactory(QEXTMvvmItemCatalogue *catalogue)
    : m_catalogue(catalogue)
{
}

QEXTMvvmItemFactory::~QEXTMvvmItemFactory()
{

}

QEXTMvvmItem *QEXTMvvmItemFactory::createItem(const QString &modelType) const
{
    return m_catalogue->create(modelType);
}

QEXTMvvmItem *QEXTMvvmItemFactory::createEmptyItem() const
{
    return new QEXTMvvmItem;
}
