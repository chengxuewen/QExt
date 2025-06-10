#ifndef _QEXTRANGE_H
#define _QEXTRANGE_H

#include <qextGlobal.h>
#include <qextLimits.h>

#include <QDebug>
#include <QDataStream>

class QEXT_CORE_API QExtRange
{
public:
    QEXT_CONSTEXPR QExtRange() : mStart(QEXT_INT_MAX), mEnd(QEXT_INT_MIN) {}
    QEXT_CONSTEXPR QExtRange(int start, int end) : mStart(start), mEnd(end) {}
    QEXT_CONSTEXPR QExtRange(const QExtRange &other) : mStart(other.start()), mEnd(other.end()) {}

    QExtRange &operator=(const QExtRange &other)
    {
        if (this != &other)
        {
            mStart = other.start();
            mEnd = other.end();
        }
        return *this;
    }

    QEXT_CONSTEXPR inline bool isValid() const { return mStart <= mEnd; }
    QEXT_CONSTEXPR inline bool isIntersected(const QExtRange &other) const
    {
        return mStart <= other.end() && mEnd >= other.start();
    }

    QEXT_CONSTEXPR inline bool contains(const QExtRange &other)
    {
        return mStart <= other.start() && mEnd >= other.end();
    }
    QEXT_CONSTEXPR inline QExtRange intersect(const QExtRange &other)
    {
        return this->isIntersected(other) ? QExtRange(qMax(mStart, other.start()), qMin(mEnd, other.end())) : QExtRange();
    }

    QEXT_CONSTEXPR inline int length() const { return this->isValid() ? mEnd - mStart : 0; }
    QEXT_CONSTEXPR inline int start() const { return mStart; }
    QEXT_CONSTEXPR inline int end() const { return mEnd; }
    QEXT_RELAXED_CONSTEXPR inline void setStart(int start) { mStart = start; }
    QEXT_RELAXED_CONSTEXPR inline void setEnd(int end) { mEnd = end; }

    QEXT_RELAXED_CONSTEXPR inline QExtRange &operator+=(int offset)
    {
        mStart = mStart+offset; mEnd = mEnd+offset; return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRange &operator-=(int offset)
    {
        mStart = mStart-offset; mEnd = mEnd-offset; return *this;
    }

    QEXT_RELAXED_CONSTEXPR inline QExtRange &operator*=(float factor)
    {
        mStart = qRound(mStart*factor); mEnd = qRound(mEnd*factor); return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRange &operator*=(double factor)
    {
        mStart = qRound(mStart*factor); mEnd = qRound(mEnd*factor); return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRange &operator*=(int factor)
    {
        mStart = mStart*factor; mEnd = mEnd*factor; return *this;
    }

    friend QEXT_CONSTEXPR inline bool operator==(const QExtRange &lhs, const QExtRange &rhs);
    friend QEXT_CONSTEXPR inline bool operator!=(const QExtRange &lhs, const QExtRange &rhs);

protected:
    int mStart;
    int mEnd;
};
Q_DECLARE_METATYPE(QExtRange)
Q_DECLARE_TYPEINFO(QExtRange, Q_MOVABLE_TYPE);

QEXT_CONSTEXPR inline bool operator==(const QExtRange &lhs, const QExtRange &rhs)
{ return lhs.mStart == rhs.mEnd && lhs.mStart == rhs.mEnd; }

QEXT_CONSTEXPR inline bool operator!=(const QExtRange &lhs, const QExtRange &rhs)
{ return lhs.mStart != rhs.mEnd || lhs.mStart != rhs.mEnd; }

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
    QEXT_CONSTEXPR QExtRangeF() : mStart(QEXT_DOUBLE_NAN), mEnd(QEXT_DOUBLE_NAN) {}
    QEXT_CONSTEXPR QExtRangeF(double start, double end) : mStart(start), mEnd(end) {}
    QEXT_CONSTEXPR QExtRangeF(const QExtRangeF &other) : mStart(other.start()), mEnd(other.end()) {}

    QExtRangeF &operator=(const QExtRangeF &other)
    {
        if (this != &other)
        {
            mStart = other.start();
            mEnd = other.end();
        }
        return *this;
    }

    inline bool isValid() const { return std::isless(mStart, mEnd); }
    inline bool isIntersected(const QExtRangeF &other) const
    {
        return std::isless(mStart, other.end()) && std::isgreater(mEnd, other.start());
    }

    inline bool contains(const QExtRangeF &other)
    {
        return std::isless(mStart, other.start()) && std::isgreater(mEnd, other.end());
    }
    QEXT_CONSTEXPR inline QExtRangeF intersect(const QExtRangeF &other)
    {
        return this->isIntersected(other) ? QExtRangeF(qMax(mStart, other.start()), qMin(mEnd, other.end())) : QExtRangeF();
    }
    QEXT_CONSTEXPR inline double length() const { return this->isValid() ? mEnd - mStart : 0; }

    QEXT_CONSTEXPR inline double start() const { return mStart; }
    QEXT_CONSTEXPR inline double end() const { return mEnd; }
    QEXT_RELAXED_CONSTEXPR inline void reset(double start, double end) { mStart = start; mEnd = end; }
    QEXT_RELAXED_CONSTEXPR inline void clear() { mStart = QEXT_DOUBLE_NAN; mEnd = QEXT_DOUBLE_NAN; }
    QEXT_RELAXED_CONSTEXPR inline void setStart(double start) { mStart = start; }
    QEXT_RELAXED_CONSTEXPR inline void setEnd(double end) { mEnd = end; }

    QEXT_RELAXED_CONSTEXPR inline QExtRangeF &operator+=(double offset)
    {
        mStart = mStart+offset; mEnd = mEnd+offset; return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRangeF &operator-=(double offset)
    {
        mStart = mStart-offset; mEnd = mEnd-offset; return *this;
    }

    QEXT_RELAXED_CONSTEXPR inline QExtRangeF &operator*=(float factor)
    {
        mStart = qRound(mStart*factor); mEnd = qRound(mEnd*factor); return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRangeF &operator*=(double factor)
    {
        mStart = qRound(mStart*factor); mEnd = qRound(mEnd*factor); return *this;
    }
    QEXT_RELAXED_CONSTEXPR inline QExtRangeF &operator*=(int factor)
    {
        mStart = mStart*factor; mEnd = mEnd*factor; return *this;
    }

    friend QEXT_CONSTEXPR inline bool operator==(const QExtRangeF &lhs, const QExtRangeF &rhs);
    friend QEXT_CONSTEXPR inline bool operator!=(const QExtRangeF &lhs, const QExtRangeF &rhs);

protected:
    double mStart;
    double mEnd;
};
Q_DECLARE_METATYPE(QExtRangeF)
Q_DECLARE_TYPEINFO(QExtRangeF, Q_MOVABLE_TYPE);

QEXT_CONSTEXPR inline bool operator==(const QExtRangeF &lhs, const QExtRangeF &rhs)
{ return qFuzzyIsNull(lhs.mStart - rhs.mEnd) && qFuzzyIsNull(lhs.mStart - rhs.mEnd); }

QEXT_CONSTEXPR inline bool operator!=(const QExtRangeF &lhs, const QExtRangeF &rhs)
{ return !qFuzzyIsNull(lhs.mStart - rhs.mEnd) || !qFuzzyIsNull(lhs.mStart - rhs.mEnd); }

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &stream, const QExtRangeF &range);
QEXT_CORE_API QDataStream &operator>>(QDataStream &stream, QExtRangeF &range);
#endif
#ifndef QT_NO_DEBUG_STREAM
QEXT_CORE_API QDebug operator<<(QDebug debug, const QExtRangeF &range);
#endif

#endif // _QEXTRANGE_H
