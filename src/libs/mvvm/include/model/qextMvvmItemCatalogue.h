#ifndef _QEXTMVVMITEMCATALOGUE_H
#define _QEXTMVVMITEMCATALOGUE_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

#include <QString>
#include <QVector>


class QEXTMvvmItem;

//! Catalogue for item constructions.
class QEXTMvvmItemCataloguePrivate;
class QEXT_MVVM_API QEXTMvvmItemCatalogue
{
public:
    QEXTMvvmItemCatalogue();
    QEXTMvvmItemCatalogue(const QEXTMvvmItemCatalogue &other);
    virtual ~QEXTMvvmItemCatalogue();

    QEXTMvvmItemCatalogue &operator=(const QEXTMvvmItemCatalogue& other);

    template <typename T> static T *createItem();
    template <typename T> void registerItem(const QString &label = QString());

    bool contains(const QString &modelType) const;

    QEXTMvvmItem *create(const QString &modelType) const;

    QVector<QString> modelTypes() const;
    QVector<QString> labels() const;

    int itemCount() const;

    void merge(const QEXTMvvmItemCatalogue &other);

protected:
    void add(const QString &modelType, const QString &label, QEXTMvvmItemFactoryFunction func);

    QScopedPointer<QEXTMvvmItemCataloguePrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTMvvmItemCatalogue)
};

template<typename T> T *QEXTMvvmItemCatalogue::createItem()
{
    return new T;
}

template <typename T> void QEXTMvvmItemCatalogue::registerItem(const QString &label)
{
    T x;
    this->add(x.modelType(), label, QEXTMvvmItemFactoryFunction(&QEXTMvvmItemCatalogue::createItem<T>));
}


#endif // _QEXTMVVMITEMCATALOGUE_H
