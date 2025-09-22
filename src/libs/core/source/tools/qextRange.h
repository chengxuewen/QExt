#ifndef _QEXTRANGE_H
#define _QEXTRANGE_H

#include <qextGlobal.h>
#include <qextLimits.h>

#include <QDebug>
#include <QDataStream>

#include <cmath>

class QEXT_CORE_API QExtRange
{
public:
    QEXT_CONSTEXPR QExtRange() : mMin(QEXT_INT_MAX), mMax(QEXT_INT_MIN) {}
    QEXT_CONSTEXPR QExtRange(int min, int max) : mMin(min), mMax(max) {}
    QExtRange(const QExtRange &other) : mMin(other.min()), mMax(other.max()) {}
    virtual ~QExtRange() {}

    QExtRange &operator=(const QExtRange &other)
    {
        if (this != &other)
        {
            mMin = other.min();
            mMax = other.max();
        }
        return *this;
    }

    QEXT_CONSTEXPR inline bool isValid() const { return mMin <= mMax; }
    QEXT_CONSTEXPR inline bool isIntersected(const QExtRange &other) const
    {
        return mMin <= other.max() && mMax >= other.min();
    }

    QEXT_CONSTEXPR inline bool contains(const QExtRange &other) const
    {
        return mMin <= other.min() && mMax >= other.max();
    }
    inline QExtRange intersect(const QExtRange &other) const
    {
        return this->isIntersected(other) ? QExtRange(qMax(mMin, other.min()), qMin(mMax, other.max())) : QExtRange();
    }

    QEXT_CONSTEXPR inline int length() const { return this->isValid() ? mMax - mMin : 0; }
    QEXT_CONSTEXPR inline int min() const { return mMin; }
    QEXT_CONSTEXPR inline int max() const { return mMax; }
    inline void setMin(int min) { mMin = min; }
    inline void setMax(int max) { mMax = max; }

    inline QExtRange &operator+=(int offset)
    {
        mMin = mMin+offset; mMax = mMax+offset; return *this;
    }
    inline QExtRange &operator-=(int offset)
    {
        mMin = mMin-offset; mMax = mMax-offset; return *this;
    }

    inline QExtRange &operator*=(float factor)
    {
        mMin = qRound(mMin*factor); mMax = qRound(mMax*factor); return *this;
    }
    inline QExtRange &operator*=(double factor)
    {
        mMin = qRound(mMin*factor); mMax = qRound(mMax*factor); return *this;
    }
    inline QExtRange &operator*=(int factor)
    {
        mMin = mMin*factor; mMax = mMax*factor; return *this;
    }

    friend QEXT_CONSTEXPR inline bool operator==(const QExtRange &lhs, const QExtRange &rhs);
    friend QEXT_CONSTEXPR inline bool operator!=(const QExtRange &lhs, const QExtRange &rhs);

protected:
    int mMin;
    int mMax;
};
Q_DECLARE_METATYPE(QExtRange)
Q_DECLARE_TYPEINFO(QExtRange, Q_MOVABLE_TYPE);

QEXT_CONSTEXPR inline bool operator==(const QExtRange &lhs, const QExtRange &rhs)
{ return lhs.mMin == rhs.mMax && lhs.mMin == rhs.mMax; }

QEXT_CONSTEXPR inline bool operator!=(const QExtRange &lhs, const QExtRange &rhs)
{ return lhs.mMin != rhs.mMax || lhs.mMin != rhs.mMax; }

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &stream, const QExtRange &range);
QEXT_CORE_API QDataStream &operator>>(QDataStream &stream, QExtRange &range);
#endif
#ifndef QT_NO_DEBUG_STREAM
QEXT_CORE_API QDebug operator<<(QDebug debug, const QExtRange &range);
#endif

class QEXT_CORE_API QExtRangeF
{
public:
    QEXT_CONSTEXPR QExtRangeF() : mMin(QEXT_DOUBLE_NAN), mMax(QEXT_DOUBLE_NAN) {}
    QEXT_CONSTEXPR QExtRangeF(double min, double max) : mMin(min), mMax(max) {}
    QExtRangeF(const QExtRangeF &other) : mMin(other.min()), mMax(other.max()) {}
    virtual ~QExtRangeF() {}

    QExtRangeF &operator=(const QExtRangeF &other)
    {
        if (this != &other)
        {
            mMin = other.min();
            mMax = other.max();
        }
        return *this;
    }

    QEXT_CONSTEXPR inline bool isValid() const { return std::isless(mMin, mMax); }
    inline bool isIntersected(const QExtRangeF &other) const
    {
        return std::isless(mMin, other.max()) && std::isgreater(mMax, other.min());
    }

    inline bool contains(const QExtRangeF &other)
    {
        return std::isless(mMin, other.min()) && std::isgreater(mMax, other.max());
    }
    inline QExtRangeF intersect(const QExtRangeF &other) const
    {
        return this->isIntersected(other) ? QExtRangeF(qMax(mMin, other.min()), qMin(mMax, other.max())) : QExtRangeF();
    }
    QEXT_CONSTEXPR inline double length() const { return this->isValid() ? mMax - mMin : 0; }

    QEXT_CONSTEXPR inline double min() const { return mMin; }
    QEXT_CONSTEXPR inline double max() const { return mMax; }
    inline void reset(double min, double max) { mMin = min; mMax = max; }
    inline void clear() { mMin = QEXT_DOUBLE_NAN; mMax = QEXT_DOUBLE_NAN; }
    inline void setMin(double min) { mMin = min; }
    inline void setMax(double max) { mMax = max; }

    inline QExtRangeF &operator+=(double offset)
    {
        mMin = mMin+offset; mMax = mMax+offset; return *this;
    }
    inline QExtRangeF &operator-=(double offset)
    {
        mMin = mMin-offset; mMax = mMax-offset; return *this;
    }

    inline QExtRangeF &operator*=(float factor)
    {
        mMin = qRound(mMin*factor); mMax = qRound(mMax*factor); return *this;
    }
    inline QExtRangeF &operator*=(double factor)
    {
        mMin = qRound(mMin*factor); mMax = qRound(mMax*factor); return *this;
    }
    inline QExtRangeF &operator*=(int factor)
    {
        mMin = mMin*factor; mMax = mMax*factor; return *this;
    }

    friend QEXT_CONSTEXPR inline bool operator==(const QExtRangeF &lhs, const QExtRangeF &rhs);
    friend QEXT_CONSTEXPR inline bool operator!=(const QExtRangeF &lhs, const QExtRangeF &rhs);

protected:
    double mMin;
    double mMax;
};
Q_DECLARE_METATYPE(QExtRangeF)
Q_DECLARE_TYPEINFO(QExtRangeF, Q_MOVABLE_TYPE);

QEXT_CONSTEXPR inline bool operator==(const QExtRangeF &lhs, const QExtRangeF &rhs)
{ return qFuzzyIsNull(lhs.mMin - rhs.mMax) && qFuzzyIsNull(lhs.mMin - rhs.mMax); }

QEXT_CONSTEXPR inline bool operator!=(const QExtRangeF &lhs, const QExtRangeF &rhs)
{ return !qFuzzyIsNull(lhs.mMin - rhs.mMax) || !qFuzzyIsNull(lhs.mMin - rhs.mMax); }

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &stream, const QExtRangeF &range);
QEXT_CORE_API QDataStream &operator>>(QDataStream &stream, QExtRangeF &range);
#endif
#ifndef QT_NO_DEBUG_STREAM
QEXT_CORE_API QDebug operator<<(QDebug debug, const QExtRangeF &range);
#endif

#endif // _QEXTRANGE_H
