#ifndef _QEXTDASERIALIZABLE_H
#define _QEXTDASERIALIZABLE_H

#include <QHash>
#include <QString>
#include <QVariant>
#include <QSharedData>

struct QExtDASerializable
{
    typedef QHash<QString, QVariant> Items;

    virtual ~QExtDASerializable() {}

    virtual void load(const Items &items) {}
    virtual Items save() const { return Items(); }

    static inline bool isItems(const QVariant &variant)
    {
        return variant.canConvert<Items>();
    }
    static inline Items itemsFromVariant(const QVariant &variant)
    {
        return variant.value<Items>();
    }
};

struct QExtDASerializeFile
{
    virtual ~QExtDASerializeFile() {}

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

    virtual QExtDASerializable::Items loadFile() = 0;
    virtual void saveFile(const QExtDASerializable::Items &items) = 0;

protected:
    virtual void onSerializeFilePathChanged(const QString &path) { Q_UNUSED(path); }

private:
    QString mSerializeFilePath;
};

#endif // _QEXTDASERIALIZABLE_H
