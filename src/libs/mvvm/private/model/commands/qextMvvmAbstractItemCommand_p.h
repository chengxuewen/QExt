#ifndef _QEXTMVVMABSTRACTITEMCOMMAND_P_H
#define _QEXTMVVMABSTRACTITEMCOMMAND_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCommandResult.h>

#include <QString>

class QEXTMvvmModel;
class QEXTMvvmAbstractItemCommand;
class QEXT_MVVM_API QEXTMvvmAbstractItemCommandPrivate
{
public:
    enum StatusType
    {
        Status_Initial,
        Status_AfterExecute,
        Status_AfterUndo
    };

    explicit QEXTMvvmAbstractItemCommandPrivate(QEXTMvvmAbstractItemCommand *q);
    virtual ~QEXTMvvmAbstractItemCommandPrivate();

    void setAfterExecute();
    void setAfterUndo();
    bool canExecute() const;
    bool canUndo() const;

    QEXTMvvmAbstractItemCommand * const q_ptr;

    bool m_isObsolete;
    QString m_text;
    StatusType m_status;
    QEXTMvvmModel *m_model;
    QEXTMvvmCommandResult m_result;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmAbstractItemCommandPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmAbstractItemCommand)
};

#endif // _QEXTMVVMABSTRACTITEMCOMMAND_P_H
