#ifndef _QEXTMVVMCOMMANDSERVICE_P_H
#define _QEXTMVVMCOMMANDSERVICE_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmUndoStackInterface.h>

#include <QScopedPointer>

class QEXTMvvmModel;
class QEXTMvvmCommandService;
class QEXT_MVVM_API QEXTMvvmCommandServicePrivate
{
public:
    explicit QEXTMvvmCommandServicePrivate(QEXTMvvmCommandService *q);
    virtual ~QEXTMvvmCommandServicePrivate();

    QEXTMvvmCommandService * const q_ptr;

    bool m_pauseRecord;
    QEXTMvvmModel *m_model;
    QScopedPointer<QEXTMvvmUndoStackInterface> m_commands;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmCommandServicePrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmCommandService)
};

#endif // _QEXTMVVMCOMMANDSERVICE_P_H
