/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#ifndef QTKEVENTADMIN_H
#define QTKEVENTADMIN_H

#include "../../qtkpluginframework_global.h"
#include "qtkevent.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKEventAdmin class
 * The Event Admin service. Plugins wishing to publish events can either
 * obtain the Event Admin service and call one of the event delivery methods
 * or publish a Qt signal for a specific event topic.
 *
 */
class QTKEventAdmin
{
public:
    virtual ~QTKEventAdmin() {}

    /**
     * @brief postEvent
     * Initiate asynchronous, ordered delivery of an event. This method returns
     * to the caller before delivery of the event is completed. Events are
     * delivered in the order that they are received by this method.
     *
     * @param event The event to send to all listeners which subscribe to the
     *        topic of the event.
     *
     */
    virtual void postEvent(const QTKEvent &event) = 0;

    /**
     * @brief sendEvent
     * Initiate synchronous delivery of an event. This method does not return to
     * the caller until delivery of the event is completed.
     *
     * @param event The event to send to all listeners which subscribe to the
     *        topic of the event.
     *
     */
    virtual void sendEvent(const QTKEvent &event) = 0;

    /**
     * @brief publishSignal
     * Publish (register) a Qt signal for event delivery. Emitting the signal
     * has the same effect as calling postEvent() if <code>type</code> is
     * Qt::QueuedConnection and as sendEvent() if <code>type</code> is
     * Qt::DirectConnection.
     *
     * The signal will be associated with the given topic and must have the
     * following signature:
     * \code
     * someSignal(const ctkDictionary& props)
     * \endcode
     * where <code>props</code> will be used to construct a ctkEvent class which
     * will additionally have the EVENT_TOPIC property set to the given <code>topic</code>.
     *
     * This method can be called multiple times for the same signal to publish
     * it under multiple topics. In that case, emitting the signal will result in
     * multiple events being send.
     *
     * @param pPublisher The owner of the signal.
     * @param psSignal The signal in normalized form.
     * @param strTopic The event topic to use.
     * @param eType Qt::QueuedConnection for asynchronous delivery and
     *        Qt::DirectConnection for synchronous delivery.
     *
     * @see unpublishSignal()
     */
    virtual void publishSignal(const QObject *pPublisher, const char *psSignal,
                               const QString &strTopic,
                               Qt::ConnectionType eType = Qt::QueuedConnection) = 0;

    /**
     * @brief unpublishSignal
     * Unpublish (unregister) a previously published signal. After unpublishing a
     * signal, no events will be send when the signal is emitted.
     *
     * @param pPublisher The owner of the signal.
     * @param psSignal The signal in normalized form. If the signal is <code>nullptr</code>
     *        all signals from the given publisher published under the given
     *        <code>topic</code> will be unpublished.
     * @param strTopic The event topic under which the given <code>signal</code> was
     *        published. If the <code>topic</code> is empty, the signal is
     *        unpublished for all topics it was previously pubished under.
     *
     * @see publishSlot()
     */
    virtual void unpublishSignal(const QObject *pPublisher, const char *psSignal = 0,
                                 const QString &strTopic = "") = 0;

    /**
     * @brief subscribeSlot
     * Subsribe for (observe) events. The slot is called whenever an event is sent
     * which matches the topic string and LDAP search expression contained
     * in the properties. Slots are executed either in the event delivery thread of
     * the Event Admin implemenation or in the subscriber's thread, depending on
     * the <code>type</code> argument.
     *
     * Slots should be registered with a property ctkEventConstants::EVENT_TOPIC.
     * The value being a QString or QStringList object that describes which
     * topics the slot is interested in. A wildcard ('*' \\u002A) may be used as
     * the last token of a topic name, for example com/action&#47*. This matches any
     * topic that shares the same first tokens. For example, com/action&#47* matches
     * com/action/listen. Slots which have not been specified with the EVENT_TOPIC
     * property must not receive events.
     * The value of each entry in the EVENT_TOPIC property must conform to the
     * following grammar:
     * \verbatim
     * topic-scope ::= '*' | ( topic '&#47*' ? )
     * \endverbatim
     *
     * Slots can also be registered with a property named ctkEventConstants::EVENT_FILTER.
     * The value of this property must be a string containing a filter specification.
     * Any of the event's properties can be used in the filter expression.
     * Each slot is notified for any event which belongs to the topics the
     * slot has expressed an interest in. If the handler has defined a
     * EVENT_FILTER property then the event properties must also match the filter
     * expression. If the filter is an error, then the Event Admin service
     * should log a warning and further ignore the registered slot.
     *
     * @param pSubscriber The owner of the slot.
     * @param psMember The slot in normalized form.
     * @param properties A map containing topics and a filter expression.
     * @param eType One of Qt::AutoConnection, Qt::DirectConnection, Qt::QueuedConnection, or
     *        Qt::BlockingQueuedConnection. Only a direct or blocking queued connection
     *        ensures that calls to <code>sendEvent()</code> will block until all event
     *        handlers completed their tasks.
     * @return Returns an id which can be used to update the properties.
     *
     * @throws ctkInvalidArgumentException If <code>subscriber</code> or <code>member</code> is 0
     *         or <code>type</code> is invalid.
     *
     * @see unsubscribeSlot(qlonglong)
     */
    virtual qlonglong subscribeSlot(const QObject *pSubscriber, const char *psMember,
                                    const QTKDictionary &properties,
                                    Qt::ConnectionType eType = Qt::AutoConnection) = 0;

    /**
     * @brief unsubscribeSlot
     * Unsubscribe a previously subscribed slot. Use this method to allow the EventAdmin
     * implementation to clean up resources.
     *
     * @param llSubscriptionId The id obtained from a previous call to subscribeSlot()
     *
     * @see subscribeSlot()
     */
    virtual void unsubscribeSlot(qlonglong llSubscriptionId) = 0;

    /**
     * @brief updateProperties
     * Updates the properties of a previously registered slot. This can be used
     * to change the topics the slot is interested in or to change the filter expression.
     * A previously registered property can be removed by providing an invalid QVariant.
     *
     * @param llSubscriptionId The slot id obtained by a call to subscribeSlot().
     * @param properties The properties which should be updated.
     * @return <code>true</code> if a slot was registered under this subscriptionId and its
     *         properties where changed, <code>false</code> otherwise.
     */
    virtual bool updateProperties(qlonglong llSubscriptionId, const QTKDictionary &properties) = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin,
                    "org.qtk.service.event.EventAdmin")

#endif // QTKEVENTADMIN_H
