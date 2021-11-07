#include "applicationmodels.h"
#include "materialmodel.h"
#include "materialpropertycontroller.h"
#include "samplemodel.h"
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmModelDocumentInterface.h>
#include <qextMvvmItem.h>
#include <qextMvvmFactory.h>



struct ApplicationModels::ApplicationModelsImpl {
    QScopedPointer<MaterialModel> m_material_model;
    QScopedPointer<SampleModel> m_sample_model;
    QScopedPointer<MaterialPropertyController> m_property_controller;
    QScopedPointer<QEXTMvvmModelDocumentInterface> m_document;

    ApplicationModelsImpl()
    {
        m_material_model.reset(new MaterialModel);
        m_sample_model.reset(new SampleModel);
        m_property_controller.reset(new MaterialPropertyController(m_material_model.get(), m_sample_model.get()));
        m_document.reset(QEXTMvvmFactory::createModelDocument({m_material_model.get(), m_sample_model.get()}));
    }
};

ApplicationModels::ApplicationModels() : p_impl(new ApplicationModelsImpl) {}

ApplicationModels::~ApplicationModels() = default;

MaterialModel* ApplicationModels::materialModel()
{
    return p_impl->m_material_model.get();
}

SampleModel* ApplicationModels::sampleModel()
{
    return p_impl->m_sample_model.get();
}

void ApplicationModels::readFromFile(const QString& name)
{
    p_impl->m_document->load(name);
}

void ApplicationModels::writeToFile(const QString& name)
{
    p_impl->m_document->save(name);
}
