#ifndef _QEXTQUICKIPCWIDGETITEM_H
#define _QEXTQUICKIPCWIDGETITEM_H

#include <qextQuickWidgetItem.h>

#include <QSharedPointer>
#include <functional>
#include <cstdint>
#include <QLoggingCategory>

class QExtQuickIpcWidgetItemPrivate;

class QEXT_QUICKCONTROLS_API QExtQuickIpcWidgetItem : public QExtQuickWidgetItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QString processPath READ processPath WRITE setProcessPath NOTIFY processPathChanged)
    Q_PROPERTY(QStringList processArgs READ processArgs WRITE setProcessArgs NOTIFY processArgsChanged)

public:
    struct ProcessInterface
    {
        using SharedPtr = QSharedPointer<ProcessInterface>;
        using ConnectionEpoch = uint64_t;

        enum Command { Show = 0, Resize = 1, Custom = 1000 };
        enum State { Disconnected, Connecting, Connected, Disconnecting };

        virtual ~ProcessInterface() = default;

        // === Lifecycle ===
        virtual bool start() { return false; }
        virtual void stop() {}
        virtual bool probe() { return false; }
        virtual bool isAlive() const { return false; }
        virtual void disconnect() {}

        // === Callback registration ===
        virtual void setWIdCallback(std::function<void(quintptr)> callback) = 0;
        virtual void setLogCallback(std::function<void(const QString &)> callback) = 0;
        virtual void setReadyCallback(std::function<void()> callback) = 0;
        virtual void setLostCallback(std::function<void()> callback) = 0;

        // === Command channel ===
        virtual void sendShowCommand() = 0;
        virtual void sendResizeCommand(int width, int height) = 0;
        virtual void *commandChannel() { return nullptr; }

        // === Texture frame transport (stubs, default false/null) ===
        virtual bool initFrameTransport() { return false; }
        virtual void shutdownFrameTransport() {}
        virtual bool isFrameTransportAvailable() const { return false; }
        virtual void *acquireFrame() { return nullptr; }
        virtual void releaseFrame(void * /*handle*/) {}
        virtual void setFrameAvailableCallback(std::function<void()> /*callback*/) {}
        virtual void destroyGlResources() {}
    };

    explicit QExtQuickIpcWidgetItem(QQuickItem *parent = nullptr);
    ~QExtQuickIpcWidgetItem() override;

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString processPath() const;
    QStringList processArgs() const;

    ProcessInterface::SharedPtr processInterface() const;

    static ProcessInterface::SharedPtr createDefaultHandler();

Q_SIGNALS:
    void processPathChanged(const QString &path);
    void processArgsChanged(const QStringList &args);

    void asyncUpdateWidgetGeometry(QPrivateSignal);
    void asyncSetWidgetWId(quintptr wId, QPrivateSignal);

public Q_SLOTS:
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
Q_DECLARE_LOGGING_CATEGORY(lcQExtQuickIpc)

#endif // _QEXTQUICKIPCWIDGETITEM_H
