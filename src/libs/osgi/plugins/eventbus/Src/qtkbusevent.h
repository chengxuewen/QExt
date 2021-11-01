#ifndef QTKBUSEVENT_H
#define QTKBUSEVENT_H

#include "qtkeventbus_global.h"
#include <QTKPluginFramework/Service/Event/QTKEvent>

#include <QMap>
#include <QVariant>
#include <QStringList>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKBusEventData;

class QTK_EVENTBUS_EXPORT QTKBusEvent : public QTKEvent
{
public:
    QTKBusEvent();
    ~QTKBusEvent();

    QTKBusEvent(const QString &strTopic, const QTKDictionary &properties = QTKDictionary());
    QTKBusEvent(const QTKBusEvent &event);
    QTKBusEvent(QString strTopic, int iEventType, int iSignatureType, QObject *pbjectPointer, QString strSignature);

    QTKBusEvent& operator=(const QTKBusEvent &event);

    void setEventType(int iEventType);
    int eventType() const;
    bool isEventLocal() const;

    void setEventTopic(QString strTopic);
    QString eventTopic() const;

    QVariant &operator[](QString strKey);

private:
    QSharedDataPointer<QTKBusEventData> d;
};

#endif // QTKBUSEVENT_H
