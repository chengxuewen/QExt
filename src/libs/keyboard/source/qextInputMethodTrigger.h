#ifndef _QEXTINPUTMETHODTRAGGER_H
#define _QEXTINPUTMETHODTRAGGER_H

#include <qextKeyboardGlobal.h>

#include <QObject>

class QExtInputMethodTriggerPrivate;
class QEXT_KEYBOARD_API QExtInputMethodTrigger : public QObject
{
    Q_OBJECT
public:
    static QExtInputMethodTrigger *instance();
    ~QExtInputMethodTrigger() QEXT_OVERRIDE;

    bool isAutoTriggerInputMethodEnabled() const;
    void setAutoTriggerInputMethodEnable(bool enable);

Q_SIGNALS:
    void autoTriggerInputMethodEnableChanged(bool enable);

public Q_SLOTS:
    void showKeyboard();
    void hideKeyboard();

protected Q_SLOTS:
    void onShowKeyboardTimerTimeout();

protected:
    QExtInputMethodTrigger(QObject *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtInputMethodTriggerPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtInputMethodTrigger)
    QEXT_DISABLE_COPY_MOVE(QExtInputMethodTrigger)
};

#endif // _QEXTINPUTMETHODTRAGGER_H
