#ifndef _QEXTQUICKIPCWIDGETITEM_P_H
#define _QEXTQUICKIPCWIDGETITEM_P_H

#include <QExtQuickControls/private/qextQuickWidgetItem_p.h>
#include <qextQuickIpcWidgetItem.h>

#include <QWindow>
#include <QWidget>
#include <QPointer>
#include <QVBoxLayout>

#include <QTimer>
#include <functional>
#include <cstdint>

class QEXT_QUICKCONTROLS_API QExtQuickIpcWidgetItemPrivate : public QExtQuickWidgetItemPrivate
{
public:
    using ProcessInterface = QExtQuickIpcWidgetItem::ProcessInterface;
    using State = ProcessInterface::State;
    using ConnectionEpoch = ProcessInterface::ConnectionEpoch;

    explicit QExtQuickIpcWidgetItemPrivate(QExtQuickIpcWidgetItem *q);
    ~QExtQuickIpcWidgetItemPrivate() override;

    void init();
    void initIpcCallbacks();
    void clearLayout();
    void detachChildWindow();
    void startProbeRetry();
    void stopProbeRetry();

    QString mProcessPath;
    QStringList mProcessArgs;
    QPointer<QVBoxLayout> mLayout;
    QPointer<QWindow> mChildWindow;
    QPointer<QWidget> mWrapperWidget;
    QPointer<QWindow> mChildWindowParent;
    QPointer<QWidget> mChildWindowContainer;
    ProcessInterface::SharedPtr mProcessInterface;

    State mState{State::Disconnected};
    ConnectionEpoch mConnectionEpoch{0};
    bool mShutdownGuard{false};

    QTimer *mProbeRetryTimer{nullptr};
    int mRetryCount{0};

private:
    Q_DECLARE_PUBLIC(QExtQuickIpcWidgetItem)
    Q_DISABLE_COPY(QExtQuickIpcWidgetItemPrivate)
};

#endif // _QEXTQUICKIPCWIDGETITEM_P_H
