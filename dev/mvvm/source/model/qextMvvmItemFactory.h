// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMFACTORY_H
#define MVVM_MODEL_ITEMFACTORY_H

#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmItemCatalogue;

//! Default QExtMvvmSessionItem factory.

class QEXT_MVVM_API QExtMvvmItemFactory : public QExtMvvmItemFactoryInterface {
public:
    QExtMvvmItemFactory(QExtUniquePointer<QExtMvvmItemCatalogue> catalogue);
    ~QExtMvvmItemFactory() override;

    void registerItem(const std::string& modelType, QExtMvvmItemFactoryFunc func,
                      const std::string& label) override;

    QExtUniquePointer<QExtMvvmSessionItem> createItem(const QExtMvvmModelType& modelType) const override;

protected:
    QExtUniquePointer<QExtMvvmItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORY_H
