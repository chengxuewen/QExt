#ifndef _QEXTQMLFONTICONINFO_H
#define _QEXTQMLFONTICONINFO_H

#include <qextQmlFontIconGlobal.h>
#include <qextQmlSingleton.h>

class QExtQmlFontIconInfo : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)
public:
    QExtQmlFontIconInfo() {}
    QExtQmlFontIconInfo(const QString &family, const QString &text) : mText(text), mFamily(family) {}
    QExtQmlFontIconInfo(const QExtQmlFontIconInfo &other) : mText(other.mText), mFamily(other.mFamily) {}

    QExtQmlFontIconInfo &operator =(const QExtQmlFontIconInfo &other)
    {
        if (this != &other)
        {
            mText = other.mText;
            mFamily = other.mFamily;
        }
        return *this;
    }

    bool operator==(const QExtQmlFontIconInfo &other) const
    {
        if (this != &other)
        {
            return mText == other.mText && mFamily == other.mFamily;
        }
        return true;
    }
    bool operator!=(const QExtQmlFontIconInfo &other) const
    {
        return !(*this == other);
    }

    QString text() const { return mText; }
    void setText(const QString &text)
    {
        if (text != mText)
        {
            mText = text;
            emit this->textChanged(text);
        }
    }

    QString family() const { return mFamily; }
    void setFamily(const QString &family)
    {
        if (family != mFamily)
        {
            mFamily = family;
            emit this->familyChanged(family);
        }
    }

Q_SIGNALS:
    void textChanged(const QString &text);
    void familyChanged(const QString &family);

private:
    QString mText;
    QString mFamily;
};

#endif // _QEXTQMLFONTICONINFO_H
