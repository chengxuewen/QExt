#ifndef QTKEALOGEVENTADAPTER_P_H
#define QTKEALOGEVENTADAPTER_P_H

#include "qtkeaabstractadapter_p.h"

#include <QTKPluginFramework/QTKServiceRegistration>
#include <QTKPluginFramework/Service/Log/QTKLogListener>

#include <QObject>
#include <QMutex>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEALogEventAdapter;

/**
 * @brief The QTKLogListenerImpl class
 */
class QTKLogListenerImpl : public QObject, public QTKLogListener
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogListener)

public:
    QTKLogListenerImpl(QTKEALogEventAdapter *pAdapter);

    void logged(QTKLogEntryPtr entry);

private:
    QTKEALogEventAdapter* const m_pAdapter;
};

/**
 * @brief The QTKEALogEventAdapter class
 */
class QTKEALogEventAdapter : public QObject, public QTKEAAbstractAdapter
{
    Q_OBJECT

public:
    QTKEALogEventAdapter(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext* pContext, QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin* pAdmin);

    ~QTKEALogEventAdapter();

    void destroy(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext* m_pContext);

private:
    friend class QTKLogListenerImpl;

    QMutex m_mutex;
    QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *m_pContext;
    QTKLogListenerImpl *m_pLogListener;
    QTKServiceRegistration m_serviceReg;
};

#endif // QTKEALOGEVENTADAPTER_P_H
