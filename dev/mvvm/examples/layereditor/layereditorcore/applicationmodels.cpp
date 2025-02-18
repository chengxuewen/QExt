// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "applicationmodels.h"
#include "materialmodel.h"
#include "materialpropertycontroller.h"
#include "samplemodel.h"
#include "model/factories/modeldocumentfactory.h"

using namespace ModelView;

struct ApplicationModels::ApplicationModelsImpl {
    QExtUniquePointer<MaterialModel> m_material_model;
    QExtUniquePointer<SampleModel> m_sample_model;
    QExtUniquePointer<MaterialPropertyController> m_property_controller;
    QExtUniquePointer<ModelDocumentInterface> m_document;

    ApplicationModelsImpl()
    {
        m_material_model = qextMakeUnique<MaterialModel>();
        m_sample_model = qextMakeUnique<SampleModel>();
        m_property_controller = qextMakeUnique<MaterialPropertyController>(m_material_model.get(),
                                                                             m_sample_model.get());
        m_document = CreateJsonDocument({m_material_model.get(), m_sample_model.get()});
    }
};

ApplicationModels::ApplicationModels() : p_impl(qextMakeUnique<ApplicationModelsImpl>()) {}

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
    p_impl->m_document->load(name.toStdString());
}

void ApplicationModels::writeToFile(const QString& name)
{
    p_impl->m_document->save(name.toStdString());
}
