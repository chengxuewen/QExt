#include <qextBreakpadHttpUploader.h>

#include <QUrl>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QHttpMultiPart>
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QNetworkAccessManager>

class QExtBreakpadHttpUploaderPrivate
{
    QExtBreakpadHttpUploader * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtBreakpadHttpUploader)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBreakpadHttpUploaderPrivate)
public:
    explicit QExtBreakpadHttpUploaderPrivate(QExtBreakpadHttpUploader *q);
    virtual ~QExtBreakpadHttpUploaderPrivate();

    QNetworkAccessManager mManager;
    QNetworkRequest mRequest;

    QPointer<QNetworkReply> mReply;
    QFile *mFile;
};

QExtBreakpadHttpUploaderPrivate::QExtBreakpadHttpUploaderPrivate(QExtBreakpadHttpUploader *q)
    : q_ptr(q)
    , mFile(QEXT_NULLPTR)
{
}

QExtBreakpadHttpUploaderPrivate::~QExtBreakpadHttpUploaderPrivate()
{
    if(mReply)
    {
        qWarning("m_reply is not NULL");
        mReply->deleteLater();
    }
    delete mFile;
}

QExtBreakpadHttpUploader::QExtBreakpadHttpUploader(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtBreakpadHttpUploaderPrivate(this))
{
}

QExtBreakpadHttpUploader::QExtBreakpadHttpUploader(const QUrl &url, QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtBreakpadHttpUploaderPrivate(this))
{
    Q_D(QExtBreakpadHttpUploader);
    d->mRequest.setUrl(url);
}

QExtBreakpadHttpUploader::~QExtBreakpadHttpUploader()
{
}

QString QExtBreakpadHttpUploader::remoteUrl() const
{
    Q_D(const QExtBreakpadHttpUploader);
    return d->mRequest.url().toString();
}

void QExtBreakpadHttpUploader::setUrl(const QUrl &url)
{
    Q_D(QExtBreakpadHttpUploader);
    d->mRequest.setUrl(url);
}

void QExtBreakpadHttpUploader::uploadDump(const QString& filePath)
{
    Q_D(QExtBreakpadHttpUploader);
    Q_ASSERT(!d->mFile);
    Q_ASSERT(!d->mReply);
    Q_ASSERT(QDir().exists(filePath));
    QFileInfo fileInfo(filePath);

    //product name parameter
    QHttpPart prodPart;
#if defined(SOCORRO)
    prodPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"ProductName\""));      // Socorro
#elif defined(CALIPER)
    prodPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"prod\""));     // Caliper
#endif
    prodPart.setBody(qApp->applicationName().toLatin1());
    //product version parameter
    QHttpPart verPart;
#if defined(SOCORRO)
    verPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"Version\""));      // Socorro
#elif defined(CALIPER)
    verPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"ver\""));     // Caliper
#endif
    verPart.setBody(qApp->applicationVersion().toLatin1());

    // file_minidump name & file_binary in one part
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"upload_file_minidump\"; filename=\""+ fileInfo.fileName()+ "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));

    d->mFile = new QFile(filePath);
    if(!d->mFile->open(QIODevice::ReadOnly))
    {
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    filePart.setBodyDevice(d->mFile);
    d->mFile->setParent(multiPart);

    multiPart->append(prodPart);
    multiPart->append(verPart);
    multiPart->append(filePart);

    d->mRequest.setRawHeader("User-Agent", qApp->applicationName().toLatin1()+"/"+qApp->applicationVersion().toLatin1());
#if defined(SOCORRO)
    d->mRequest.setRawHeader("Host", qApp->applicationName().toLower().toLatin1()+"_reports");
    d->mRequest.setRawHeader("Accept", "*/*");
#endif

    d->mReply = d->mManager.post(d->mRequest, multiPart);
    multiPart->setParent(d->mReply);

    connect(d->mReply, SIGNAL(finished()), this, SLOT(onUploadFinished()));
    connect(d->mReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(onUploadProgress(qint64,qint64)));
    connect(d->mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void QExtBreakpadHttpUploader::onUploadProgress(qint64 sent, qint64 total)
{
    qDebug("upload progress: %lld/%lld", sent, total);
}

void QExtBreakpadHttpUploader::onError(QNetworkReply::NetworkError err)
{
    qDebug() << err;
}

void QExtBreakpadHttpUploader::onUploadFinished()
{
    Q_D(QExtBreakpadHttpUploader);
    QString data = (QString)d->mReply->readAll();
    qDebug() << "Upload finished";
    qDebug() << "Answer: " << data;

    if(d->mReply->error() != QNetworkReply::NoError)
    {
        qWarning("Upload error: %d - %s", d->mReply->error(), qPrintable(d->mReply->errorString()));
    }
    else
    {
        qDebug() << "Upload to " << remoteUrl() << " success!";
        d->mFile->remove();
    }
    emit this->finished(data);

    d->mReply->close();
    d->mReply->deleteLater();
    d->mReply = 0;

    delete d->mFile;
    d->mFile = QEXT_NULLPTR;
}
