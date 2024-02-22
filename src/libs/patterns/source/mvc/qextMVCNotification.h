#ifndef _QEXTMVCNOTIFICATION_H
#define _QEXTMVCNOTIFICATION_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

#include <QString>

class QEXT_PATTERNS_API QExtMVCNotification : public QExtMVCNotificationInterface
{
public:
    QExtMVCNotification(const QString &notificationName, void *body);

    QString getNotificationName();

    void *getBody();

protected:
    QString m_notificationName;
    void *m_body;
};

#endif // _QEXTMVCNOTIFICATION_H
