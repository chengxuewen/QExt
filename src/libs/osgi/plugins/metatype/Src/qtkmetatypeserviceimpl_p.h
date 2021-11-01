#ifndef QTKMETATYPESERVICEIMPL_P_H
#define QTKMETATYPESERVICEIMPL_P_H

#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeService>
#include <QTKPluginFramework/QTKServiceTracker>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * Implementation of QTKMetaTypeService
 */
class QTKMetaTypeServiceImpl : public QObject, public QTKMetaTypeService
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKMetaTypeService)

private:

    QMutex _mtpsMutex;
    QHash<long, QTKMetaTypeInformationPtr> _mtps;

    QTKLogService* const logger;
    QTKServiceTracker<>* metaTypeProviderTracker;

public:

    /**
   * Constructor of class QTKMetaTypeServiceImpl.
   */
    QTKMetaTypeServiceImpl(QTKLogService* logger, QTKServiceTracker<>* metaTypeProviderTracker);

    /*
   * @see QTKMetaTypeService#getMetaTypeInformation()
   */
    QTKMetaTypeInformationPtr getMetaTypeInformation(const QSharedPointer<QTKPlugin>& plugin);

public Q_SLOTS:

    void pluginChanged(const QTKPluginEvent& event);

private:

    /**
   * Internal Method - to get QTKMetaTypeProvider object.
   */
    QTKMetaTypeInformationPtr getMetaTypeProvider(const QSharedPointer<QTKPlugin>& p);

};

#endif // QTKMETATYPESERVICEIMPL_P_H
