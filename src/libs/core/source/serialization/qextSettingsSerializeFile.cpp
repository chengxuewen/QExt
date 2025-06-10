#include <qextSettingsSerializeFile.h>

#include <QMutex>

class QExtSettingsSerializeFilePrivate
{
public:
    explicit QExtSettingsSerializeFilePrivate(QExtSettingsSerializeFile *q);
    virtual ~QExtSettingsSerializeFilePrivate();

    QExtSerializable::SerializedItems loadItems();
    void saveItems(const QExtSerializable::SerializedItems &items);
    void saveVariant(const QString &key, const QVariant &value);

    mutable QMutex mMutex;
    QExtSerializable::SerializedItems mItems;
    QScopedPointer<QSettings> mSettings;

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

QExtSerializable::SerializedItems QExtSettingsSerializeFilePrivate::loadItems()
{
    QExtSerializable::SerializedItems items;
    QStringList childGroups = mSettings->childGroups();
    for (int i = 0; i < childGroups.size(); ++i)
    {
        const QString &key = childGroups.at(i);
        mSettings->beginGroup(key);
        QExtSerializable::SerializedItems childItems = this->loadItems();
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

void QExtSettingsSerializeFilePrivate::saveItems(const QExtSerializable::SerializedItems &items)
{
    QExtSerializable::SerializedItems::ConstIterator iter(items.constBegin());
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
        QExtSerializable::SerializedItems items = QExtSerializable::serializedItemsFromVariant(value);
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

QExtSerializable::SerializedItems QExtSettingsSerializeFile::loadFile()
{
    Q_D(QExtSettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    return d->loadItems();
}

void QExtSettingsSerializeFile::saveFile(const QExtSerializable::SerializedItems &items)
{
    Q_D(QExtSettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    d->mSettings->clear();
    d->saveItems(items);
    d->mItems = items;
}

void QExtSettingsSerializeFile::onSerializeFilePathChanged(const QString &path)
{
    Q_D(QExtSettingsSerializeFile);
    QMutexLocker locker(&d->mMutex);
    d->mSettings.reset(new QSettings(path, QSettings::IniFormat));
    d->saveItems(d->mItems);
}

