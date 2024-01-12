#ifndef _QEXTPATTERNCONTROLLER_H
#define _QEXTPATTERNCONTROLLER_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

#include <QString>
#include <QMap>

class QExtPatternViewInterface;
class QEXT_PATTERN_API QExtPatternController : public QExtPatternControllerInterface
{
public:
    static QExtPatternController *instance();

    void registerCommand(const QString &notificationName, QExtPatternCommandInterface *command);

    void excuteCommand(QExtPatternNotificationInterface *notification);

    bool hasCommand(const QString &notificationName);

    void removeCommand(const QString &notificationName);

private:
    QExtPatternController();

private:
    QMap<QString, QExtPatternCommandInterface *> m_commandMap;
    static QExtPatternController *m_instance;
    QExtPatternViewInterface *m_view;
};

#endif // _QEXTPATTERNCONTROLLER_H
