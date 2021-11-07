#include <qextMvvmProject.h>
#include <qextMvvmProject_p.h>
#include <qextMvvmFactory.h>
#include <qextMvvmProjectUtils.h>
#include <qextMvvmUtils.h>

#include <QFile>

QEXTMvvmProjectPrivate::QEXTMvvmProjectPrivate(QEXTMvvmProject *q)
    : q_ptr(q)
    , m_changeController(m_context.m_models_callback(), m_context.m_modified_callback)
{

}

QEXTMvvmProjectPrivate::~QEXTMvvmProjectPrivate()
{

}

QVector<QEXTMvvmModel *> QEXTMvvmProjectPrivate::models() const
{
    return m_context.m_models_callback();
}



QEXTMvvmProject::QEXTMvvmProject(const QEXTMvvmProjectContext &context)
    : d_ptr(new QEXTMvvmProjectPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmProject);
    d->m_context = context;
//    d->m_changeController = QEXTMvvmProjectChangedController(context.m_models_callback(), context.m_modified_callback);
}

QEXTMvvmProject::~QEXTMvvmProject()
{

}

//! Returns the full path to a project directory. It is a name where the project has been last time
//! saved, or loaded from.

QString QEXTMvvmProject::projectDir() const
{
    QEXT_DECL_DC(QEXTMvvmProject);
    return d->m_projectDir;
}

//! Saves all models to a given directory. Directory should exist.
//! Provided name will become 'projectDir'.

bool QEXTMvvmProject::save(const QString &dirname)
{
    QEXT_DECL_D(QEXTMvvmProject);
    return d->process(dirname, &QEXTMvvmModelDocumentInterface::save);
}

//! Loads all models from the given directory.
bool QEXTMvvmProject::load(const QString &dirname)
{
    QEXT_DECL_D(QEXTMvvmProject);
    return d->process(dirname, &QEXTMvvmModelDocumentInterface::load);
}

bool QEXTMvvmProject::isModified() const
{
    QEXT_DECL_DC(QEXTMvvmProject);
    return d->m_changeController.hasChanged();
}
