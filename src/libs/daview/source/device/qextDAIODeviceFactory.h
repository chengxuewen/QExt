#ifndef _QEXTDAIODEVICEFACTORY_H
#define _QEXTDAIODEVICEFACTORY_H

#include <qextTypeTrait.h>
#include <qextDAIODevice.h>
#include <qextDAViewGlobal.h>

#include <QObject>
#include <QStandardItemModel>

typedef QExtDAIODevice::SharedPtr(*QExtDAIODeviceCreaterFunc)();

template <typename T>
QExtDAIODevice::SharedPtr qextMakeDAIODevice()
{
    return QExtDAIODevice::SharedPtr(new T);
}

template <typename T>
QExtDAIODeviceCreaterFunc qextDAIODeviceCreaterFunction()
{
    return &qextMakeDAIODevice<T>;
}

template <typename T>
struct QExtDAIODeviceCreaterFunctor
{
    QExtDAIODeviceCreaterFunc operator ()() { return new T; }
};

class QExtDAIODeviceFactoryPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceFactory : public QObject
{
    Q_OBJECT
public:
    explicit QExtDAIODeviceFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDAIODeviceFactory() QEXT_OVERRIDE;

    template <typename T>
    void registerIODevice(const QString &type)
    {
        enum { Valid = QExtIsBaseOf<QExtDAIODevice, T>::value };
        QEXT_STATIC_ASSERT_X(Valid, "type must base on QExtDAIODevice.");
        this->registerIODevice(type, qextDAIODeviceCreaterFunction<T>());
    }

    virtual QStringList ioDeviceTypes() const;
    virtual QExtDAIODevice::SharedPtr createIODevice(const QString &type) const;
    virtual void registerIODevice(const QString &type, QExtDAIODeviceCreaterFunc func);

    virtual QStandardItemModel *makeIODeviceTypeListModel(QObject *parent = QEXT_NULLPTR) const;
    virtual QExtDAIODevice::SharedPtr selectCreateIODevice(QWidget *parent = QEXT_NULLPTR) const;

protected:
    QScopedPointer<QExtDAIODeviceFactoryPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceFactory)
};

#endif // _QEXTDAIODEVICEFACTORY_H
