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

    bool mVisible;
    bool mNeedHiden;
    QString mPreeditText;
    QEvent *mFilterEvent;
    QObject *mFocusObject;
    QSize mInputPanelSize;
    QPoint mInputPanelFollowPos;
    QExtKeyboardLayout mMainLayout;
    QExtKeyboardLayout mSymbolLayout;
    QStringList mEditablePropertyNames;
    QStringList mReadonlyPropertyNames;
    QStringList mEditableWidgetClassNames;
    QStringList mReadonlyWidgetClassNames;
    QExtAbstractInputMethod *mInputMethod;
    Qt::InputMethodHints mInputMethodHints;
    QPointer<QExtKeyboardPanel> mInputPanel;
    QExtKeyboardInputContext::PopupModeEnum mInputPanelPopupMode;

private:
    QEXT_DECLARE_PUBLIC(QExtKeyboardInputContext)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtKeyboardInputContextPrivate)
};

#endif // _QEXTKEYBOARDINPUTCONTEXT_P_H
