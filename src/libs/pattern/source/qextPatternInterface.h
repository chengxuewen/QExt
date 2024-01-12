#ifndef _QEXTPATTERNINTERFACE_H
#define _QEXTPATTERNINTERFACE_H

#include <QList>
#include <QString>
#include <QObject>

class QExtPatternUpdateDataInterface : public QObject
{
public:
    /*virtual QString getType() const = 0;

    virtual QString setType(const QString &type) = 0;*/

    virtual QString getName() const = 0;
};

class QExtPatternViewComponentInterface
{
public:
    virtual void update(QExtPatternUpdateDataInterface *updateData) = 0;
};

class QExtPatternNotificationInterface
{
public:
    /**
     * Get the name of the QExtPatternNotificationInterface instance.
     * @return The name of the QExtPatternNotificationInterface instance
     */
    virtual QString getNotificationName() = 0;

    /**
     * Get the body of the QExtPatternNotificationInterface instance.
     * @return The body of the QExtPatternNotificationInterface instance
     */
    virtual void *getBody() = 0;
};

class QExtPatternMediatorInterface
{
public:
    virtual void registerViewComponent(QExtPatternViewComponentInterface *viewComponent) = 0;

    virtual QString getMediatorName() = 0;

    virtual QList<QString> getListNotificationInterests() = 0;

    virtual void handleNotification(QExtPatternNotificationInterface *notification) = 0;
};

class QExtPatternNotifierInterface
{
public:
    virtual void sendNotification(const QString &notificationName, void *body) = 0;
};

class QExtPatternObserverInterface
{
public:
    virtual void notifyObserver(QExtPatternNotificationInterface *notification) = 0;
};

class QExtPatternProxyInterface
{
public:
    /**
     * Get the name of the <c>IProxy</c> instance.
     * @return The <c>IProxy</c> instance name.
     */
    virtual QString getProxyName() = 0;
};

class QExtPatternCommandInterface
{
public:
    /**
     * Execute the <c>QExtPatternCommandInterface</c>'s logic to handle a given <c>QExtPatternNotificationInterface</c>.
     * @param notification An <c>QExtPatternNotificationInterface</c> to handle.
     */
    virtual void excute(QExtPatternNotificationInterface *notification) = 0;
};

class QExtPatternControllerInterface
{
public:
    /**
     * Register a particular <c>QExtPatternCommandInterface</c> class as the handler for a particular <c>QExtPatternNotificationInterface</c>.
     * @param notificationName The name of the <c>QExtPatternNotificationInterface</c>.
     * @param command The <c>QExtPatternCommandInterface</c> to handle the <c>QExtPatternNotificationInterface</c>.
     */
    virtual void registerCommand(const QString &notificationName, QExtPatternCommandInterface *command) = 0;

    /**
     * Execute the <c>QExtPatternCommandInterface</c> previously registered as the handler for <c>QExtPatternNotificationInterface</c>s with the given notification name.
     * @param notification The <c>QExtPatternNotificationInterface</c> to execute the associated <c>QExtPatternCommandInterface</c> for.
     */
    virtual void excuteCommand(QExtPatternNotificationInterface *notification) = 0;

    /**
     * Check if a Command is registered for a given Notification.
     * @param notificationName The name of the <c>QExtPatternNotificationInterface</c>.
     * return Whether a Command is currently registered for the given notificationName
     */
    virtual bool hasCommand(const QString &notificationName) = 0;

    /**
     * Remove a previously registered <c>QExtPatternCommandInterface</c> to <c>QExtPatternNotificationInterface</c> mapping.
     * @param notificationName The name of the QExtPatternNotificationInterface.
     * return Whether a Command is currently registered for the given notificationName
     */
    virtual void removeCommand(const QString &notificationName) = 0;
};

class QExtPatternModelInterface
{
public:
    /**
     * Register an <c>IProxy</c> instance with the <c>QExtPatternModel</c>.
     * @param proxy A reference to the proxy object to be held by the <c>QExtPatternModel</c>.
     */
    virtual void registerProxy(QExtPatternProxyInterface *proxy) = 0;

    /**
     * Retrieve an <c>IProxy</c> instance from the QExtPatternModel.
     * @param proxyName The name of the proxy to retrieve.
     */
    virtual QExtPatternProxyInterface *retrieveProxy(const QString &proxyName) = 0;

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

class QExtPatternViewInterface
{
public:
    virtual void registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName) = 0;

    virtual void removeObserver(const QString &notificationName) = 0;

    virtual void notifyObservers(QExtPatternNotificationInterface *notification) = 0;

    virtual void registerMediator(QExtPatternMediatorInterface *mediator) = 0;

    virtual QExtPatternMediatorInterface *retrieveMediator(const QString &mediatorName) = 0;

    virtual bool hasMediator(const QString &mediatorName) = 0;

    virtual void removeMediator(const QString &mediatorName) = 0;
};

class QExtPatternFacadeInterface : public QExtPatternNotifierInterface
{
public:
    virtual void registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName) = 0;

    virtual void removeObserver(const QString &notificationName) = 0;

    virtual void notifyObservers(QExtPatternNotificationInterface *notification) = 0;

    virtual void registerMediator(QExtPatternMediatorInterface *mediator) = 0;

    virtual QExtPatternMediatorInterface *retrieveMediator(const QString &mediatorName) = 0;

    virtual bool hasMediator(const QString &mediatorName) = 0;

    virtual void removeMediator(const QString &mediatorName) = 0;

    virtual void registerCommand(const QString &notificationName, QExtPatternCommandInterface *command) = 0;

    virtual bool hasCommand(const QString &notificationName) = 0;

    virtual void removeCommand(const QString &notificationName) = 0;

    virtual void registerProxy(QExtPatternProxyInterface *proxy) = 0;

    virtual QExtPatternProxyInterface *retrieveProxy(const QString &proxyName) = 0;

    virtual bool hasProxy(const QString &proxyName) = 0;

    virtual void removeProxy(const QString &proxyName) = 0;
};

#endif // _QEXTPATTERNINTERFACE_H
