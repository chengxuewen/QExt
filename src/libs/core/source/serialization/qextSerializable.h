#ifndef _QEXTSERIALIZABLE_H
#define _QEXTSERIALIZABLE_H

#include <QMap>
#include <QHash>
#include <QFile>
#include <QString>
#include <QVariant>
#include <QSharedData>
#include <QMutableHashIterator>

#include <qextGlobal.h>

struct QExtSerializable
{
    typedef QMap<QString, QVariant> SerializedItemsMap;
    typedef void(*DestroyedNotifyFunction)(QExtSerializable *serializable, const QVariant &usrdata);

    virtual ~QExtSerializable()
    {
        QMutableHashIterator<qulonglong, QVariant> iter(mDestroyedNotifyFunctionMap);
        while (iter.hasNext())
        {
            iter.next();
            DestroyedNotifyFunction func = reinterpret_cast<DestroyedNotifyFunction>(iter.key());
            if (func)
            {
                func(this, iter.value());
            }
        }
    }

    void removeDestroyedNotifyFunction(DestroyedNotifyFunction func)
    {
        mDestroyedNotifyFunctionMap.remove(reinterpret_cast<qulonglong>(func));
    }
    void appendDestroyedNotifyFunction(DestroyedNotifyFunction func, const QVariant &usrdata = QVariant())
    {
        mDestroyedNotifyFunctionMap.insert(reinterpret_cast<qulonglong>(func), usrdata);
    }

    virtual void serializeLoad(const SerializedItemsMap &items) { Q_UNUSED(items); }
    virtual SerializedItemsMap serializeSave() const { return SerializedItemsMap(); }
    virtual bool isSerializationModified() const { return true; }

    static inline bool isSerializedItems(const QVariant &variant)
    {
        return variant.canConvert<SerializedItemsMap>();
    }
    static inline SerializedItemsMap serializedItemsFromVariant(const QVariant &variant)
    {
        return variant.value<SerializedItemsMap>();
    }

protected:
    void resetModified();

private:
    bool mModified;
    QMultiHash<qulonglong, QVariant> mDestroyedNotifyFunctionMap;
};


class QExtSerializableProxy : public QExtSerializable
{
public:
    QExtSerializableProxy(QExtSerializable *serializable = QEXT_NULLPTR)
        : mSerializable(serializable) {}
    QExtSerializableProxy(const SerializedItemsMap &items)
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
    const SerializedItemsMap &serializedItems() const { return mSerializedItems; }

    bool isValid() const { return !this->isNull(); }
    bool isNull() const { return QEXT_NULLPTR == mSerializable && mSerializedItems.isEmpty(); }

    void serializeLoad(const SerializedItemsMap &items) QEXT_OVERRIDE
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
    SerializedItemsMap serializeSave() const QEXT_OVERRIDE
    {
        return mSerializable ? mSerializable->serializeSave() : mSerializedItems;
    }
    bool isSerializationModified() const QEXT_OVERRIDE
    {
        return mSerializable ? mSerializable->isSerializationModified() : false;
    }

private:
    QExtSerializable *mSerializable;
    SerializedItemsMap mSerializedItems;
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

    virtual int versionMajor() const = 0;
    virtual int versionMinor() const = 0;
    virtual void setVersionMajor(int major) = 0;
    virtual void setVersionMinor(int minor) = 0;

    QString versionString() const
    {
        return QString("%1.%2").arg(this->versionMajor()).arg(this->versionMinor());
    }
    void setVersion(int major, int minor)
    {
        this->setVersionMajor(major);
        this->setVersionMinor(minor);
    }

    virtual QExtSerializable::SerializedItemsMap loadFile() = 0;
    virtual void saveFile(const QExtSerializable::SerializedItemsMap &items) = 0;

protected:
    virtual void onSerializeFilePathChanged(const QString &path) { Q_UNUSED(path); }

private:
    QString mSerializeFilePath;
};

#endif // _QEXTSERIALIZABLE_H
