#ifndef _QEXTNUMBERKEYBOARD_H
#define _QEXTNUMBERKEYBOARD_H

#include <qextKeyboardGlobal.h>

#include <QWidget>

namespace Ui {
class QExtNumberKeyboard;
}

class QEXT_KEYBOARD_API QExtNumberKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit QExtNumberKeyboard(QWidget *parent = QEXT_NULLPTR);
    ~QExtNumberKeyboard();

private:
    Ui::QExtNumberKeyboard *ui;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtNumberKeyboard)
};

#endif // _QEXTNUMBERKEYBOARD_H
