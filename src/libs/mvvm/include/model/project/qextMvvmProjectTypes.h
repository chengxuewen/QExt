#ifndef _QEXTMVVMPROJECTTYPES_H
#define _QEXTMVVMPROJECTTYPES_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QString>
#include <QVector>



class QEXTMvvmModel;

//! Possible user answers on question "Project was modified".
enum class SaveChangesAnswer { SAVE = 0, DISCARD = 1, CANCEL = 2 };

//! Provides necessary information for Project construction.

struct QEXT_MVVM_API QEXTMvvmProjectContext
{

    //!< To notify about the change of the project with respect to what was written on disk.
    typedef QEXTFunction<void> modified_callback_t;

    //! To ask for a vector of models to save/load to/from disk.
    //! This is intentionally obtained via callback since save request might come after
    //! the Project construction.
    typedef QEXTFunction<QVector<QEXTMvvmModel *> > models_callback_t;

    modified_callback_t m_modified_callback;
    models_callback_t m_models_callback;
};

//! Defines the context to interact with the user regarding save/save-as/create-new project
//! scenarious.

struct QEXT_MVVM_API QEXTMvvmUserInteractionContext
{
    //!< To ask the user to select existing directory, returns full path to the directory.
    typedef QEXTFunction<QString> select_dir_callback_t;

    //!< To ask the user to create a new directory, returns full path to the directory.
    typedef QEXTFunction<QString> create_dir_callback_t;

    //!< To ask the user what to do with modified project.
    typedef QEXTFunction<SaveChangesAnswer> answer_callback_t;

    select_dir_callback_t m_select_dir_callback;
    create_dir_callback_t m_create_dir_callback;
    answer_callback_t m_answer_callback;
};


#endif // _QEXTMVVMPROJECTTYPES_H
