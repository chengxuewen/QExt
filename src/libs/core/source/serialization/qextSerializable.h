#ifndef _QEXTSERIALIZABLE_H
#define _QEXTSERIALIZABLE_H

#include <QHash>
#include <QString>
#include <QVariant>
#include <QSharedData>
// #include <QMutableHash>

#include <qextGlobal.h>

struct QExtSerializable
{
    typedef QHash<QString, QVariant> SerializedItems;
    typedef void(*DestroyedNotifyFunction)(QExtSerializable *serializable, const QVariant &usrdata);

    virtual ~QExtSerializable()
    {
        // QMultiHash<DestroyedNotifyFunction, QVariant>::ConstIterator iter(mDestroyedNotifyFunctionMap);
        // while (mDestroyedNotifyFunctionMap.constEnd() != iter)
        // {
        //     DestroyedNotifyFunction func = iter.key();
        //     if (func)
        //     {
        //         func(this, iter.value());
        //     }
        //     iter++;
        // }
    }

    void removeDestroyedNotifyFunction(DestroyedNotifyFunction func)
    {
        mDestroyedNotifyFunctionMap.remove(func);
    }
    void appendDestroyedNotifyFunction(DestroyedNotifyFunction func, const QVariant &usrdata = QVariant())
    {
        mDestroyedNotifyFunctionMap.insert(func, usrdata);
    }

    virtual void serializeLoad(const SerializedItems &items) { Q_UNUSED(items); }
    virtual SerializedItems serializeSave() const { return SerializedItems(); }
    virtual bool isSerializationModified() const { return true; }

    static inline bool isSerializedItems(const QVariant &variant)
    {
        return variant.canConvert<SerializedItems>();
    }
    static inline SerializedItems serializedItemsFromVariant(const QVariant &variant)
    {
        return variant.value<SerializedItems>();
    }

protected:
    void resetModified();

private:
    bool mModified;
    QMultiHash<DestroyedNotifyFunction, QVariant> mDestroyedNotifyFunctionMap;
};


class QExtSerializableProxy : public QExtSerializable
{
public:
    QExtSerializableProxy(QExtSerializable *serializable = QEXT_NULLPTR)
        : mSerializable(serializable) {}
    QExtSerializableProxy(const SerializedItems &items)
        : mSerializable(QEXT_NULLPTR), mSerializedItems(items) {}
    QExtSerializableProxy(const QExtSerializableProxy &other)
        : mSerializable(other.mSerializable), mSerializedItems(other.mSerializedItems) {}
    ~QExtSerializableProxy() QEXT_OVERRIDE {}

    QExtSerializableProxy &operator=(const QExtSerializableProxy &other)
    {
        if (this != &other)
        {
            mSerializable = other.mSerializable;
            mSerializedItems = other.mSerializedItems;
        }
        return *this;
    }

    inline bool operator==(const QExtSerializableProxy &other)
    {
        if (this != &other)
        {
            return other.mSerializable == mSerializable && other.mSerializedItems == mSerializedItems;
        }
        return true;
    }
    inline bool operator!=(const QExtSerializableProxy &other)
    {
        return !(*this == other);
    }

    inline void swap(QExtSerializableProxy &other)
    {
        qSwap(mSerializable, other.mSerializable);
        qSwap(mSerializedItems, other.mSerializedItems);
    }

    QExtSerializable *serializable() const { return mSerializable; }
    const SerializedItems &serializedItems() const { return mSerializedItems; }

    bool isValid() const { return !this->isNull(); }
    bool isNull() const { return QEXT_NULLPTR == mSerializable && mSerializedItems.isEmpty(); }

    void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE
    {
        if (mSerializable)
        {
            mSerializable->serializeLoad(items);
        }
        else
        {
            mSerializedItems = items;
        }
    }
    SerializedItems serializeSave() const QEXT_OVERRIDE
    {
        return mSerializable ? mSerializable->serializeSave() : mSerializedItems;
    }
    bool isSerializationModified() const QEXT_OVERRIDE
    {
        return mSerializable ? mSerializable->isSerializationModified() : false;
    }

private:
    QExtSerializable *mSerializable;
    SerializedItems mSerializedItems;
};

class QExtSerializableObject : public QObject, public QExtSerializable
{
public:
    explicit QExtSerializableObject(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}
    ~QExtSerializableObject() QEXT_OVERRIDE {}
};

struct QExtSerializeFile
{
    virtual ~QExtSerializeFile() {}

    virtual QString serializeFilePath() const
    {
        return mSerializeFilePath;
    }
    virtual void setSerializeFilePath(const QString &path)
    {
        if (path != mSerializeFilePath)
        {
            mSerializeFilePath = path;
            this->onSerializeFilePathChanged(path);
        }
    }

    virtual QExtSerializable::SerializedItems loadFile() = 0;
    virtual void saveFile(const QExtSerializable::SerializedItems &items) = 0;

protected:
    virtual void onSerializeFilePathChanged(const QString &path) { Q_UNUSED(path); }

private:
    QString mSerializeFilePath;
};

#endif // _QEXTSERIALIZABLE_H
