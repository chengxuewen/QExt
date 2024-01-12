#ifndef _QEXTPATTERNFACADE_H
#define _QEXTPATTERNFACADE_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

#include <QString>

class QExtPatternViewInterface;
class QExtPatternModelInterface;
class QExtPatternControllerInterface;

class QEXT_PATTERN_API QExtPatternFacade : public QExtPatternFacadeInterface
{
public:
    static QExtPatternFacade *instance();

    void registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName);

    void removeObserver(const QString &notificationName);

    void notifyObservers(QExtPatternNotificationInterface *notification);

    void registerMediator(QExtPatternMediatorInterface *mediator);

    QExtPatternMediatorInterface *retrieveMediator(const QString &mediatorName);

    bool hasMediator(const QString &mediatorName);

    void removeMediator(const QString &mediatorName);

    void registerCommand(const QString &notificationName, QExtPatternCommandInterface *command);

    bool hasCommand(const QString &notificationName);

    void removeCommand(const QString &notificationName);

    void registerProxy(QExtPatternProxyInterface *proxy);

    QExtPatternProxyInterface *retrieveProxy(const QString &proxyName);

    bool hasProxy(const QString &proxyName);

    void removeProxy(const QString &proxyName);

    void sendNotification(const QString &notificationName, void *body);

    void startUp();

protected:
    virtual void initializeMediator();
    virtual void initializeCommand();
    virtual void initializeProxy();

protected:
    QExtPatternFacade();

private:
    QExtPatternViewInterface *m_view;
    QExtPatternControllerInterface *m_controller;
    QExtPatternModelInterface *m_model;
    static QExtPatternFacade *m_instance;
};

#endif // _QEXTPATTERNFACADE_H
