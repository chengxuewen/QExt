#ifndef _QEXTPLOTDATA_H
#define _QEXTPLOTDATA_H

#include <QVector>

#include <qextAny.h>
#include <qextRange.h>
#include <qextOptional.h>
#include <qextTypeTrait.h>

typedef QHash<QString, QVariant> QExtPlotAttributes;

class QExtPlotDataBase
{
public:
    QExtPlotDataBase() {}
    virtual ~QExtPlotDataBase() {}

    QEXT_STATIC_CONSTANT_NUMBER(CapacityMax, 1024 * 1024)
    QEXT_STATIC_CONSTANT_NUMBER(ASyncBufferCapacityMax, 1024)

    virtual void clear() = 0;
    virtual int size() const = 0;
    virtual bool isTimeseries() const = 0;
    virtual const QString& plotName() const = 0;

    virtual QExtRangeF xRange() const = 0;
    virtual QExtRangeF yRange() const = 0;
};

// A Generic series of points
template <typename TypeX, typename Value>
class QExtPlotData : public QExtPlotDataBase
{
public:
    class Point
    {
    public:
        TypeX x;
        Value y;

        Point() {}
        Point(TypeX x, Value y)
        {
            this->x = x;
            this->y = y;
        }
        virtual ~Point() {}
    };

    typedef Value ValueType;

    typedef QVector<Point> Points;
    typedef typename Points::iterator Iterator;
    typedef typename Points::const_iterator ConstIterator;
    typedef typename Points::reference Reference;
    typedef typename Points::const_reference ConstReference;

    QExtPlotData(const QString &name)
        : mName(name), mXRangeDirty(true), mYRangeDirty(true)
    {
    }
    ~QExtPlotData() QEXT_OVERRIDE {}

    void clear() QEXT_OVERRIDE
    {
        mPoints.clear();
        mXRange.clear();
        mYRange.clear();
        mXRangeDirty = true;
        mYRangeDirty = true;
    }
    int size() const QEXT_OVERRIDE { return mPoints.size(); }
    bool isTimeseries() const QEXT_OVERRIDE { return false; }
    const QString& plotName() const QEXT_OVERRIDE { return mName; }

    QExtRangeF xRange() const QEXT_OVERRIDE
    {
        if (QExtIsArithmetic<TypeX>::value && !mPoints.isEmpty())
        {
            if (mXRangeDirty)
            {
                mXRange.clear();
                ConstIterator iter = mPoints.cbegin();
                while (mPoints.constEnd() != iter)
                {
                    mXRange.setMin(std::min(mXRange.min(), iter->x));
                    mXRange.setMax(std::max(mXRange.max(), iter->x));
                    ++iter;
                }
                mXRangeDirty = false;
            }
            return mXRange;
        }
        return QExtRangeF();
    }
    QExtRangeF yRange() const QEXT_OVERRIDE
    {
        if (QExtIsArithmetic<Value>::value && !mPoints.isEmpty())
        {
            if (mYRangeDirty)
            {
                mYRange.clear();
                ConstIterator iter = mPoints.cbegin();
                while (mPoints.constEnd() != iter)
                {
                    mYRange.setMin(std::min(mYRange.min(), iter->y));
                    mYRange.setMax(std::max(mYRange.max(), iter->y));
                    ++iter;
                }
                mYRangeDirty = false;
            }
            return mYRange;
        }
        return QExtRangeF();
    }

    virtual void pushBack(const Point& point)
    {
        if (this->pushUpdateXYRange(point))
        {
            mPoints.append(point);
        }
    }

#if QEXT_CC_CPP11_OR_GREATER
    virtual void pushBack(Point&& point)
    {
        if (this->pushUpdateXYRange(point))
        {
            mPoints.append(point);
        }
    }
#endif

    virtual void insert(Iterator iter, const Point& point)
    {
        if (this->pushUpdateXYRange(point))
        {
            mPoints.insert(iter, point);
        }
    }

#if QEXT_CC_CPP11_OR_GREATER
    virtual void insert(Iterator iter, Point&& point)
    {
        if (this->pushUpdateXYRange(point))
        {
            mPoints.insert(iter, point);
        }
    }
#endif

    virtual void popFront()
    {
        const ConstReference &point = mPoints.front();

        if QEXT_CONSTEXPR (QExtIsArithmetic<TypeX>::value)
        {
            if (!mXRangeDirty && (point.x == mXRange.min() || point.x == mYRange.max()))
            {
                mXRangeDirty = true;
            }
        }

        if QEXT_CONSTEXPR (QExtIsArithmetic<Value>::value)
        {
            if (!mYRangeDirty && (point.y == mYRange.min() || point.y == mYRange.max()))
            {
                mYRangeDirty = true;
            }
        }
        mPoints.pop_front();
    }

    Point& at(size_t index) { return mPoints.at(index); }
    const Point &at(size_t index) const { return mPoints.at(index); }

    Point& operator[](size_t index) { return this->at(index); }
    const Point& operator[](size_t index) const { return this->at(index); }

    QExtPlotAttributes& attributes() { return mAttributes; }
    const QExtPlotAttributes& attributes() const { return mAttributes; }

    QVariant attribute(const QString& id) const
    {
        return mAttributes.value(id, QVariant());
    }
    void setAttribute(const QString& id, const QVariant &value)
    {
        mAttributes[id] = value;
        this->onAttributeChanged(id, value);
    }

    const Point& front() const { return mPoints.front(); }
    const Point& back() const { return mPoints.back(); }

    ConstIterator begin() const { return mPoints.begin(); }
    ConstIterator end() const { return mPoints.end(); }

    Iterator begin() { return mPoints.begin(); }
    Iterator end() {  return mPoints.end(); }

protected:
    void onAttributeChanged(const QString &id, const QVariant &value) { Q_UNUSED(id); Q_UNUSED(value); }

    // template specialization for types that support compare operator
    virtual void pushUpdateXRange(const Point& point)
    {
        if QEXT_CONSTEXPR (QExtIsArithmetic<TypeX>::value)
        {
            if (mPoints.isEmpty())
            {
                mXRangeDirty = false;
                mXRange.setMin(point.x);
                mXRange.setMax(point.x);
            }
            if (!mXRangeDirty)
            {
                if (point.x > mXRange.max())
                {
                    mXRange.setMax(point.x);
                }
                else if (point.x < mXRange.min())
                {
                    mXRange.setMin(point.x);
                }
                else
                {
                    mXRangeDirty = true;
                }
            }
        }
    }

    // template specialization for types that support compare operator
    virtual void pushUpdateYRange(const Point& point)
    {
        if QEXT_CONSTEXPR (QExtIsArithmetic<Value>::value)
        {
            if (!mYRangeDirty)
            {
                if (point.y > mYRange.max())
                {
                    mYRange.setMax(point.y);
                }
                else if (point.y < mYRange.min())
                {
                    mYRange.setMin(point.y);
                }
                else
                {
                    mYRangeDirty = true;
                }
            }
        }
    }

    bool pushUpdateXYRange(const Point& point)
    {
        if QEXT_CONSTEXPR (QExtIsArithmetic<TypeX>::value)
        {
            if (std::isinf(point.x) || std::isnan(point.x))
            {
                return false;  // skip
            }
            this->pushUpdateXRange(point);
        }
        if QEXT_CONSTEXPR (QExtIsArithmetic<Value>::value)
        {
            if (std::isinf(point.y) || std::isnan(point.y))
            {
                return false;  // skip
            }
            this->pushUpdateYRange(point);
        }
        return true;
    }

protected:
    Points mPoints;
    const QString mName;
    mutable bool mXRangeDirty;
    mutable bool mYRangeDirty;
    mutable QExtRangeF mXRange;
    mutable QExtRangeF mYRange;
    QExtPlotAttributes mAttributes;
    // QEXT_DISABLE_COPY_MOVE(QExtPlotDataBase)
};


template <typename Value>
class QExtPlotTimeSeriesDataBase : public QExtPlotData<double, Value>
{
public:
    typedef QExtPlotData<double, Value> Base;
    typedef typename Base::Point Point;
    typedef typename Base::Iterator Iterator;
    typedef typename Base::ConstIterator ConstIterator;
    typedef typename Base::Reference Reference;
    typedef typename Base::ConstReference ConstReference;

    QExtPlotTimeSeriesDataBase(const QString& name)
        : Base(name)
        , mXRangeMax(std::numeric_limits<double>::max())
    {
    }

    bool isTimeseries() const QEXT_OVERRIDE
    {
        return true;
    }

    void pushBack(const Point& point) QEXT_OVERRIDE
    {
        const bool needSorting = (!Base::mPoints.empty() && point.x < this->back().x);
        if (needSorting)
        {
            Iterator iter = std::upper_bound(Base::mPoints.begin(), Base::mPoints.end(), point, timeCompare);
            Base::insert(iter, point);
        }
        else
        {
            Base::pushBack(point);
        }
        this->trimRange();
    }

#if QEXT_CC_CPP11_OR_GREATER
    void pushBack(Point&& point) QEXT_OVERRIDE
    {
        const bool needSorting = (!Base::mPoints.empty() && point.x < this->back().x);
        if (needSorting)
        {
            Iterator iter = std::upper_bound(Base::mPoints.begin(), Base::mPoints.end(), point, timeCompare);
            Base::insert(iter, point);
        }
        else
        {
            Base::pushBack(point);
        }
        this->trimRange();
    }
#endif

    double maximumRangeX() const
    {
        return mXRangeMax;
    }
    void setMaximumRangeX(double range)
    {
        mXRangeMax = range;
        this->trimRange();
    }

    int getIndexFromX(double x) const
    {
        if (Base::mPoints.empty())
        {
            return -1;
        }
        auto lowerIter = std::lower_bound(Base::mPoints.begin(), Base::mPoints.end(), Point(x, {}), timeCompare);
        auto indexIter = std::distance(Base::mPoints.begin(), lowerIter);

        if (indexIter >= Base::mPoints.size())
        {
            return Base::mPoints.size() - 1;
        }
        if (indexIter < 0)
        {
            return 0;
        }

        if (indexIter > 0 && (std::abs(Base::mPoints[indexIter - 1].x - x) < std::abs(Base::mPoints[indexIter].x - x)))
        {
            indexIter = indexIter - 1;
        }
        return indexIter;
    }

    QExtOptional<Value> getYfromX(double x) const
    {
        int index = this->getIndexFromX(x);
        return (index < 0) ? qextMakeNullopt() : qextMakeOptional(Base::mPoints[index].y);
    }


private:
    void trimRange()
    {
        if (mXRangeMax < std::numeric_limits<double>::max() && !Base::mPoints.empty())
        {
            const double backPointX = Base::mPoints.back().x;
            while (Base::mPoints.size() > 2 && (backPointX - Base::mPoints.front().x) > mXRangeMax)
            {
                this->popFront();
            }
        }
    }

    static bool timeCompare(const Point& lhs, const Point& rhs)
    {
        return lhs.x < rhs.x;
    }

protected:
    double mXRangeMax;
};

typedef QExtPlotData<double, double> QExtPlotScatterData;
typedef QExtPlotTimeSeriesDataBase<double> QExtPlotTimeSeriesData;
typedef QExtPlotTimeSeriesDataBase<QExtAny> QExtPlotTimeSeriesAnyData;

typedef QHash<QString, QExtPlotScatterData> QExtPlotScatterDataMap;
typedef QHash<QString, QExtPlotTimeSeriesData> QExtPlotTimeSeriesDataMap;
typedef QHash<QString, QExtPlotTimeSeriesAnyData> QExtPlotTimeSeriesAnyDataMap;

#endif // _QEXTPLOTDATA_H
