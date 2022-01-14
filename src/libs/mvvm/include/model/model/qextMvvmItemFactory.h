#ifndef _QEXTMVVMMODELITEMFACTORY_H
#define _QEXTMVVMMODELITEMFACTORY_H

#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmItemCatalogue;

//! Default QEXTMvvmSessionItem factory.

class QEXT_MVVM_API QEXTMvvmItemFactory : public QEXTMvvmItemFactoryInterface
{
public:
    QEXTMvvmItemFactory(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue);
    ~QEXTMvvmItemFactory() override;

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType) const override;

    std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const override;

protected:
    std::unique_ptr<QEXTMvvmItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELITEMFACTORY_H
