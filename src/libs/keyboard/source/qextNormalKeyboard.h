#ifndef _QEXTNORMALKEYBOARD_H
#define _QEXTNORMALKEYBOARD_H

#include <qextKeyboardGlobal.h>

#include <QMap>
#include <QWidget>
#include <QPushButton>

#include <algorithm>

namespace Ui {
class QExtNormalKeyboard;
}

class QEXT_KEYBOARD_API QExtNormalKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit QExtNormalKeyboard(QWidget *parent = QEXT_NULLPTR);
    ~QExtNormalKeyboard();

Q_SIGNALS:
    void changeSymbol();
    void hideKeyboard();
    void changeLanguage();
    void keyPressed(Qt::Key key, const QString &text,Qt::KeyboardModifiers modifiers);

public Q_SLOTS:
    void setCurLanguage(const QString& lang);

private Q_SLOTS:
    void letterClicked(QAbstractButton *);

protected:
    QString buttonText(QAbstractButton *);
    //大小写字母切换
    void capsLock();

private:
    Ui::QExtNormalKeyboard *ui;
    Qt::KeyboardModifiers m_modifier;
    QMap<QAbstractButton*,Qt::Key> m_letterkeys;
    QEXT_DISABLE_COPY_MOVE(QExtNormalKeyboard)
};

#endif // _QEXTNORMALKEYBOARD_H
