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

    QExtSerializable::SerializedItems loadFile() QEXT_OVERRIDE;
    void saveFile(const QExtSerializable::SerializedItems &items) QEXT_OVERRIDE;

protected:
    void onSerializeFilePathChanged(const QString &path) QEXT_OVERRIDE;

    QScopedPointer<QExtSettingsSerializeFilePrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtSettingsSerializeFile)
    QEXT_DISABLE_COPY_MOVE(QExtSettingsSerializeFile)
};

#endif // _QEXTSETTINGSSERIALIZEFILE_H
