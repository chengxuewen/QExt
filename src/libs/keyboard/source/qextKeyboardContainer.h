#ifndef _QEXTKEYBOARDCONTAINER_H
#define _QEXTKEYBOARDCONTAINER_H

#include <qextKeyboardGlobal.h>
#include <qextNormalKeyboard.h>
#include <qextSymbolKeyboard.h>
#include <qextCandidatesListWidget.h>

#include <QWidget>

class QPropertyAnimation;
class QExtKeyboardContainerPrivate;
class QEXT_KEYBOARD_API QExtKeyboardContainer : public QWidget
{
    Q_OBJECT
public:
    explicit QExtKeyboardContainer(QWidget *parent = nullptr);
    ~QExtKeyboardContainer() QEXT_OVERRIDE;

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

protected:
    QScopedPointer<QExtKeyboardContainerPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtKeyboardContainer)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardContainer)
};

#endif // _QEXTKEYBOARDCONTAINER_H
