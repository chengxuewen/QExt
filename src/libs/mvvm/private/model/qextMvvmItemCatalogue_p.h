#ifndef _QEXTMVVMITEMCATALOGUE_P_H
#define _QEXTMVVMITEMCATALOGUE_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmFactoryInterface.h>

#include <QPair>

class QEXTMvvmItem;
class QEXTMvvmItemCatalogue;
class QEXT_MVVM_API QEXTMvvmItemCataloguePrivate
{
public:
    explicit QEXTMvvmItemCataloguePrivate(QEXTMvvmItemCatalogue *q);
    virtual ~QEXTMvvmItemCataloguePrivate();

    QEXTMvvmItemCatalogue * const q_ptr;

    QEXTMvvmFactoryInterface<QString, QEXTMvvmItem> m_factory;
    QVector<QPair<QString, QString> > m_info;   // QPair<item_type, item_label>

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemCataloguePrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmItemCatalogue)
};

#endif // _QEXTMVVMITEMCATALOGUE_P_H
