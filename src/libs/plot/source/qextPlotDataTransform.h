#ifndef _QEXTPLOTDATATRANSFORM_H
#define _QEXTPLOTDATATRANSFORM_H

#include <qextPlotGlobal.h>
#include <qextSingleton.h>

#include <QObject>
#include <QSharedPointer>
#include <QStandardItemModel>

class QExtPlotDataTransform : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtPlotDataTransform> SharedPtr;

    QExtPlotDataTransform(QObject *parent = QEXT_NULLPTR);
    ~QExtPlotDataTransform() QEXT_OVERRIDE {}

    virtual const char* name() const = 0;
    virtual int numOutputs() const = 0;
    virtual int numInputs() const = 0;
    virtual void calculate() = 0;
    virtual void reset() { }
    // PlotDataMapRef* plotData()
    // {
    //     return _data;
    // }
    // unsigned order() const
    // {
    //     return _order;
    // }

    // std::vector<const PlotData*>& dataSources();
    // virtual void setData(PlotDataMapRef* data, const std::vector<const PlotData*>& src_vect,
    // std::vector<PlotData*>& dst_vect);
};

/// Simplified version with Single input and Single output
class QExtPlotDataSISOTransform : public QExtPlotDataTransform
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtPlotDataSISOTransform> SharedPtr;

    QExtPlotDataSISOTransform(QObject *parent = QEXT_NULLPTR) : QExtPlotDataTransform(parent) {}
    ~QExtPlotDataSISOTransform() QEXT_OVERRIDE {}
};


typedef QExtPlotDataTransform::SharedPtr(*QExtPlotDataTransformCreaterFunc)();

template <typename T>
QExtPlotDataTransform::SharedPtr qextMakePlotDataTransform()
{
    return QExtPlotDataTransform::SharedPtr(new T);
}

template <typename T>
QExtPlotDataTransformCreaterFunc qextPlotDataTransformCreaterFunction()
{
    return []() { return QExtPlotDataTransform::SharedPtr(new T); };
}

template <typename T>
struct QExtPlotDataTransformCreaterFunctor
{
    QExtPlotDataTransformCreaterFunc operator ()() { return new T; }
};

class QExtPlotDataTransformFactoryPrivate;
class QEXT_PLOT_API QExtPlotDataTransformFactory : public QObject, public QExtSingleton<QExtPlotDataTransformFactory>
{
    Q_OBJECT
    QEXT_DECL_SINGLETON(QExtPlotDataTransformFactory)
public:
    typedef QExtPlotDataTransformFactory Self;

    template <typename T>
    void registerTransform(const QString &type)
    {
        // QEXT_STATIC_ASSERT(QExtIsBaseOf<QExtPlotDataTransform, T>::value)
        this->registerTransform(type, qextPlotDataTransformCreaterFunction<T>());
    }

    QStringList registeredTransformTypes() const;
    QExtPlotDataTransform::SharedPtr createTransform(const QString &type) const;
    void registerTransform(const QString &type, QExtPlotDataTransformCreaterFunc func);

    QStandardItemModel *makeTransformTypesListModel(QObject *parent = QEXT_NULLPTR) const;
    QExtPlotDataTransform::SharedPtr selectCreateTransform(QWidget *parent = QEXT_NULLPTR) const;

protected:
    explicit QExtPlotDataTransformFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtPlotDataTransformFactory() QEXT_OVERRIDE;

private:
    QScopedPointer<QExtPlotDataTransformFactoryPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtPlotDataTransformFactory)
    QEXT_DISABLE_COPY_MOVE(QExtPlotDataTransformFactory)
};

#define qextPlotDataTransformFactory QExtPlotDataTransformFactory::instance()

#endif // _QEXTPLOTDATATRANSFORM_H
