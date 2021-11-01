#ifndef QTKCONFIGURATIONADMINIMPL_P_H
#define QTKCONFIGURATIONADMINIMPL_P_H

#include <QTKPluginFramework/Service/Config/QTKConfigurationAdmin>
#include <QTKPluginFramework/QTKPlugin>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationAdminFactory;
class QTKConfigurationStore;

class QTKConfigurationAdminImpl : public QObject, public QTKConfigurationAdmin
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKConfigurationAdmin)

public:
    QTKConfigurationAdminImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                              QTKConfigurationStore* configurationStore,
                              QSharedPointer<QTKPlugin> plugin);

    QTKConfigurationPtr createFactoryConfiguration(const QString& factoryPid);

    QTKConfigurationPtr createFactoryConfiguration(const QString& factoryPid,
                                                   const QString& location);

    QTKConfigurationPtr getConfiguration(const QString& pid);

    QTKConfigurationPtr getConfiguration(const QString& pid, const QString& location);

    QList<QTKConfigurationPtr> listConfigurations(const QString& filterString = QString());

private:

    QTKConfigurationAdminFactory* const configurationAdminFactory;
    const QSharedPointer<QTKPlugin> plugin;
    QTKConfigurationStore* const configurationStore;

    void checkPID(const QString& pid);
};

#endif // QTKCONFIGURATIONADMINIMPL_P_H
