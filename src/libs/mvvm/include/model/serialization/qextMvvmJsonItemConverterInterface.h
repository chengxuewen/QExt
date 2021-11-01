#ifndef _QEXTMVVMJSONITEMCONVERTERINTERFACE_H
#define _QEXTMVVMJSONITEMCONVERTERINTERFACE_H

#include <memory>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Base class for all converters of QEXTMvvmSessionItem to/from JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemConverterInterface
{
public:
    virtual ~QEXTMvvmJsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject to_json(const QEXTMvvmSessionItem* item) const = 0;

    //! Creates item from JSON.
    virtual std::unique_ptr<QEXTMvvmSessionItem> from_json(const QJsonObject&) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMCONVERTERINTERFACE_H
