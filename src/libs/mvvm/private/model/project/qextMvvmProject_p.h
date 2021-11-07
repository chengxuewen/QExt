#ifndef QEXTMVVMPROJECT_P_H
#define QEXTMVVMPROJECT_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmUtils.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmProjectChangeController.h>

#include <QFile>

class QEXTMvvmProject;
class QEXT_MVVM_API QEXTMvvmProjectPrivate
{
public:
    explicit QEXTMvvmProjectPrivate(QEXTMvvmProject *q);
    virtual ~QEXTMvvmProjectPrivate();

    //! Returns list of models which are subject to save/load.
    QVector<QEXTMvvmModel *> models() const;

    //! Processes all models one by one and either save or load them to/from given directory.
    //! Template parameter `method` specifies QEXTMvvmModelDocumentInterface's method to use.
    template <typename T> bool process(const QString &dirname, T method)
    {
//        if (!QFile::exists(dirname))
//            return false;

//        for (auto model : models()) {
//            QEXTMvvmModelDocumentInterface *document = QEXTMvvmFactory::createModelDocument(QVector<QEXTMvvmModel *>(1, model));
//            QString filename = QEXTMvvmUtils::join(dirname, ProjectUtils::SuggestFileName(*model));
//            std::invoke(method, document, filename);
//        }
//        m_projectDir = dirname;
//        m_changeController.resetChanged();
        return true;
    }

    QEXTMvvmProject * const q_ptr;

    QString m_projectDir;
    QEXTMvvmProjectContext m_context;
    QEXTMvvmProjectChangedController m_changeController;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmProjectPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmProject)
};

#endif // QEXTMVVMPROJECT_P_H
