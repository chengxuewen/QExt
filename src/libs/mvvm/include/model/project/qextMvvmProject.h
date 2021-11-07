#ifndef _QEXTMVVMPROJECT_H
#define _QEXTMVVMPROJECT_H

#include <qextMvvmProjectInterface.h>

#include <QScopedPointer>

struct QEXTMvvmProjectContext;

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.
class QEXTMvvmProjectPrivate;
class QEXT_MVVM_API QEXTMvvmProject : public QEXTMvvmProjectInterface
{
public:
    QEXTMvvmProject(const QEXTMvvmProjectContext &context);
    ~QEXTMvvmProject();

    QString projectDir() const QEXT_DECL_OVERRIDE;

    bool save(const QString &dirName) QEXT_DECL_OVERRIDE;

    bool load(const QString &dirName) QEXT_DECL_OVERRIDE;

    bool isModified() const QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QEXTMvvmProjectPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmProject)
    QEXT_DECL_PRIVATE(QEXTMvvmProject)
};


#endif // _QEXTMVVMPROJECT_H
