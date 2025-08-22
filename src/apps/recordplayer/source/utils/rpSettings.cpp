#include <rpSettings.h>
#include <rpConfig.h>
#include <rpCommonUtils.h>

#include <qextSettingsSerializeFile.h>

#include <QDebug>

class RPSettingsPrivate
{
public:
    explicit RPSettingsPrivate(RPSettings *q);
    ~RPSettingsPrivate();

    RPSettings *const q_ptr;

    QExtSettingsSerializeFile mSettingsSerializeFile;

private:
    Q_DISABLE_COPY(RPSettingsPrivate)
    Q_DECLARE_PUBLIC(RPSettings)
};

RPSettingsPrivate::RPSettingsPrivate(RPSettings *q)
    : q_ptr(q)
{
    const auto filePath = QString("%1/%2.ini").arg(RPCommonUtils::appConfigLocation(), RP_PROGRAM_NAME);
    mSettingsSerializeFile.setSerializeFilePath(filePath);
    qDebug() << "SettingsSerializeFile: " << filePath;
}

RPSettingsPrivate::~RPSettingsPrivate()
{
}

RPSettings::RPSettings(QObject *parent)
    : QObject(parent), dd_ptr(new RPSettingsPrivate(this))
{
}

void RPSettings::onSerializeFilePathChanged(const QString &path)
{
    Q_D(RPSettings);
    d->mSettingsSerializeFile.setSerializeFilePath(path);
}

RPSettings::~RPSettings()
{
}

QString RPSettings::serializeFilePath() const
{
    Q_D(const RPSettings);
    return d->mSettingsSerializeFile.serializeFilePath();
}

int RPSettings::versionMajor() const
{
    Q_D(const RPSettings);
    return d->mSettingsSerializeFile.versionMajor();
}

int RPSettings::versionMinor() const
{
    Q_D(const RPSettings);
    return d->mSettingsSerializeFile.versionMinor();
}

void RPSettings::setVersionMajor(int major)
{
    Q_D(RPSettings);
    d->mSettingsSerializeFile.setVersionMajor(major);
}

void RPSettings::setVersionMinor(int minor)
{
    Q_D(RPSettings);
    d->mSettingsSerializeFile.setVersionMinor(minor);
}

QExtSerializable::SerializedItemsMap RPSettings::loadFile()
{
    Q_D(RPSettings);
    return d->mSettingsSerializeFile.loadFile();
}

void RPSettings::saveFile(const QExtSerializable::SerializedItemsMap &items)
{
    Q_D(RPSettings);
    d->mSettingsSerializeFile.saveFile(items);
}

void RPSettings::updateSettings()
{
    emit this->requestUpdateSettings();
}
