#ifndef _QEXTSETTINGSSERIALIZEFILE_H
#define _QEXTSETTINGSSERIALIZEFILE_H

#include <QObject>
#include <QSettings>

#include <qextGlobal.h>
#include <qextSerializable.h>

class QExtSettingsSerializeFilePrivate;
class QEXT_CORE_API QExtSettingsSerializeFile : public QExtSerializeFile
{
public:
    explicit QExtSettingsSerializeFile(const QString &filePath = "");
    ~QExtSettingsSerializeFile() QEXT_OVERRIDE;

    int versionMajor() const QEXT_OVERRIDE;
    int versionMinor() const QEXT_OVERRIDE;
    void setVersionMajor(int major) QEXT_OVERRIDE;
    void setVersionMinor(int minor) QEXT_OVERRIDE;

    QExtSerializable::SerializedItemsMap loadFile() QEXT_OVERRIDE;
    void saveFile(const QExtSerializable::SerializedItemsMap &items) QEXT_OVERRIDE;

protected:
    void onSerializeFilePathChanged(const QString &path) QEXT_OVERRIDE;

    QScopedPointer<QExtSettingsSerializeFilePrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtSettingsSerializeFile)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSettingsSerializeFile)
};

#endif // _QEXTSETTINGSSERIALIZEFILE_H
