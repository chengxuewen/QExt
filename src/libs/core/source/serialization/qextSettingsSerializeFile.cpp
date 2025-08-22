#include <qextSettingsSerializeFile.h>

#include <QReadWriteLock>

namespace internal
{
QEXT_STATIC_CONSTANT_STRING(kVersion, "Version")
QEXT_STATIC_CONSTANT_STRING(kVersionMajor, "Major")
QEXT_STATIC_CONSTANT_STRING(kVersionMinor, "Minor")
}

class QExtSettingsSerializeFilePrivate
{
public:
    explicit QExtSettingsSerializeFilePrivate(QExtSettingsSerializeFile *q);
    virtual ~QExtSettingsSerializeFilePrivate();

    QExtSerializable::SerializedItemsMap loadItems();
    void saveItems(const QExtSerializable::SerializedItemsMap &items);
    void saveVariant(const QString &key, const QVariant &value);

    mutable QReadWriteLock mRWLock;
    QScopedPointer<QSettings> mSettings;
    QExtSerializable::SerializedItemsMap mItems;

protected:
    QExtSettingsSerializeFile * const q_ptr;
    QEXT_DECL_PUBLIC(QExtSettingsSerializeFile)
    QEXT_DISABLE_COPY_MOVE(QExtSettingsSerializeFilePrivate)
};

QExtSettingsSerializeFilePrivate::QExtSettingsSerializeFilePrivate(QExtSettingsSerializeFile *q)
    : q_ptr(q)
{
}

QExtSettingsSerializeFilePrivate::~QExtSettingsSerializeFilePrivate()
{
}

QExtSerializable::SerializedItemsMap QExtSettingsSerializeFilePrivate::loadItems()
{
    QExtSerializable::SerializedItemsMap items;
    QStringList childGroups = mSettings->childGroups();
    for (int i = 0; i < childGroups.size(); ++i)
    {
        const QString &key = childGroups.at(i);
        mSettings->beginGroup(key);
        QExtSerializable::SerializedItemsMap childItems = this->loadItems();
        QStringList childKeys = mSettings->childKeys();
        for (int j = 0; j < childKeys.size(); ++j)
        {
            const QString &childKey = childKeys.at(j);
            childItems.insert(childKey, mSettings->value(childKey));
        }
        items.insert(key, childItems);
        mSettings->endGroup();
    }
    return items;
}

void QExtSettingsSerializeFilePrivate::saveItems(const QExtSerializable::SerializedItemsMap &items)
{
    QExtSerializable::SerializedItemsMap::ConstIterator iter(items.constBegin());
    while (items.constEnd() != iter)
    {
        const QString &key = iter.key();
        const QVariant &value = iter.value();
        this->saveVariant(key, value);
        iter++;
    }
}

void QExtSettingsSerializeFilePrivate::saveVariant(const QString &key, const QVariant &value)
{
    if (QExtSerializable::isSerializedItems(value))
    {
        QExtSerializable::SerializedItemsMap items = QExtSerializable::serializedItemsFromVariant(value);
        mSettings->beginGroup(key);
        this->saveItems(items);
        mSettings->endGroup();
    }
    else
    {
        mSettings->setValue(key, value);
    }
}

QExtSettingsSerializeFile::QExtSettingsSerializeFile(const QString &filePath)
    : dd_ptr(new QExtSettingsSerializeFilePrivate(this))
{
    this->setSerializeFilePath(filePath);
}

QExtSettingsSerializeFile::~QExtSettingsSerializeFile()
{
}

int QExtSettingsSerializeFile::versionMajor() const
{
    Q_D(const QExtSettingsSerializeFile);
    QReadLocker locker(&d->mRWLock);
    d->mSettings->beginGroup(internal::kVersion);
    const int major = d->mSettings->value(internal::kVersionMajor, 0).toInt();
    d->mSettings->endGroup();
    return major;
}

int QExtSettingsSerializeFile::versionMinor() const
{
    Q_D(const QExtSettingsSerializeFile);
    QReadLocker locker(&d->mRWLock);
    d->mSettings->beginGroup(internal::kVersion);
    const int minor = d->mSettings->value(internal::kVersionMinor, 0).toInt();
    d->mSettings->endGroup();
    return minor;
}

void QExtSettingsSerializeFile::setVersionMajor(int major)
{
    Q_D(QExtSettingsSerializeFile);
    QWriteLocker locker(&d->mRWLock);
    d->mSettings->beginGroup(internal::kVersion);
    d->mSettings->setValue(internal::kVersionMajor, major);
    d->mSettings->endGroup();
}

void QExtSettingsSerializeFile::setVersionMinor(int minor)
{
    Q_D(QExtSettingsSerializeFile);
    QWriteLocker locker(&d->mRWLock);
    d->mSettings->beginGroup(internal::kVersion);
    d->mSettings->setValue(internal::kVersionMinor, minor);
    d->mSettings->endGroup();
}

QExtSerializable::SerializedItemsMap QExtSettingsSerializeFile::loadFile()
{
    Q_D(QExtSettingsSerializeFile);
    QReadLocker locker(&d->mRWLock);
    return d->loadItems();
}

void QExtSettingsSerializeFile::saveFile(const QExtSerializable::SerializedItemsMap &items)
{
    Q_D(QExtSettingsSerializeFile);
    QWriteLocker locker(&d->mRWLock);
    d->mSettings->clear();
    d->saveItems(items);
    d->mItems = items;
}

void QExtSettingsSerializeFile::onSerializeFilePathChanged(const QString &path)
{
    Q_D(QExtSettingsSerializeFile);
    QWriteLocker locker(&d->mRWLock);
    d->mSettings.reset(new QSettings(path, QSettings::IniFormat));
    d->saveItems(d->mItems);
}

