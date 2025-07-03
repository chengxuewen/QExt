#ifndef _QEXTBREAKPADHTTPSENDER_H
#define _QEXTBREAKPADHTTPSENDER_H

#include <qextBreakpadGlobal.h>

#include <QObject>
#include <QPointer>
#include <QNetworkReply>

class QUrl;
class QFile;
class QString;

class QExtBreakpadHttpUploaderPrivate;
class QEXT_BREAKPAD_API QExtBreakpadHttpUploader : public QObject
{
    Q_OBJECT
public:
    explicit QExtBreakpadHttpUploader(QObject *parent = QEXT_NULLPTR);
    QExtBreakpadHttpUploader(const QUrl &url, QObject *parent = QEXT_NULLPTR);
    ~QExtBreakpadHttpUploader() QEXT_OVERRIDE;

    QString remoteUrl() const;
    void setUrl(const QUrl &url);

Q_SIGNALS:
    void finished(QString answer);

public Q_SLOTS:
    void uploadDump(const QString &filePath);

private Q_SLOTS:
    void onUploadProgress(qint64 sent, qint64 total);
    void onError(QNetworkReply::NetworkError err);
    void onUploadFinished();

protected:
    QScopedPointer<QExtBreakpadHttpUploaderPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBreakpadHttpUploader)
    QEXT_DISABLE_COPY_MOVE(QExtBreakpadHttpUploader)
};

#endif	// _QEXTBREAKPADHTTPSENDER_H
