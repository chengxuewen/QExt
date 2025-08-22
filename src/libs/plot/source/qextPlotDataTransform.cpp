#include <qextPlotDataTransform.h>

#include <qextInputDialog.h>

#include <QMutex>

typedef QHash<QString, QExtPlotDataTransformCreaterFunc> QExtPlotDataTransformCreaterMap;

class QExtPlotDataTransformFactoryPrivate
{
    QExtPlotDataTransformFactory * const q_ptr;
    Q_DECLARE_PUBLIC(QExtPlotDataTransformFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotDataTransformFactoryPrivate)
public:
    explicit QExtPlotDataTransformFactoryPrivate(QExtPlotDataTransformFactory *q);
    virtual ~QExtPlotDataTransformFactoryPrivate();

    mutable QMutex mMutex;
    QExtPlotDataTransformCreaterMap mTransformCreaterMaps;
};

QExtPlotDataTransformFactoryPrivate::QExtPlotDataTransformFactoryPrivate(QExtPlotDataTransformFactory *q)
    : q_ptr(q)
{
}

QExtPlotDataTransformFactoryPrivate::~QExtPlotDataTransformFactoryPrivate()
{
}

QExtPlotDataTransformFactory::QExtPlotDataTransformFactory(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtPlotDataTransformFactoryPrivate(this))
{
    // this->registerTransform<QExtDASerialPortTransform>(QExtDAConstants::IODEVICE_TYPE_SERIALPORT);
    // this->registerTransform<QExtDATcpSocketTransform>(QExtDAConstants::IODEVICE_TYPE_TCPSOCKET);
    // this->registerTransform<QExtDAUdpSocketTransform>(QExtDAConstants::IODEVICE_TYPE_UDPSOCKET);
}

QExtPlotDataTransformFactory::~QExtPlotDataTransformFactory()
{
}

QStringList QExtPlotDataTransformFactory::registeredTransformTypes() const
{
    Q_D(const QExtPlotDataTransformFactory);
    QMutexLocker locker(&d->mMutex);
    return d->mTransformCreaterMaps.keys();
}

QExtPlotDataTransform::SharedPtr QExtPlotDataTransformFactory::createTransform(const QString &type) const
{
    Q_D(const QExtPlotDataTransformFactory);
    QMutexLocker locker(&d->mMutex);
    QExtPlotDataTransformCreaterMap::ConstIterator iter = d->mTransformCreaterMaps.find(type);
    if (d->mTransformCreaterMaps.constEnd() != iter)
    {
        QExtPlotDataTransformCreaterFunc func = iter.value();
        if (func)
        {
            return func();
        }
    }
    return QEXT_NULLPTR;
}

void QExtPlotDataTransformFactory::registerTransform(const QString &type, QExtPlotDataTransformCreaterFunc func)
{
    Q_D(QExtPlotDataTransformFactory);
    QMutexLocker locker(&d->mMutex);
    d->mTransformCreaterMaps.insert(type, func);
}

QStandardItemModel *QExtPlotDataTransformFactory::makeTransformTypesListModel(QObject *parent) const
{
    const QStringList types = this->registeredTransformTypes();
    QStandardItemModel *model = new QStandardItemModel(parent);
    for (int i = 0; i < types.size(); ++i)
    {
        model->appendRow(new QStandardItem(types.at(i)));
    }
    return model;
}

QExtPlotDataTransform::SharedPtr QExtPlotDataTransformFactory::selectCreateTransform(QWidget *parent) const
{
    bool ok = false;
    const QStringList types = this->registeredTransformTypes();
    const QString type = QExtInputDialog::getItem(parent, tr("Select Create Transform"),
                                                  tr("Types:"), types, 0, false, &ok,
                                                  Qt::Dialog);
    if (ok && !type.isEmpty())
    {
        return this->createTransform(type);
    }
    return QEXT_NULLPTR;
}
