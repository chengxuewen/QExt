#ifndef _QEXTPATTERNVIEW_H
#define _QEXTPATTERNVIEW_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

#include <QString>
#include <QMap>
#include <QList>

class QExtPatternNotificationInterface;

class QEXT_PATTERN_API QExtPatternView : public QExtPatternViewInterface
{
public:
    static QExtPatternView *instance();

    void registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName);

    void removeObserver(const QString &notificationName);

    void notifyObservers(QExtPatternNotificationInterface *notification);

    void registerMediator(QExtPatternMediatorInterface *mediator);

    QExtPatternMediatorInterface *retrieveMediator(const QString &mediatorName);

    bool hasMediator(const QString &mediatorName);

    void removeMediator(const QString &mediatorName);

private:
    QExtPatternView();

private:
    QMap<QString, QExtPatternMediatorInterface *> m_mediatorMap;
    QMap<QString, QList<QExtPatternObserverInterface *> > m_observerMap;
    static QExtPatternView *m_instance;
};

#endif // _QEXTPATTERNVIEW_H
