#include <qextPlotFactory.h>
#include <qextInputDialog.h>
#include <qextPlotConstants.h>

#include <QMutex>

typedef QHash<QString, QExtPlotCreaterFunc> QExtPlotCreaterMap;

class QExtPlotFactoryPrivate
{
    QExtPlotFactory * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPlotFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotFactoryPrivate)
public:
    explicit QExtPlotFactoryPrivate(QExtPlotFactory *q);
    virtual ~QExtPlotFactoryPrivate();

    mutable QMutex mMutex;
    QExtPlotCreaterMap mPlotCreaterMaps;
};

QExtPlotFactoryPrivate::QExtPlotFactoryPrivate(QExtPlotFactory *q)
    : q_ptr(q)
{
}

QExtPlotFactoryPrivate::~QExtPlotFactoryPrivate()
{
}

QExtPlotFactory::QExtPlotFactory(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtPlotFactoryPrivate(this))
{
    this->registerPlot<QExtPlot>(QExtPlotConstants::PLOT_TYPE_BASE);
}

QExtPlotFactory::~QExtPlotFactory()
{
}

QStringList QExtPlotFactory::plotTypes() const
{
    Q_D(const QExtPlotFactory);
    QMutexLocker locker(&d->mMutex);
    return d->mPlotCreaterMaps.keys();
}

QExtPlot::SharedPtr QExtPlotFactory::createPlot(const QString &type) const
{
    Q_D(const QExtPlotFactory);
    QMutexLocker locker(&d->mMutex);
    QExtPlotCreaterMap::ConstIterator iter = d->mPlotCreaterMaps.find(type);
    if (d->mPlotCreaterMaps.constEnd() != iter)
    {
        QExtPlotCreaterFunc func = iter.value();
        if (func)
        {
            return func();
        }
    }
    return QEXT_NULLPTR;
}

void QExtPlotFactory::registerPlot(const QString &type, QExtPlotCreaterFunc func)
{
    Q_D(QExtPlotFactory);
    QMutexLocker locker(&d->mMutex);
    d->mPlotCreaterMaps.insert(type, func);
}

QStandardItemModel *QExtPlotFactory::makePlotTypeListModel(QObject *parent) const
{
    const QStringList types = this->plotTypes();
    QStandardItemModel *model = new QStandardItemModel(parent);
    for (int i = 0; i < types.size(); ++i)
    {
        model->appendRow(new QStandardItem(types.at(i)));
    }
    return model;
}

QExtPlot::SharedPtr QExtPlotFactory::selectCreatePlot(QWidget *parent) const
{
    bool ok = false;
    const QStringList types = this->plotTypes();
    const QString type = QExtInputDialog::getItem(parent, tr("Select Create Plot"),
                                                  tr("Types:"), types, 0, false, &ok,
                                                  Qt::Dialog);
    if (ok && !type.isEmpty())
    {
        return this->createPlot(type);
    }
    return QEXT_NULLPTR;
}

