#ifndef QTKEVENTHANDLERWRAPPER_P_H
#define QTKEVENTHANDLERWRAPPER_P_H

#include <QTKPluginFramework/Service/Event/QTKEventAdmin>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>
#include <QTKPluginFramework/QTKLDAPSearchFilter>

#include <QStringList>

#include <iostream>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventHandlerWrapper : public QObject
{
    Q_OBJECT

public:
    QTKEventHandlerWrapper(const QObject *pSubscriber, const char *pHandler, const QTKProperties &properties)
        : m_properties(properties)
    {
        connect(this, SIGNAL(notifySubscriber(QTKEvent)), pSubscriber, pHandler);
    }

    QStringList topics() const {
        return m_listTopic;
    }

    bool init() {
        m_listTopic.clear();

        // Get topic names
        QVariant value = m_properties[QTKEventConstants::EVENT_TOPICS];
        m_listTopic = value.toStringList();

        if (m_listTopic.empty()) {
            return false;
        }

        value = m_properties[QTKEventConstants::EVENT_FILTER];
        m_filter = QTKLDAPSearchFilter(value.toString());
        return true;
    }

    void handleEvent(const QTKEvent &event) {
        if (!event.matches(m_filter)) {
            return;
        }
        // should do permissions checks now somehow
        // ...

        try {
            emit this->notifySubscriber(event);
        } catch (const std::exception &e) {
            // TODO logging
            std::cerr << "Exception occured during publishing " << qPrintable(event.getTopic()) << ": " << e.what() << std::endl;
        }
    }

Q_SIGNALS:
    void notifySubscriber(const QTKEvent &);

private:
    QTKProperties m_properties;
    QStringList m_listTopic;
    QTKLDAPSearchFilter m_filter;
};

#endif // QTKEVENTHANDLERWRAPPER_P_H
