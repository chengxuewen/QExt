#ifndef _QEXTBREAKPADHANDLER_H
#define _QEXTBREAKPADHANDLER_H

#include <qextBreakpadGlobal.h>
#include <qextSingleton.h>

#include <QObject>
#include <QString>
#include <QUrl>

class QExtBreakpadHandlerPrivate;
class QEXT_BREAKPAD_API QExtBreakpadHandler: public QObject
{
    Q_OBJECT
public:
    explicit QExtBreakpadHandler(QObject *parent = QEXT_NULLPTR);
    ~QExtBreakpadHandler() QEXT_OVERRIDE;

    QString uploadUrl() const;
    void setUploadUrl(const QUrl &url);
    QStringList dumpFileList() const;

    QString dumpPath() const;
    void setDumpPath(const QString &path);

    bool isReporterEnable() const;
    void setReporterEnable(bool enable);

    int reporterAutoCloseTime() const;
    void setReporterAutoCloseTime(int time);

    QString reporterStyleTheme() const;
    void setReporterStyleTheme(const QString &name);

    static QString version();

public Q_SLOTS:
    void sendDumps();

protected:
    QScopedPointer<QExtBreakpadHandlerPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBreakpadHandler)
    QEXT_DISABLE_COPY_MOVE(QExtBreakpadHandler)
};

#define qextBreakpadHandler QExtSingleton<QExtBreakpadHandler>::instance()

#endif	// _QEXTBREAKPADHANDLER_H
