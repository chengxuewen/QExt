#ifndef _QEXTMVCNOTIFIER_H
#define _QEXTMVCNOTIFIER_H

#include <qextPatternsGlobal.h>

#include <QString>

class QExtMVCFacadeInterface;
class QExtMVCNotificationInterface;

class QEXT_PATTERNS_API QExtMVCNotifier
{
public:
    QExtMVCNotifier();

    void sendNotification(const QString &notificationName, void *body);

protected:
    QExtMVCFacadeInterface *m_facade;
};

#endif // _QEXTMVCNOTIFIER_H
