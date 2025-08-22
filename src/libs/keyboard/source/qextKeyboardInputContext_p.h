#ifndef _QEXTKEYBOARDINPUTCONTEXT_P_H
#define _QEXTKEYBOARDINPUTCONTEXT_P_H

#include <qextKeyboardPanel.h>
#include <qextKeyboardLayout.h>
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
    QSize m_inputPanelSize;
    QPoint m_inputPanelFollowPos;
    QExtKeyboardLayout m_mainLayout;
    QExtKeyboardLayout m_symbolLayout;
    QStringList m_editablePropertyNames;
    QStringList m_readonlyPropertyNames;
    QStringList m_editableWidgetClassNames;
    QStringList m_readonlyWidgetClassNames;
    QExtAbstractInputMethod *m_inputMethod;
    Qt::InputMethodHints m_inputMethodHints;
    QPointer<QExtKeyboardPanel> m_inputPanel;
    QExtKeyboardInputContext::PopupModeEnum m_inputPanelPopupMode;

private:
    QEXT_DECLARE_PUBLIC(QExtKeyboardInputContext)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtKeyboardInputContextPrivate)
};

#endif // _QEXTKEYBOARDINPUTCONTEXT_P_H
