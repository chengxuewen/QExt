#include <qextBPNodeDelegateModelRegistry.h>

#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>

QExtBPNodeDelegateModel *QExtBPNodeDelegateModelRegistry::create(const QString &modelName)
{
    auto it = _registeredItemCreators.find(modelName);

    if (it != _registeredItemCreators.end())
    {
        return it->second();
    }

    return QEXT_NULLPTR;
}

const QExtBPNodeDelegateModelRegistry::RegisteredModelCreatorsMap &
QExtBPNodeDelegateModelRegistry::registeredModelCreators() const
{
    return _registeredItemCreators;
}

const QExtBPNodeDelegateModelRegistry::RegisteredModelsCategoryMap &
QExtBPNodeDelegateModelRegistry::registeredModelsCategoryAssociation() const
{
    return _registeredModelsCategory;
}

const QExtBPNodeDelegateModelRegistry::CategoriesSet &QExtBPNodeDelegateModelRegistry::categories() const
{
    return _categories;
}
