#ifndef _QEXTPATTERNNOTIFICATION_H
#define _QEXTPATTERNNOTIFICATION_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

#include <QString>

class QEXT_PATTERN_API QExtPatternNotification : public QExtPatternNotificationInterface
{
public:
    QExtPatternNotification(const QString &notificationName, void *body);

    QString getNotificationName();

    void *getBody();

protected:
    QString m_notificationName;
    void *m_body;
};

#endif // _QEXTPATTERNNOTIFICATION_H
