#include "qextmvvmmodel.h"
#include "qextmvvmmodelmapper.h"

QEXT_USE_NAMESPACE

QEXTMvvmModel::QEXTMvvmModel(const QString &modelType)
    : m_model_type(modelType),
      m_mapper(new QEXTMvvmModelMapper(this))
{

}

QEXTMvvmModel::~QEXTMvvmModel()
{
    m_mapper->callOnModelDestroyed();
}

QEXTMvvmModelMapper *QEXTMvvmModel::mapper() const
{
    return m_mapper.data();
}
