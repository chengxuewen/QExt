#ifndef _QEXTREGEXP_H
#define _QEXTREGEXP_H

#include <qextGlobal.h>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#   include <QRegExp>
#   define QEXT_REGEXP_VALIDATOR_HEADER  #include <QRegExpValidator>
#   define QEXT_MAKE_REGEXP_VALIDATOR(regExp, parent) new QRegExpValidator(regExp, parent)
#else
#   include <QRegularExpression>
#   define QEXT_REGEXP_VALIDATOR_HEADER  #include <QRegularExpressionValidator>
#   define QEXT_MAKE_REGEXP_VALIDATOR(regExp, parent) new QRegularExpressionValidator(regExp, parent)
#endif

class QEXT_CORE_API QExtRegExp
{
public:
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    typedef QRegExp RawType;
#else
    typedef QRegularExpression RawType;
#endif

    QExtRegExp() {}
    explicit QExtRegExp(const QString &pattern) : mRaw(pattern) { }
    QExtRegExp(const QExtRegExp &other) : mRaw(other.mRaw) { }
    QExtRegExp &operator=(const QExtRegExp &other)
    {
        if (this != &other)
        {
            mRaw = other.mRaw;
        }
        return *this;
    }
#if QEXT_CC_CPP11_OR_GREATER
    QExtRegExp &operator=(QExtRegExp &&other) noexcept
    {
        this->swap(other);
        return *this;
    }
#endif
    virtual ~QExtRegExp() {}

    bool exactMatch(const QString &str) const
    {
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
        return mRaw.exactMatch(str);
#else
        return mRaw.match(str).isValid();
#endif
    }

    bool isValid() const { return mRaw.isValid(); }
    QString errorString() const { return mRaw.errorString(); }

    RawType &raw() { return mRaw; }
    void swap(QExtRegExp &other) noexcept { mRaw.swap(other.mRaw); }
    bool operator==(const QExtRegExp &other) const { return mRaw == other.mRaw; }
    inline bool operator!=(const QExtRegExp &other) const { return !operator==(other); }

private:
    RawType mRaw;
};

#endif // _QEXTREGEXP_H
