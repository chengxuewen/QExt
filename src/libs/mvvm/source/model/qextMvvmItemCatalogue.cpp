#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemCatalogue_p.h>
#include <qextMvvmFactoryInterface.h>
#include <qextMvvmItem.h>

#include <stdexcept>

QEXTMvvmItemCataloguePrivate::QEXTMvvmItemCataloguePrivate(QEXTMvvmItemCatalogue *q)
    : q_ptr(q)
{

}

QEXTMvvmItemCataloguePrivate::~QEXTMvvmItemCataloguePrivate()
{

}



QEXTMvvmItemCatalogue::QEXTMvvmItemCatalogue()
    : d_ptr(new QEXTMvvmItemCataloguePrivate(this))
{

}

QEXTMvvmItemCatalogue::~QEXTMvvmItemCatalogue()
{

}

QEXTMvvmItemCatalogue::QEXTMvvmItemCatalogue(const QEXTMvvmItemCatalogue &other)
    : d_ptr(new QEXTMvvmItemCataloguePrivate(this))
{
    QEXT_DECL_D(QEXTMvvmItemCatalogue);
    d->m_factory = other.d_func()->m_factory;
    d->m_info = other.d_func()->m_info;
}

QEXTMvvmItemCatalogue &QEXTMvvmItemCatalogue::operator=(const QEXTMvvmItemCatalogue &other)
{
    if (this != &other)
    {
        QEXT_DECL_D(QEXTMvvmItemCatalogue);
        d->m_factory = other.d_func()->m_factory;
        d->m_info = other.d_func()->m_info;
    }
    return *this;
}

void QEXTMvvmItemCatalogue::add(const QString &modelType, const QString &label, QEXTMvvmItemFactoryFunction func)
{
    QEXT_DECL_D(QEXTMvvmItemCatalogue);
    d->m_factory.add(modelType, func);
    d->m_info.append(QPair<QString, QString>(modelType, label));
}

bool QEXTMvvmItemCatalogue::contains(const QString &modelType) const
{
    QEXT_DECL_DC(QEXTMvvmItemCatalogue);
    return d->m_factory.contains(modelType);
}

QEXTMvvmItem *QEXTMvvmItemCatalogue::create(const QString &modelType) const
{
    QEXT_DECL_DC(QEXTMvvmItemCatalogue);
    return d->m_factory.create(modelType);
}

QVector<QString> QEXTMvvmItemCatalogue::modelTypes() const
{
    QEXT_DECL_DC(QEXTMvvmItemCatalogue);
    QVector<QString> result;
    for (int i = 0; i < d->m_info.size(); ++i) {
        result.append(d->m_info.at(i).first);
    }
    return result;
}

QVector<QString> QEXTMvvmItemCatalogue::labels() const
{
    QEXT_DECL_DC(QEXTMvvmItemCatalogue);
    QVector<QString> result;
    for (int i = 0; i < d->m_info.size(); ++i) {
        result.append(d->m_info.at(i).second);
    }
    return result;
}

int QEXTMvvmItemCatalogue::itemCount() const
{
    QEXT_DECL_DC(QEXTMvvmItemCatalogue);
    return d->m_factory.size();
}

//! Adds content of other catalogue to this.

void QEXTMvvmItemCatalogue::merge(const QEXTMvvmItemCatalogue &other)
{
    QEXT_DECL_D(QEXTMvvmItemCatalogue);
    size_t index(0);
    QEXTMvvmFactoryInterface<QString, QEXTMvvmItem> factory = other.d_func()->m_factory;
    QEXTMvvmFactoryInterface<QString, QEXTMvvmItem>::Iterator iter;
    for (iter = factory.begin(); iter != factory.end(); ++iter)
    {
        if (this->contains(iter.key()))
        {
            throw std::runtime_error("QEXTMvvmItemCatalogue::add() -> Catalogue contains duplicated records");
        }
        this->add(iter.key(), other.d_func()->m_info[index].second, iter.value());
    }
}

