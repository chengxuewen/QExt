#ifndef _QEXTMVVMITEMCATALOGUE_H
#define _QEXTMVVMITEMCATALOGUE_H

#include <qextMvvmFunctionTypes.h>
#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Catalogue for item constructions.

class QEXT_MVVM_API QEXTMvvmItemCatalogue
{
public:
    QEXTMvvmItemCatalogue();
    ~QEXTMvvmItemCatalogue();

    QEXTMvvmItemCatalogue(const QEXTMvvmItemCatalogue& other);
    QEXTMvvmItemCatalogue& operator=(const QEXTMvvmItemCatalogue& other);

    template <typename T> void registerItem(const std::string& label = {});

    bool contains(const std::string& QEXTMvvmModelType) const;

    std::unique_ptr<QEXTMvvmSessionItem> create(const std::string& QEXTMvvmModelType) const;

    std::vector<std::string> modelTypes() const;
    std::vector<std::string> labels() const;

    int itemCount() const;

    void merge(const QEXTMvvmItemCatalogue& other);

private:
    void add(const std::string& QEXTMvvmModelType, item_factory_func_t func, const std::string& label);
    struct ItemCatalogueImpl;
    std::unique_ptr<ItemCatalogueImpl> p_impl;
};

template <typename T> void QEXTMvvmItemCatalogue::registerItem(const std::string& label)
{
    T x;
    add(
        x.modelType(), []() { return std::make_unique<T>(); }, label);
}

} // namespace ModelView

#endif // _QEXTMVVMITEMCATALOGUE_H
