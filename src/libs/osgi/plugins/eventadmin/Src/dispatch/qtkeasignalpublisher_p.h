#ifndef QTKEASIGNALPUBLISHER_P_H
#define QTKEASIGNALPUBLISHER_P_H

#include <QTKPluginFramework/Service/Event/QTKEvent>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventAdminService;

class QTKEASignalPublisher : public QObject
{
    Q_OBJECT

public:
    QTKEASignalPublisher(QTKEventAdminService *pEventAdmin, const QString &strSignal, const QString &strTopic);

    QString getSignalName() const;
    QString getTopicName() const;

public slots:
    void publishSyncSignal(const QTKDictionary &eventProps);
    void publishAsyncSignal(const QTKDictionary &eventProps);

private:
    QTKEventAdminService *m_pEventAdmin;
    const QString m_strSignal;
    const QString m_strTopic;
};

#endif // QTKEASIGNALPUBLISHER_P_H
