#ifndef _QEXTPLOTFACTORY_H
#define _QEXTPLOTFACTORY_H

#include <qextPlotGlobal.h>
#include <qextTypeTrait.h>
#include <qextPlot.h>

#include <QObject>
#include <QStandardItemModel>

typedef QExtPlot::SharedPtr(*QExtPlotCreaterFunc)();

template <typename T>
QExtPlot::SharedPtr qextMakePlot()
{
    enum { Valid = QExtIsBaseOf<QExtPlot, T>::value };
    QEXT_STATIC_ASSERT_X(Valid, "type must base on QExtPlot.");
    return QExtPlot::SharedPtr(new T);
}

template <typename T>
QExtPlotCreaterFunc qextPlotCreaterFunction()
{
    return &qextMakePlot<T>;
}

template <typename T>
struct QExtPlotCreaterFunctor
{
    QExtPlotCreaterFunc operator ()() { return new T; }
};

class QExtPlotFactoryPrivate;
class QEXT_PLOT_API QExtPlotFactory : public QObject
{
    Q_OBJECT
public:
    explicit QExtPlotFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtPlotFactory() QEXT_OVERRIDE;

    template <typename T>
    void registerPlot(const QString &type)
    {
        enum { Valid = QExtIsBaseOf<QExtPlot, T>::value };
        QEXT_STATIC_ASSERT_X(Valid, "type must base on QExtPlot.");
        this->registerPlot(type, qextPlotCreaterFunction<T>());
    }

    virtual QStringList plotTypes() const;
    virtual QExtPlot::SharedPtr createPlot(const QString &type) const;
    virtual void registerPlot(const QString &type, QExtPlotCreaterFunc func);

    virtual QStandardItemModel *makePlotTypeListModel(QObject *parent = QEXT_NULLPTR) const;
    virtual QExtPlot::SharedPtr selectCreatePlot(QWidget *parent = QEXT_NULLPTR) const;

protected:
    QScopedPointer<QExtPlotFactoryPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtPlotFactory)
    QEXT_DISABLE_COPY_MOVE(QExtPlotFactory)
};

#endif // _QEXTPLOTFACTORY_H
