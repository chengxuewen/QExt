#include <qextMvvmFactory.h>
#include <qextMvvmCompoundItem.h>
#include <qextMvvmPropertyItem.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmData1dItem.h>
#include <qextMvvmData2dItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmGraphViewPortItem.h>
#include <qextMvvmLinkedItem.h>
#include <qextMvvmPlotTableItems.h>
#include <qextMvvmVectorItem.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmProjectManagerDecorator.h>

QEXTMvvmItemCatalogue *QEXTMvvmFactory::createStandardItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<QEXTMvvmColorMapItem>();
    result->registerItem<QEXTMvvmColorMapViewportItem>();
    result->registerItem<QEXTMvvmCompoundItem>();
    result->registerItem<QEXTMvvmContainerItem>();
    result->registerItem<QEXTMvvmData1DItem>();
    result->registerItem<QEXTMvvmData2DItem>();
    result->registerItem<QEXTMvvmFixedBinAxisItem>();
    result->registerItem<QEXTMvvmGraphItem>();
    result->registerItem<QEXTMvvmGraphViewportItem>();
    result->registerItem<QEXTMvvmLinkedItem>();
    result->registerItem<QEXTMvvmPenItem>();
    result->registerItem<QEXTMvvmPointwiseAxisItem>();
    result->registerItem<QEXTMvvmPropertyItem>();
    result->registerItem<QEXTMvvmItem>();
    result->registerItem<QEXTMvvmTextItem>();
    result->registerItem<QEXTMvvmVectorItem>();
    result->registerItem<QEXTMvvmViewportAxisItem>();
    return result;
}

QEXTMvvmModelDocumentInterface *QEXTMvvmFactory::createModelDocument(const QVector<QEXTMvvmModel *> &models)
{
//    return new QEXTMvvmJsonDocument(models);
}

QEXTMvvmProjectManagerInterface *QEXTMvvmFactory::createProjectManager(const QEXTMvvmProjectContext &project_context, const QEXTMvvmUserInteractionContext &user_context)
{
    return new QEXTMvvmProjectManagerDecorator(project_context, user_context);
}


//QEXTMvvmJsonItemConverterInterface *QEXTMvvmFactory::createItemCloneConverter(const QEXTMvvmItemFactoryInterface *item_factory)
//{
//    QEXTMvvmConverterContext context;
//    context.m_factory = item_factory;
//    context.m_mode = ConverterMode::clone;
//    return new QEXTMvvmJsonItemConverter(context);
//}

//QEXTMvvmJsonItemConverterInterface *QEXTMvvmFactory::createItemCopyConverter(const QEXTMvvmItemFactoryInterface *item_factory)
//{
//    QEXTMvvmConverterContext context;
//    context.m_factory = item_factory;
//    context.m_mode = ConverterMode::copy;
//    return new QEXTMvvmJsonItemConverter(context);
//}

//QEXTMvvmJsonItemConverterInterface *QEXTMvvmFactory::createItemProjectConverter(const QEXTMvvmItemFactoryInterface *item_factory)
//{
//    QEXTMvvmConverterContext context;
//    context.m_factory = item_factory;
//    context.m_mode = ConverterMode::project;
//    return new QEXTMvvmJsonItemConverter(context);
//}


//QEXTMvvmJsonModelConverterInterface *QEXTMvvmFactory::createModelCloneConverter()
//{
//    return new QEXTMvvmJsonModelConverter(ConverterMode::clone);
//}

//QEXTMvvmJsonModelConverterInterface *QEXTMvvmFactory::createModelCopyConverter()
//{
//    return new QEXTMvvmJsonModelConverter(ConverterMode::copy);
//}

//QEXTMvvmJsonModelConverterInterface *QEXTMvvmFactory::createModelProjectConverter()
//{
//    return new QEXTMvvmJsonModelConverter(ConverterMode::project);
//}
