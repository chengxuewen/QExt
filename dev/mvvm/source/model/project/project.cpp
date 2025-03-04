// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/project/project.h"
#include "model/factories/modeldocumentfactory.h"
#include "model/project/project_types.h"
#include "model/project/projectchangecontroller.h"
#include "model/project/projectutils.h"
#include "model/utils/fileutils.h"
#include <functional>

#include <qextInvoke.h>

#include <QDebug>

using namespace ModelView;

struct QExtMvvmProject::ProjectImpl {
    std::string m_project_dir;
    QExtMvvmProjectContext m_context;
    QExtMvvmProjectChangedController m_change_controller;

    ProjectImpl(const QExtMvvmProjectContext& context)
        : m_context(context)
        , m_change_controller(context.m_models_callback(), context.m_modified_callback)
    {
    }

    //! Returns list of models which are subject to save/load.
    std::vector<QExtMvvmSessionModel*> models() const { return m_context.m_models_callback(); }

    //! Processes all models one by one and either save or load them to/from given directory.
    //! Template parameter `method` specifies QExtMvvmModelDocumentInterface's method to use.
    template <typename T>
    bool process(const std::string& dirname, T method)
    {
        if (!Utils::exists(dirname))
            return false;

        for (auto model : models()) {
            auto document = qextMvvmCreateJsonDocument({model});
            auto filename = Utils::join(dirname, ProjectUtils::SuggestFileName(*model));
            // qextInvoke(method, document, filename);
            ((*document.get()).*method)(dirname);
            qDebug() << "filename:" << filename.data();
        }
        m_project_dir = dirname;
        m_change_controller.resetChanged();
        return true;
    }
};

QExtMvvmProject::QExtMvvmProject(const QExtMvvmProjectContext& context) : p_impl(qextMakeUnique<ProjectImpl>(context)) {}

QExtMvvmProject::~QExtMvvmProject() = default;

//! Returns the full path to a project directory. It is a name where the project has been last time
//! saved, or loaded from.

std::string QExtMvvmProject::projectDir() const
{
    return p_impl->m_project_dir;
}

//! Saves all models to a given directory. Directory should exist.
//! Provided name will become 'projectDir'.

bool QExtMvvmProject::save(const std::string& dirname) const
{
    return p_impl->process(dirname, &QExtMvvmModelDocumentInterface::save);
}

//! Loads all models from the given directory.
bool QExtMvvmProject::load(const std::string& dirname)
{
    return p_impl->process(dirname, &QExtMvvmModelDocumentInterface::load);
}

bool QExtMvvmProject::isModified() const
{
    return p_impl->m_change_controller.hasChanged();
}
