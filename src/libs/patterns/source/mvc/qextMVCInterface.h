#ifndef _QEXTMVCINTERFACE_H
#define _QEXTMVCINTERFACE_H

#include <QList>
#include <QString>
#include <QObject>

class QExtMVCUpdateDataInterface : public QObject
{
public:
    /*virtual QString getType() const = 0;

    virtual QString setType(const QString &type) = 0;*/

    virtual QString getName() const = 0;
};

class QExtMVCViewComponentInterface
{
public:
    virtual void update(QExtMVCUpdateDataInterface *updateData) = 0;
};

class QExtMVCNotificationInterface
{
public:
    /**
     * Get the name of the QExtMVCNotificationInterface instance.
     * @return The name of the QExtMVCNotificationInterface instance
     */
    virtual QString getNotificationName() = 0;

    /**
     * Get the body of the QExtMVCNotificationInterface instance.
     * @return The body of the QExtMVCNotificationInterface instance
     */
    virtual void *getBody() = 0;
};

class QExtMVCMediatorInterface
{
public:
    virtual void registerViewComponent(QExtMVCViewComponentInterface *viewComponent) = 0;

    virtual QString getMediatorName() = 0;

    virtual QList<QString> getListNotificationInterests() = 0;

    virtual void handleNotification(QExtMVCNotificationInterface *notification) = 0;
};

class QExtMVCNotifierInterface
{
public:
    virtual void sendNotification(const QString &notificationName, void *body) = 0;
};

class QExtMVCObserverInterface
{
public:
    virtual void notifyObserver(QExtMVCNotificationInterface *notification) = 0;
};

class QExtMVCProxyInterface
{
public:
    /**
     * Get the name of the <c>IProxy</c> instance.
     * @return The <c>IProxy</c> instance name.
     */
    virtual QString getProxyName() = 0;
};

class QExtMVCCommandInterface
{
public:
    /**
     * Execute the <c>QExtMVCCommandInterface</c>'s logic to handle a given <c>QExtMVCNotificationInterface</c>.
     * @param notification An <c>QExtMVCNotificationInterface</c> to handle.
     */
    virtual void excute(QExtMVCNotificationInterface *notification) = 0;
};

class QExtMVCControllerInterface
{
public:
    /**
     * Register a particular <c>QExtMVCCommandInterface</c> class as the handler for a particular
     * <c>QExtMVCNotificationInterface</c>.
     * @param notificationName The name of the <c>QExtMVCNotificationInterface</c>.
     * @param command The <c>QExtMVCCommandInterface</c> to handle the <c>QExtMVCNotificationInterface</c>.
     */
    virtual void registerCommand(const QString &notificationName, QExtMVCCommandInterface *command) = 0;

    /**
     * Execute the <c>QExtMVCCommandInterface</c> previously registered as the handler for
     * <c>QExtMVCNotificationInterface</c>s with the given notification name.
     * @param notification The <c>QExtMVCNotificationInterface</c> to execute the associated
     * <c>QExtMVCCommandInterface</c> for.
     */
    virtual void excuteCommand(QExtMVCNotificationInterface *notification) = 0;

    /**
     * Check if a Command is registered for a given Notification.
     * @param notificationName The name of the <c>QExtMVCNotificationInterface</c>.
     * return Whether a Command is currently registered for the given notificationName
     */
    virtual bool hasCommand(const QString &notificationName) = 0;

    /**
     * Remove a previously registered <c>QExtMVCCommandInterface</c> to <c>QExtMVCNotificationInterface</c> mapping.
     * @param notificationName The name of the QExtMVCNotificationInterface.
     * return Whether a Command is currently registered for the given notificationName
     */
    virtual void removeCommand(const QString &notificationName) = 0;
};

class QExtMVCModelInterface
{
public:
    /**
     * Register an <c>IProxy</c> instance with the <c>QExtMVCModel</c>.
     * @param proxy A reference to the proxy object to be held by the <c>QExtMVCModel</c>.
     */
    virtual void registerProxy(QExtMVCProxyInterface *proxy) = 0;

    /**
     * Retrieve an <c>IProxy</c> instance from the QExtMVCModel.
     * @param proxyName The name of the proxy to retrieve.
     */
    virtual QExtMVCProxyInterface *retrieveProxy(const QString &proxyName) = 0;

    /**
     * Check if a Proxy is registered.
     * @param proxyName The name of the proxy to check for.
     * @return Whether a Proxy is currently registered with the given <c>proxyName</c>.
     */
    virtual bool hasProxy(const QString &proxyName) = 0;

    /**
     * Check if a Proxy is registered.
     * @param proxyName The name of the proxy to check for.
     * @return Whether a Proxy is currently registered with the given <c>proxyName</c>.
     */
    virtual void removeProxy(const QString &proxyName) = 0;
};

class QExtMVCInterface
{
public:
    virtual void registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName) = 0;

    virtual void removeObserver(const QString &notificationName) = 0;

    virtual void notifyObservers(QExtMVCNotificationInterface *notification) = 0;

    virtual void registerMediator(QExtMVCMediatorInterface *mediator) = 0;

    virtual QExtMVCMediatorInterface *retrieveMediator(const QString &mediatorName) = 0;

    virtual bool hasMediator(const QString &mediatorName) = 0;

    virtual void removeMediator(const QString &mediatorName) = 0;
};

class QExtMVCFacadeInterface : public QExtMVCNotifierInterface
{
public:
    virtual void registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName) = 0;

    virtual void removeObserver(const QString &notificationName) = 0;

    virtual void notifyObservers(QExtMVCNotificationInterface *notification) = 0;

    virtual void registerMediator(QExtMVCMediatorInterface *mediator) = 0;

    virtual QExtMVCMediatorInterface *retrieveMediator(const QString &mediatorName) = 0;

    virtual bool hasMediator(const QString &mediatorName) = 0;

    virtual void removeMediator(const QString &mediatorName) = 0;

    virtual void registerCommand(const QString &notificationName, QExtMVCCommandInterface *command) = 0;

    virtual bool hasCommand(const QString &notificationName) = 0;

    virtual void removeCommand(const QString &notificationName) = 0;

    virtual void registerProxy(QExtMVCProxyInterface *proxy) = 0;

    virtual QExtMVCProxyInterface *retrieveProxy(const QString &proxyName) = 0;

    virtual bool hasProxy(const QString &proxyName) = 0;

    virtual void removeProxy(const QString &proxyName) = 0;
};

#endif // _QEXTMVCINTERFACE_H
