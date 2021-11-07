#include <qextMvvmApplicationModelsInterface.h>
#include <qextMvvmModel.h>
#include <qextMvvmProject.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmProjectUtils.h>
#include <qextMvvmUtils.h>

#include <cctype>

namespace
{
    const QString json_extention = ".json";
    const QString untitled_name = "Untitled";
} // namespace



//! Suggests file name which can be used to store json content of given model.
//! Uses the model type to construct a filename: MaterialModel -> materialmodel.json

QString ProjectUtils::SuggestFileName(const QEXTMvvmModel &model)
{
    QString result = model.modelType();
    return result.toLower() + json_extention;
}

//! Returns 'true' if given directory might be a project directory.
//! This simplified check counts number of files with json extention.

bool ProjectUtils::IsPossibleProjectDir(const QString &project_dir)
{
    return !QEXTMvvmUtils::FindFiles(project_dir, json_extention).empty();
}

//! Creates new untitled project.

QEXTMvvmProjectInterface *ProjectUtils::CreateUntitledProject(const QEXTMvvmProjectContext &context)
{
    return new QEXTMvvmProject(context);
}

//! Returns a MainWindow title for given project.

QString ProjectUtils::ProjectWindowTitle(const QEXTMvvmProjectInterface &project)
{
    return ProjectWindowTitle(project.projectDir(), project.isModified());
}

//! Returns a title composed from last part of project path, and `is_modified` flag.
//! QEXTMvvmProject without projectDir will be "Untitled", modified project will be "*Untitled".
//! QEXTMvvmProject with projectDir in "/home/user/project1" will get title "project1".

QString ProjectUtils::ProjectWindowTitle(const QString &project_dir, bool is_modified)
{
    int pos = project_dir.lastIndexOf('/');
    QString project_name = (pos == -1 ? untitled_name : project_dir.mid(pos));
    QString unsaved_status = is_modified ? "*" : "";
    return unsaved_status + project_name;
}

