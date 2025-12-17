#include <qextSingleApp.h>

#include <singleapplication.h>

class QExtSingleAppPrivate
{
    QExtSingleApp * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtSingleApp)
    QEXT_DECLARE_DISABLE_MOVE(QExtSingleAppPrivate)
public:
    explicit QExtSingleAppPrivate(QExtSingleApp *p);
    virtual ~QExtSingleAppPrivate();

    QScopedPointer<SingleApplication> mSingleApplication;
};

QExtSingleAppPrivate::QExtSingleAppPrivate(QExtSingleApp *p)
    : q_ptr(p)
{
}

QExtSingleAppPrivate::~QExtSingleAppPrivate()
{
}

QExtSingleApp::QExtSingleApp(int &argc, char *argv[])
    : dd_ptr(new QExtSingleAppPrivate(this))
{
    Q_D(QExtSingleApp);
    d->mSingleApplication.reset(new SingleApplication(argc, argv));
    connect(d->mSingleApplication.data(), &SingleApplication::instanceStarted, this, &QExtSingleApp::instanceStarted);
    connect(d->mSingleApplication.data(), &SingleApplication::receivedMessage, this, &QExtSingleApp::receivedMessage);
}

QExtSingleApp::~QExtSingleApp()
{
}

bool QExtSingleApp::sendMessage(const QByteArray &message)
{
    Q_D(QExtSingleApp);
    return d->mSingleApplication->sendMessage(message);
}

