#ifndef _QEXTMVCFACADE_H
#define _QEXTMVCFACADE_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

#include <QString>

class QExtMVCInterface;
class QExtMVCModelInterface;
class QExtMVCControllerInterface;

class QEXT_PATTERNS_API QExtMVCFacade : public QExtMVCFacadeInterface
{
public:
    static QExtMVCFacade *instance();

    void registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName);

    void removeObserver(const QString &notificationName);

    void notifyObservers(QExtMVCNotificationInterface *notification);

    void registerMediator(QExtMVCMediatorInterface *mediator);

    QExtMVCMediatorInterface *retrieveMediator(const QString &mediatorName);

    bool hasMediator(const QString &mediatorName);

    void removeMediator(const QString &mediatorName);

    void registerCommand(const QString &notificationName, QExtMVCCommandInterface *command);

    bool hasCommand(const QString &notificationName);

    void removeCommand(const QString &notificationName);

    void registerProxy(QExtMVCProxyInterface *proxy);

    QExtMVCProxyInterface *retrieveProxy(const QString &proxyName);

    bool hasProxy(const QString &proxyName);

    void removeProxy(const QString &proxyName);

    void sendNotification(const QString &notificationName, void *body);

    void startUp();

protected:
    virtual void initializeMediator();
    virtual void initializeCommand();
    virtual void initializeProxy();

protected:
    QExtMVCFacade();

private:
    QExtMVCInterface *m_view;
    QExtMVCControllerInterface *m_controller;
    QExtMVCModelInterface *m_model;
    static QExtMVCFacade *m_instance;
};

#endif // _QEXTMVCFACADE_H
