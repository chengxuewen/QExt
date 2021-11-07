#ifndef _QEXTMVVMITEMFACTORYINTERFACE_H
#define _QEXTMVVMITEMFACTORYINTERFACE_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

class QEXTMvvmItem;

//! Interface class for all factories capable of producing QEXTMvvmItem's.

class QEXT_MVVM_API QEXTMvvmItemFactoryInterface
{
public:
    virtual ~QEXTMvvmItemFactoryInterface() { }

    virtual QEXTMvvmItem *createItem(const QString &modelType) const = 0;

    virtual QEXTMvvmItem *createEmptyItem() const = 0;
};


#endif // _QEXTMVVMITEMFACTORYINTERFACE_H
