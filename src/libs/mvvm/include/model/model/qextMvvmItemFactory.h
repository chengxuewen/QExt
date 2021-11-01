#ifndef _QEXTMVVMITEMFACTORY_H
#define _QEXTMVVMITEMFACTORY_H

#include <memory>
#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmItemCatalogue;

//! Default QEXTMvvmSessionItem factory.

class QEXT_MVVM_API QEXTMvvmItemFactory : public QEXTMvvmItemFactoryInterface
{
public:
    QEXTMvvmItemFactory(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue);
    ~QEXTMvvmItemFactory() override;

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const QEXTMvvmModelType& modelType) const override;

    std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const override;

protected:
    std::unique_ptr<QEXTMvvmItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMFACTORY_H
