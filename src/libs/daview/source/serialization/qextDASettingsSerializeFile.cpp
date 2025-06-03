#include <qextDASettingsSerializeFile.h>

#include <QMutex>

class QExtDASettingsSerializeFilePrivate
{
public:
    explicit QExtDASettingsSerializeFilePrivate(QExtDASettingsSerializeFile *q);
    virtual ~QExtDASettingsSerializeFilePrivate();

    QExtDASerializable::Items loadItems();
    void saveItems(const QExtDASerializable::Items &items);
    void saveVariant(const QString &key, const QVariant &value);

    mutable QMutex mMutex;
    QExtDASerializable::Items mItems;
    QScopedPointer<QSettings> mSettings;

protected:
    QExtDASettingsSerializeFile * const q_ptr;
    QEXT_DECL_PUBLIC(QExtDASettingsSerializeFile)
    QEXT_DISABLE_COPY_MOVE(QExtDASettingsSerializeFilePrivate)
};

QExtDASettingsSerializeFilePrivate::QExtDASettingsSerializeFilePrivate(QExtDASettingsSerializeFile *q)
    : q_ptr(q)
{
}

QExtDASettingsSerializeFilePrivate::~QExtDASettingsSerializeFilePrivate()
{
}

QExtDASerializable::Items QExtDASettingsSerializeFilePrivate::loadItems()
{
    QExtDASerializable::Items items;
    QStringList childGroups = mSettings->childGroups();
    for (int i = 0; i < childGroups.size(); ++i)
    {
        const QString &key = childGroups.at(i);
        mSettings->beginGroup(key);
        QExtDASerializable::Items childItems = this->loadItems();
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

void QExtDASettingsSerializeFilePrivate::saveItems(const QExtDASerializable::Items &items)
{
    QExtDASerializable::Items::ConstIterator iter(items.constBegin());
    while (items.constEnd() != iter)
    {
        const QString &key = iter.key();
        const QVariant &value = iter.value();
        this->saveVariant(key, value);
        iter++;
    }
}

void QExtDASettingsSerializeFilePrivate::saveVariant(const QString &key, const QVariant &value)
{
    if (QExtDASerializable::isItems(value))
    {
        QExtDASerializable::Items items = QExtDASerializable::itemsFromVariant(value);
        mSettings->beginGroup(key);
        this->saveItems(items);
        mSettings->endGroup();
    }
    else
    {
        mSettings->setValue(key, value);
    }
}

QExtDASettingsSerializeFile::QExtDASettingsSerializeFile(const QString &filePath)
    : dd_ptr(new QExtDASettingsSerializeFilePrivate(this))
{
    this->setSerializeFilePath(filePath);
}

QExtDASettingsSerializeFile::~QExtDASettingsSerializeFile()
{
}

QExtDASerializable::Items QExtDASettingsSerializeFile::loadFile()
{
    Q_D(QExtDASettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    return d->loadItems();
}

void QExtDASettingsSerializeFile::saveFile(const QExtDASerializable::Items &items)
{
    Q_D(QExtDASettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    d->mSettings->clear();
    d->saveItems(items);
    d->mItems = items;
}

void QExtDASettingsSerializeFile::onSerializeFilePathChanged(const QString &path)
{
    Q_D(QExtDASettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    d->mSettings.reset(new QSettings(path, QSettings::IniFormat));
    d->saveItems(d->mItems);
}

