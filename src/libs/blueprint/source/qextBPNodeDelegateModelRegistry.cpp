#include <qextBPNodeDelegateModelRegistry.h>

#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>

QExtBPNodeDelegateModel *QExtBPNodeDelegateModelRegistry::create(QString const &modelName)
{
    auto it = _registeredItemCreators.find(modelName);

    if (it != _registeredItemCreators.end()) {
        return it->second();
    }

    return QEXT_NULLPTR;
}

QExtBPNodeDelegateModelRegistry::RegisteredModelCreatorsMap const &
QExtBPNodeDelegateModelRegistry::registeredModelCreators() const
{
    return _registeredItemCreators;
}

QExtBPNodeDelegateModelRegistry::RegisteredModelsCategoryMap const &
QExtBPNodeDelegateModelRegistry::registeredModelsCategoryAssociation() const
{
    return _registeredModelsCategory;
}

QExtBPNodeDelegateModelRegistry::CategoriesSet const &QExtBPNodeDelegateModelRegistry::categories() const
{
    return _categories;
}
