#ifndef _QEXTSYSTEMKEYBOARD_H
#define _QEXTSYSTEMKEYBOARD_H

#include <qextKeyboardGlobal.h>

#include <QObject>

class QExtSystemKeyboardPrivate;
class QEXT_KEYBOARD_API QExtSystemKeyboard : public QObject
{
    Q_OBJECT
public:
    static QExtSystemKeyboard *instance();
    ~QExtSystemKeyboard() QEXT_OVERRIDE;

public Q_SLOTS:
    void hideKeyboard();
    void showKeyboard();

protected:
    explicit QExtSystemKeyboard(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtSystemKeyboardPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtSystemKeyboard)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSystemKeyboard)
};

#endif // _QEXTSYSTEMKEYBOARD_H
