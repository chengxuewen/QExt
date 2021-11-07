#ifndef _QEXTMVVMUNDOSTACK_P_H
#define _QEXTMVVMUNDOSTACK_P_H

#include <qextMvvmGlobal.h>

#include <QUndoStack>
#include <QScopedPointer>

class QEXTMvvmUndoStack;
class QEXT_MVVM_API QEXTMvvmUndoStackPrivate
{
public:
    explicit QEXTMvvmUndoStackPrivate(QEXTMvvmUndoStack *q);
    virtual ~QEXTMvvmUndoStackPrivate();

    QEXTMvvmUndoStack * const q_ptr;

    QScopedPointer<QUndoStack> m_undoStack;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmUndoStackPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmUndoStack)
};

#endif // _QEXTMVVMUNDOSTACK_P_H
