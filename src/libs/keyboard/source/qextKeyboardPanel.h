#ifndef _QEXTKEYBOARDPANEL_H
#define _QEXTKEYBOARDPANEL_H

#include <qextKeyboardGlobal.h>

#include <QWidget>

class QPropertyAnimation;
class QExtKeyboardPanelPrivate;
class QEXT_KEYBOARD_API QExtKeyboardPanel : public QWidget
{
    Q_OBJECT
public:
    static QExtKeyboardPanel *instance();
    ~QExtKeyboardPanel() QEXT_OVERRIDE;

    bool isAnimating() const;

Q_SIGNALS:
    void hideKeyboard();
    void changeSymbol();
    void changeLanguage();
    void chooseCandidate(int id);
    void keyPressed(Qt::Key key, const QString &text,Qt::KeyboardModifiers modifiers);

public Q_SLOTS:
    void setLanguageName(const QString &name);
    void setCandidateList(const QStringList &texts);
    void setInputMethodHints(Qt::InputMethodHints hints);

    void onHideSymbol();
    void onChangeSymbol();
    void onAnimationFinished();

    void animationHide();
    void animationShow();
    void animationSetVisible(bool visible);

protected:
    explicit QExtKeyboardPanel(QWidget *parent = QEXT_NULLPTR);

    QScopedPointer<QExtKeyboardPanelPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtKeyboardPanel)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardPanel)
};

#endif // _QEXTKEYBOARDPANEL_H
