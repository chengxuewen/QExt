#ifndef _QEXTMVVMFACTORY_H
#define _QEXTMVVMFACTORY_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmModelDocumentInterface.h>
#include <qextMvvmProjectManagerInterface.h>

//#include <qextMvvmJsonItemConverterInterface.h>
//#include <qextMvvmJsonModelConverterInterface.h>

#include <QVector>

struct QEXTMvvmProjectContext;
struct QEXTMvvmUserInteractionContext;

class QEXTMvvmItemFactoryInterface;
class QEXTMvvmModel;

struct QEXT_MVVM_API QEXTMvvmFactory
{
    static QEXTMvvmItemCatalogue *createStandardItemCatalogue();

    //! Creates QEXTMvvmJsonDocument to save and load models.
    static QEXTMvvmModelDocumentInterface *createJsonDocument(const QVector<QEXTMvvmModel *> &models);

    //! Creates default QEXTMvvmProjectManager to save and load models.
    static QEXTMvvmProjectManagerInterface *createProjectManager(const QEXTMvvmProjectContext &project_context,
                                                          const QEXTMvvmUserInteractionContext& user_context);

    //! Creates JSON item converter intended for item cloning.
    static QEXTMvvmJsonItemConverterInterface *createItemCloneConverter(const QEXTMvvmItemFactoryInterface *item_factory);

    //! Creates JSON item converter intended for item copying.
    static QEXTMvvmJsonItemConverterInterface *createItemCopyConverter(const QEXTMvvmItemFactoryInterface *item_factory);

    //! Creates JSON item converter intended for saving on disk.
    static QEXTMvvmJsonItemConverterInterface *createItemProjectConverter(const QEXTMvvmItemFactoryInterface *item_factory);

    //! Creates a JSON model converter intended for model cloning.
    static QEXTMvvmJsonModelConverterInterface *createModelCloneConverter();

    //! Creates a JSON model converter intended for model copying.
    static QEXTMvvmJsonModelConverterInterface *createModelCopyConverter();

    //! Creates a JSON model converter intended for save/load of the project on disk.
    static QEXTMvvmJsonModelConverterInterface *createModelProjectConverter();

};

#endif // _QEXTMVVMFACTORY_H
