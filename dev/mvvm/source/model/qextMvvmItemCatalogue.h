// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMCATALOGUE_H
#define MVVM_MODEL_ITEMCATALOGUE_H

#include <qextMvvmFunctionTypes.h>
#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItem;

//! Catalogue for item constructions. Contains collection of factory functions associated with
//! item's modelType and optional label.

class QEXT_MVVM_API QExtMvvmItemCatalogue {
public:
    QExtMvvmItemCatalogue();
    ~QExtMvvmItemCatalogue();

    QExtMvvmItemCatalogue(const QExtMvvmItemCatalogue& other);
    QExtMvvmItemCatalogue& operator=(const QExtMvvmItemCatalogue& other);

    template <typename T> void registerItem(const std::string& label = {});

    void registerItem(const std::string& modelType, QExtMvvmItemFactoryFunc func,
                      const std::string& label);

    bool contains(const std::string& modelType) const;

    QExtUniquePointer<QExtMvvmSessionItem> create(const std::string& modelType) const;

    std::vector<std::string> modelTypes() const;

    std::vector<std::string> labels() const;

    int itemCount() const;

    void merge(const QExtMvvmItemCatalogue& other);

private:
    struct ItemCatalogueImpl;
    QExtUniquePointer<ItemCatalogueImpl> p_impl;
};

template <typename T> void QExtMvvmItemCatalogue::registerItem(const std::string& label)
{
    registerItem(T().modelType(), qextMvvmItemFactoryFunction<T>(), label);
}

} // namespace ModelView

#endif // MVVM_MODEL_ITEMCATALOGUE_H
