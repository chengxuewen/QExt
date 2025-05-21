#ifndef _QEXTSYMBOLKEYBOARD_H
#define _QEXTSYMBOLKEYBOARD_H

#include <qextKeyboardGlobal.h>

#include <QMap>
#include <QWidget>
#include <QVector>
#include <QAbstractButton>

namespace Ui {
class QExtSymbolKeyboard;
}

class QEXT_KEYBOARD_API QExtSymbolKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit QExtSymbolKeyboard(QWidget *parent = QEXT_NULLPTR);
    ~QExtSymbolKeyboard();

Q_SIGNALS:
    void changeSymbol();
    void hideKeyboard();
    void changeLanguage();
    void keyPressed(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

public Q_SLOTS:
    void setCurLanguage(const QString &lang);

private Q_SLOTS:
    void onChangePage();
    void onSymbolButtonClicked(QAbstractButton *);

protected:
    void buttonRemap();
    QString buttonText(QAbstractButton *);

private:
    Ui::QExtSymbolKeyboard *ui;
    int m_curPage;
    int m_maxPage;
    QVector<QPair<int, QString>> m_page1;
    QMap<QAbstractButton *, int> m_keyMap;
    QVector<QAbstractButton *> m_symbolButtons;
    QEXT_DISABLE_COPY_MOVE(QExtSymbolKeyboard)
};

#endif // _QEXTSYMBOLKEYBOARD_H
