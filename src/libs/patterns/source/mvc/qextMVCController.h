#ifndef _QEXTMVCCONTROLLER_H
#define _QEXTMVCCONTROLLER_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

#include <QString>
#include <QMap>

class QExtMVCInterface;
class QEXT_PATTERNS_API QExtMVCController : public QExtMVCControllerInterface
{
public:
    static QExtMVCController *instance();

    void registerCommand(const QString &notificationName, QExtMVCCommandInterface *command);

    void excuteCommand(QExtMVCNotificationInterface *notification);

    bool hasCommand(const QString &notificationName);

    void removeCommand(const QString &notificationName);

private:
    QExtMVCController();

private:
    QMap<QString, QExtMVCCommandInterface *> m_commandMap;
    static QExtMVCController *m_instance;
    QExtMVCInterface *m_view;
};

#endif // _QEXTMVCCONTROLLER_H
