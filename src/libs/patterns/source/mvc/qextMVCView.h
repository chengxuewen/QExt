#ifndef _QEXTMVCVIEW_H
#define _QEXTMVCVIEW_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

#include <QString>
#include <QMap>
#include <QList>

class QExtMVCNotificationInterface;

class QEXT_PATTERNS_API QExtMVCView : public QExtMVCInterface
{
public:
    static QExtMVCView *instance();

    void registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName);

    void removeObserver(const QString &notificationName);

    void notifyObservers(QExtMVCNotificationInterface *notification);

    void registerMediator(QExtMVCMediatorInterface *mediator);

    QExtMVCMediatorInterface *retrieveMediator(const QString &mediatorName);

    bool hasMediator(const QString &mediatorName);

    void removeMediator(const QString &mediatorName);

private:
    QExtMVCView();

private:
    QMap<QString, QExtMVCMediatorInterface *> m_mediatorMap;
    QMap<QString, QList<QExtMVCObserverInterface *> > m_observerMap;
    static QExtMVCView *m_instance;
};

#endif // _QEXTMVCVIEW_H
