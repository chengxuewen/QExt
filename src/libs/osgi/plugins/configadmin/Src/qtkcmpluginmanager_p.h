#ifndef QTKCMPLUGINMANAGER_P_H
#define QTKCMPLUGINMANAGER_P_H

#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/QTKDictionary>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginTracker;

/**
 * PluginManager tracks and allows customization via ConfigurationPlugin
 */
class QTKCMPluginManager
{
public:
    QTKCMPluginManager(QTKPluginContext* context);
    ~QTKCMPluginManager();

    void start();
    void stop();

    void modifyConfiguration(const QTKServiceReference& managedReference, QTKDictionary& properties);

private:
    QScopedPointer<QTKPluginTracker> pluginTracker;
};

#endif // QTKCMPLUGINMANAGER_P_H
