#ifndef _QEXTPATTERNNOTIFIER_H
#define _QEXTPATTERNNOTIFIER_H

#include <qextPatternGlobal.h>

#include <QString>

class QExtPatternFacadeInterface;
class QExtPatternNotificationInterface;

class QEXT_PATTERN_API QExtPatternNotifier
{
public:
    QExtPatternNotifier();

    void sendNotification(const QString &notificationName, void *body);

protected:
    QExtPatternFacadeInterface *m_facade;
};

#endif // _QEXTPATTERNNOTIFIER_H
