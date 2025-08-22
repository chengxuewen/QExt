#ifndef _QEXTKEYBOARDINPUTCONTEXT_H
#define _QEXTKEYBOARDINPUTCONTEXT_H

#include <qextKeyboardGlobal.h>

#include <QScopedPointer>
#include <QInputMethodEvent>
#include <qpa/qplatforminputcontext.h>

class QExtAbstractInputMethod;
class QExtKeyboardInputContextPrivate;
class QEXT_KEYBOARD_API QExtKeyboardInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    enum PopupModeEnum
    {
        PopupMode_AutoFollow = 0,
        PopupMode_BottomCenter,
    };
    Q_ENUM(PopupModeEnum)

    typedef QList<QInputMethodEvent::Attribute> AttributesList;

    static QExtKeyboardInputContext *instance();
    ~QExtKeyboardInputContext() QEXT_OVERRIDE;

    QObject *focusObject();

    bool isValid() const QEXT_OVERRIDE;

    void hideInputPanel() QEXT_OVERRIDE;

    void showInputPanel() QEXT_OVERRIDE;

    bool isAnimating() const QEXT_OVERRIDE;

    QRectF keyboardRect() const QEXT_OVERRIDE;

    bool isInputPanelVisible() const QEXT_OVERRIDE;

    void setFocusObject(QObject *object) QEXT_OVERRIDE;

    void update(Qt::InputMethodQueries queries) QEXT_OVERRIDE;

    Q_INVOKABLE void commit() QEXT_OVERRIDE;

    Q_INVOKABLE void commit(const QString &text, int replaceFrom = 0, int replaceLength = 0);

    void sendKeyClick(int key, const QString &text, int modifiers = 0);

    void sendKeyEvent(QKeyEvent *event);

    void setPreeditText(const QString &text, AttributesList attributes = AttributesList(),
                        int replaceFrom = 0, int replaceLength = 0);

    void sendEvent(QEvent *event);

    QSize inputPanelSize() const;
    void setInputPanelSize(const QSize &size);
    void setInputPanelSize(int width, int height);

    PopupModeEnum inputPanelPopupMode() const;
    void setInputPanelPopupMode(PopupModeEnum mode);

Q_SIGNALS:
    void inputMethodHintsChanged();
    void inputPanelSizeChanged(const QSize &size);
    void inputPanelPopupModeChanged(PopupModeEnum mode);

private Q_SLOTS:
    void hideKeyboard();

protected:
    QExtKeyboardInputContext();

    void updateInputPanelVisible();

    QVariant inputMethodQuery(Qt::InputMethodQuery query);

    void sendPreedit(const QString &text, const AttributesList &attributes,
                     int replaceFrom, int replaceLength);

    QScopedPointer<QExtKeyboardInputContextPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtKeyboardInputContext)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtKeyboardInputContext)
};

#endif // _QEXTKEYBOARDINPUTCONTEXT_H
