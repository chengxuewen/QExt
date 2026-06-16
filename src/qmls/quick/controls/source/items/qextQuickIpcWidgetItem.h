#ifndef _QEXTQUICKIPCWIDGETITEM_H
#define _QEXTQUICKIPCWIDGETITEM_H

#include <qextQuickWidgetItem.h>

#include <QProcess>

#include <functional>

class QExtQuickIpcWidgetItemPrivate;

class QEXT_QUICKCONTROLS_API QExtQuickIpcWidgetItem : public QExtQuickWidgetItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QString processPath READ processPath WRITE setProcessPath NOTIFY processPathChanged)
    Q_PROPERTY(QStringList processArgs READ processArgs WRITE setProcessArgs NOTIFY processArgsChanged)
    Q_PROPERTY(QString workingPath READ workingPath WRITE setWorkingPath NOTIFY workingPathChanged)

public:
    struct ProcessInterface 
    {
        using SharedPtr = QSharedPointer<ProcessInterface>;

    virtual ~ProcessInterface() = default;

    virtual bool start(const QString &path, const QStringList &args) = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
    virtual bool isStopped() const = 0;

    virtual void setWorkingPath(const QString &path) = 0;
    virtual QString workingPath() const = 0;

    // WId discovery callback (implementation-specific: QProcess stdout / DDS topic / file / pipe)
    virtual void setWIdCallback(std::function<void(WId)> callback) = 0;

    // Child process stdout/stderr callback
    virtual void setLogCallback(std::function<void(const QString &)> callback) = 0;

    // Send show command to child process (implementation-specific)
    virtual void sendShowCommand() = 0;
    virtual void sendResizeCommand(int width, int height) = 0;
};

    explicit QExtQuickIpcWidgetItem(QQuickItem *parent = nullptr);
    ~QExtQuickIpcWidgetItem() override;

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString processPath() const;
    QStringList processArgs() const;
    QString workingPath() const;

    ProcessInterface::SharedPtr processInterface() const;

Q_SIGNALS:
    void workingPathChanged(const QString &path);
    void processPathChanged(const QString &path);
    void processArgsChanged(const QStringList &args);

    void asyncUpdateWidgetGeometry(QPrivateSignal);
    void asyncSetWidgetWId(WId wId, QPrivateSignal);

public Q_SLOTS:
    void setWorkingPath(const QString &path);
    void setProcessPath(const QString &path);
    void setProcessArgs(const QStringList &args);
    void setProcessInterface(const ProcessInterface::SharedPtr &interface);

    bool startProcess();

protected:
    QExtQuickIpcWidgetItem(QExtQuickIpcWidgetItemPrivate *d, QQuickItem *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickIpcWidgetItem)
    Q_DISABLE_COPY(QExtQuickIpcWidgetItem)
};


class QEXT_QUICKCONTROLS_API QExtQuickIpcWidgetItemProcessHandler : public QObject, 
    public QExtQuickIpcWidgetItem::ProcessInterface
{
    Q_OBJECT
public:
    explicit QExtQuickIpcWidgetItemProcessHandler(QObject *parent = nullptr);
    ~QExtQuickIpcWidgetItemProcessHandler() override;

    // QExtProcessInterface interface
    bool start(const QString &path, const QStringList &args) override;
    void stop() override;
    bool isRunning() const override;
    bool isStopped() const override;

    void setWorkingPath(const QString &path) override;
    QString workingPath() const override;

    void setWIdCallback(std::function<void(WId)> callback) override;
    void setLogCallback(std::function<void(const QString &)> callback) override;
    void sendShowCommand() override;
    void sendResizeCommand(int width, int height) override;

Q_SIGNALS:
    void started();
    void stopped();
    void errorOccurred(const QString &error);

private Q_SLOTS:
    void onReadyReadStandardOutput();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessErrorOccurred(QProcess::ProcessError error);
    void onKillTimeout();

private:
    std::unique_ptr<QProcess> mProcess;
    std::unique_ptr<QTimer> mKillTimer;
    std::function<void(WId)> mWidCallback;
    std::function<void(const QString &)> mLogCallback;
};

#endif // _QEXTQUICKIPCWIDGETITEM_H
