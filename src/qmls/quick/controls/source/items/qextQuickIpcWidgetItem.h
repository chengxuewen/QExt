#ifndef _QEXTQUICKIPCWIDGETITEM_H
#define _QEXTQUICKIPCWIDGETITEM_H

#include <qextQuickWidgetItem.h>

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

        virtual QString workingPath() const = 0;
        virtual void setWorkingPath(const QString &path) = 0;
        
        virtual QVariantMap config() const = 0;
        virtual void setConfig(const QVariantMap &config) = 0;

        virtual void setWIdCallback(std::function<void(quintptr)> callback) = 0;
        virtual void setLogCallback(std::function<void(const QString &)> callback) = 0;
        
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
    void asyncSetWidgetWId(quintptr wId, QPrivateSignal);

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
    Q_DECLARE_PRIVATE(QExtQuickIpcWidgetItem)
    Q_DISABLE_COPY(QExtQuickIpcWidgetItem)
};

#endif // _QEXTQUICKIPCWIDGETITEM_H
