#ifndef QTKEVENTDISPATCHER_H
#define QTKEVENTDISPATCHER_H

#include "qtkeventdefinitions.h"

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKEventDispatcher : public QObject
{
    Q_OBJECT

public:
    QTKEventDispatcher();
    virtual ~QTKEventDispatcher();

    bool addObserver(QTKBusEvent &props);
    bool removeObserver(QTKBusEvent &props);
    bool removeObserver(const QObject *pObj, const QString strTopic, bool bQtDisconnect = true);
    bool removeSignal(const QObject *pObj, const QString strTopic = "", bool bQtDisconnect = true);

    bool registerSignal(QTKBusEvent &props);
    bool removeSignal(QTKBusEvent &props);

    bool isLocalSignalPresent(const QString strTopic) const;

    virtual void notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList = nullptr,
                             QTKGenericReturnArgument *pReturnArg = nullptr) const;

    void resetHashes();

Q_SIGNALS:
    void notifyDefaultEvent();
    void remoteCommunicationDone();
    void remoteCommunicationFailed();

protected:
    virtual void initializeGlobalEvents();

    bool removeEventItem(QTKBusEvent &props);

    QTKEventItemListType signalItemProperty(const QString strTopic) const;

private:
    bool isSignaturePresent(QTKBusEvent &props) const;

    bool disconnectSignal(QTKBusEvent &props);

    bool disconnectCallback(QTKBusEvent &props);

    bool removeFromHash(QTKEventsHashType *pHash, const QObject *pObj, const QString strTopic, bool bQtDisconnect = true);

    QTKEventsHashType m_callbacksHash; ///< Callbacks' hash for receiving events like updates or refreshes.
    QTKEventsHashType m_signalsHash; ///< Signals' hash for sending events.
};

inline QTKEventItemListType QTKEventDispatcher::signalItemProperty(const QString strTopic) const {
    return m_signalsHash.values(strTopic);
}

} // namespace QTKEventBus

#endif // QTKEVENTDISPATCHER_H
