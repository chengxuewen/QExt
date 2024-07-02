#ifndef _QEXTPINYININPUTMETHOD_H
#define _QEXTPINYININPUTMETHOD_H

#include <qextKeyboardGlobal.h>
#include <qextAbstractInputMethod.h>

class QExtKeyboardInputContext;
class QExtPinyinInputMethodPrivate;
class QEXT_KEYBOARD_API QExtPinyinInputMethod : public QExtAbstractInputMethod
{
    Q_OBJECT
public:
    explicit QExtPinyinInputMethod(QObject *parent = QEXT_NULLPTR);
    ~QExtPinyinInputMethod() QEXT_OVERRIDE;

    QExtKeyboardInputContext *inputContext() const;
    void setInputContext(QExtKeyboardInputContext * context);

    void reset() QEXT_OVERRIDE;
    void changeLanguage() QEXT_OVERRIDE;
    void chooseCandidate(int id) QEXT_OVERRIDE;
    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtPinyinInputMethodPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPinyinInputMethod)
    QEXT_DISABLE_COPY_MOVE(QExtPinyinInputMethod)
};

#endif // _QEXTPINYININPUTMETHOD_H
