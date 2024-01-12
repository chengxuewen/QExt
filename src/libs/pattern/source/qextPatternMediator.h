#ifndef _QEXTPATTERNMEDIATOR_H
#define _QEXTPATTERNMEDIATOR_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>
#include <qextPatternNotifier.h>

#include <QString>

class QEXT_PATTERN_API QExtPatternMediator
    : public QExtPatternMediatorInterface, public QExtPatternNotifier, public QExtPatternObserverInterface
{
public:
    void registerViewComponent(QExtPatternViewComponentInterface *viewComponent);

    QString getMediatorName();

    virtual QList<QString> getListNotificationInterests() = 0;

    virtual void handleNotification(QExtPatternNotificationInterface *notification) = 0;

    void notifyObserver(QExtPatternNotificationInterface *notification);

protected:
    static QString MEDIATOR_NAME;
    QExtPatternViewComponentInterface *m_viewComponent;
};

#endif // _QEXTPATTERNMEDIATOR_H
