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
    int mCurPage;
    int mMaxPage;
    QVector<QPair<int, QString>> mPage1;
    QMap<QAbstractButton *, int> mKeyMap;
    QVector<QAbstractButton *> mSymbolButtons;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSymbolKeyboard)
};

#endif // _QEXTSYMBOLKEYBOARD_H
