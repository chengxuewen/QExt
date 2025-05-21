#ifndef _QEXTDASETTINGSSERIALIZEFILE_H
#define _QEXTDASETTINGSSERIALIZEFILE_H

#include <QObject>
#include <QSettings>

#include <qextDAViewGlobal.h>
#include <qextDASerializable.h>

class QExtDASettingsSerializeFilePrivate;
class QEXT_DAVIEW_API QExtDASettingsSerializeFile : public QExtDASerializeFile
{
public:
    explicit QExtDASettingsSerializeFile(const QString &filePath = "");
    ~QExtDASettingsSerializeFile() QEXT_OVERRIDE;

    QExtDASerializable::Items loadFile() QEXT_OVERRIDE;
    void saveFile(const QExtDASerializable::Items &items) QEXT_OVERRIDE;

protected:
    void onSerializeFilePathChanged(const QString &path) QEXT_OVERRIDE;

    QScopedPointer<QExtDASettingsSerializeFilePrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtDASettingsSerializeFile)
    QEXT_DISABLE_COPY_MOVE(QExtDASettingsSerializeFile)
};

#endif // _QEXTDASETTINGSSERIALIZEFILE_H
