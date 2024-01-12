#include <qextPatternView.h>
#include <qextPatternInterface.h>
#include <qextPatternMediator.h>

QExtPatternView *QExtPatternView::m_instance;

QExtPatternView::QExtPatternView()
{
}

QExtPatternView *QExtPatternView::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new QExtPatternView();
    }

    return m_instance;
}

void QExtPatternView::registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName)
{
    if (observer == NULL)
    {
        return;
    }

    if (m_observerMap.contains(notificationName))
    {
        QList<QExtPatternObserverInterface *> observers = m_observerMap[notificationName];
        if (observers.contains(observer))
        {
            return;
        }

        observers.append(observer);

        m_observerMap[notificationName] = observers;
    }
    else
    {
        QList<QExtPatternObserverInterface *> observers;

        observers.append(observer);

        m_observerMap[notificationName] = observers;
    }
}

void QExtPatternView::removeObserver(const QString &notificationName)
{
    if (!m_observerMap.contains(notificationName))
    {
        return;
    }

    m_observerMap.remove(notificationName);
}

void QExtPatternView::notifyObservers(QExtPatternNotificationInterface *notification)
{
    if (!m_observerMap.contains(notification->getNotificationName()))
    {
        return;
    }

    QList<QExtPatternObserverInterface *> observers = m_observerMap[notification->getNotificationName()];

    int count = observers.size();
    for (int i = 0; i < count; i++)
    {
        observers.at(i)->notifyObserver(notification);
    }
}

void QExtPatternView::registerMediator(QExtPatternMediatorInterface *mediator)
{
    if (mediator == NULL)
    {
        return;
    }

    m_mediatorMap[mediator->getMediatorName()] = mediator;

    QList<QString> notificationInterests = mediator->getListNotificationInterests();

    int count = notificationInterests.size();
    for (int i = 0; i < count; i++)
    {
        registerObserver((QExtPatternObserverInterface *)((QExtPatternMediator *)mediator),
                         notificationInterests.at(i));
    }
}

QExtPatternMediatorInterface *QExtPatternView::retrieveMediator(const QString &mediatorName)
{
    if (!hasMediator(mediatorName))
    {
        return NULL;
    }

    return m_mediatorMap[mediatorName];
}

bool QExtPatternView::hasMediator(const QString &mediatorName)
{
    return m_mediatorMap.contains(mediatorName);
}

void QExtPatternView::removeMediator(const QString &mediatorName)
{
    m_mediatorMap.remove(mediatorName);
}
