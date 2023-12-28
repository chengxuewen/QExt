#ifndef _QEXTKEYBOARD_P_H
#define _QEXTKEYBOARD_P_H

#include <qextKeyboard.h>

class QExtKeyboardPrivate
{
public:
    explicit QExtKeyboardPrivate(QExtKeyboard *q);
    virtual ~QExtKeyboardPrivate();

    QExtKeyboard * const q_ptr;

private:
    QEXT_DECL_PUBLIC(QExtKeyboard)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardPrivate)
};

#endif // _QEXTKEYBOARD_P_H
