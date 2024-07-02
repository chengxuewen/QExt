#ifndef _QEXTABSTRACTINPUTMETHOD_H
#define _QEXTABSTRACTINPUTMETHOD_H

#include <QObject>

class QExtAbstractInputMethod : public QObject
{
    Q_OBJECT
public:
    enum InputMode
    {
        Latin,
        Numeric,
        Dialable,
        Pinyin,
        Cangjie,
        Zhuyin,
        Hangul,
        Hiragana,
        Katakana,
        FullwidthLatin,
        Greek,
        Cyrillic,
        Arabic,
        Hebrew,
        ChineseHandwriting,
        JapaneseHandwriting,
        KoreanHandwriting,
        Thai
    };

    explicit QExtAbstractInputMethod(QObject *parent = 0) : QObject(parent) {}
    ~QExtAbstractInputMethod() {}

    virtual void reset() {}
    virtual void changeLanguage() {}
    virtual void chooseCandidate(int) {}
    virtual bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) = 0;

Q_SIGNALS:
    void showLanguageName(const QString & name);
    void showCandidateList(const QStringList & strings);
};

#endif // _QEXTABSTRACTINPUTMETHOD_H
