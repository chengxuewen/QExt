#ifndef _QEXTMVVMITEMFACTORY_H
#define _QEXTMVVMITEMFACTORY_H

#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QEXTMvvmItemCatalogue;

//! Default QEXTMvvmItem factory.

class QEXT_MVVM_API QEXTMvvmItemFactory : public QEXTMvvmItemFactoryInterface
{
public:
    QEXTMvvmItemFactory(QEXTMvvmItemCatalogue *catalogue);
    ~QEXTMvvmItemFactory() QEXT_DECL_OVERRIDE;

    QEXTMvvmItem *createItem(const QString &modelType) const QEXT_DECL_OVERRIDE;

    QEXTMvvmItem *createEmptyItem() const QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QEXTMvvmItemCatalogue> m_catalogue;
};


#endif // _QEXTMVVMITEMFACTORY_H
