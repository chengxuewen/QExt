#ifndef _RPSETTINGS_H
#define _RPSETTINGS_H

#include <rpConstants.h>

#include <qextSingleton.h>
#include <qextSerializable.h>

#include <QObject>
#include <QSettings>

class RPSettingsPrivate;
class RPSettings : public QObject, public QExtSerializeFile, public QExtSingleton<RPSettings>
{
    Q_OBJECT
    QEXT_DECLARE_SINGLETON(RPSettings)
public:

    QString serializeFilePath() const override;

    int versionMajor() const override;
    int versionMinor() const override;
    void setVersionMajor(int major) override;
    void setVersionMinor(int minor) override;

    QExtSerializable::SerializedItemsMap loadFile() override;
    void saveFile(const QExtSerializable::SerializedItemsMap &items) override;

    void updateSettings();

Q_SIGNALS:
    void requestUpdateSettings();
    void advanceViewSettingChanged();

protected:
    explicit RPSettings(QObject *parent = nullptr);
    ~RPSettings() override;

    void onSerializeFilePathChanged(const QString &path) override;

private:
    QScopedPointer<RPSettingsPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, RPSettings)
    Q_DISABLE_COPY(RPSettings)
};

#endif // _RPSETTINGS_H
