#ifndef _QEXTKEYBOARDINPUTCONTEXT_P_H
#define _QEXTKEYBOARDINPUTCONTEXT_P_H

#include <qextKeyboardLayout.h>
#include <qextKeyboardContainer.h>
#include <qextKeyboardInputContext.h>

#include <QPointer>

class QExtKeyboardInputContextPrivate
{
public:
    explicit QExtKeyboardInputContextPrivate(QExtKeyboardInputContext *q);
    virtual ~QExtKeyboardInputContextPrivate();

    QExtKeyboardInputContext * const q_ptr;

    bool m_visible;
    bool m_needHiden;
    QString m_preeditText;
    QEvent *m_filterEvent;
    QObject *m_focusObject;
    QExtKeyboardLayout m_mainLayout;
    QExtKeyboardLayout m_symbolLayout;
    QExtAbstractInputMethod *m_inputMethod;
    Qt::InputMethodHints m_inputMethodHints;
    QPointer<QExtKeyboardContainer> m_inputPanel;

private:
    QEXT_DECL_PUBLIC(QExtKeyboardInputContext)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardInputContextPrivate)
};

#endif // _QEXTKEYBOARDINPUTCONTEXT_P_H
