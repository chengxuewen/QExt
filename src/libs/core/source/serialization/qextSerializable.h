#ifndef _QEXTSERIALIZABLE_H
#define _QEXTSERIALIZABLE_H

#include <QHash>
#include <QString>
#include <QVariant>
#include <QSharedData>

struct QExtSerializable
{
    typedef QHash<QString, QVariant> SerializedItems;

    virtual ~QExtSerializable() {}

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
