#ifndef _QEXTMVVMJSONITEMCONVERTERINTERFACE_H
#define _QEXTMVVMJSONITEMCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QJsonObject;

class QEXTMvvmItem;

//! Base class for all converters of QEXTMvvmItem to/from JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemConverterInterface
{
public:
    virtual ~QEXTMvvmJsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject toJson(const QEXTMvvmItem* item) const = 0;

    //! Creates item from JSON.
    virtual QEXTMvvmItem *fromJson(const QJsonObject &) const = 0;
};


#endif // _QEXTMVVMJSONITEMCONVERTERINTERFACE_H
