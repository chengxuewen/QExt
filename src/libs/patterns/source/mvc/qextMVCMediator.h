#ifndef _QEXTMVCMEDIATOR_H
#define _QEXTMVCMEDIATOR_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>
#include <qextMVCNotifier.h>

#include <QString>

class QEXT_PATTERNS_API QExtMVCMediator
    : public QExtMVCMediatorInterface, public QExtMVCNotifier, public QExtMVCObserverInterface
{
public:
    void registerViewComponent(QExtMVCViewComponentInterface *viewComponent);

    QString getMediatorName();

    virtual QList<QString> getListNotificationInterests() = 0;

    virtual void handleNotification(QExtMVCNotificationInterface *notification) = 0;

    void notifyObserver(QExtMVCNotificationInterface *notification);

protected:
    static QString MEDIATOR_NAME;
    QExtMVCViewComponentInterface *m_viewComponent;
};

#endif // _QEXTMVCMEDIATOR_H
