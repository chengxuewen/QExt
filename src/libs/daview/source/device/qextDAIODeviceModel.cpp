#include <qextDAIODeviceModel.h>
#include <qextDAIODeviceManager.h>
#include <qextDAIODevice.h>

#include <QPointer>
#include <QDebug>

class QExtDAIODeviceModelPrivate
{
public:
    explicit QExtDAIODeviceModelPrivate(QExtDAIODeviceModel *q);
    virtual ~QExtDAIODeviceModelPrivate();

    QExtDAIODeviceModel * const q_ptr;

    bool mEditable;
    QPointer<QExtDAIODeviceManager> mIODeviceManager;

private:
    Q_DECLARE_PUBLIC(QExtDAIODeviceModel)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceModelPrivate)
};

QExtDAIODeviceModelPrivate::QExtDAIODeviceModelPrivate(QExtDAIODeviceModel *q)
    : q_ptr(q)
    , mEditable(true)
{
}

QExtDAIODeviceModelPrivate::~QExtDAIODeviceModelPrivate()
{
}

QExtDAIODeviceModel::QExtDAIODeviceModel(QExtDAIODeviceManager *ioDeviceManager, QObject *parent)
    : QAbstractTableModel(parent)
    , dd_ptr(new QExtDAIODeviceModelPrivate(this))
{
    Q_D(QExtDAIODeviceModel);
    d->mIODeviceManager = ioDeviceManager;
    connect(ioDeviceManager, &QExtDAIODeviceManager::ioDeviceAboutToBeDelete, this,
            [=](const QExtDAIODevice::SharedPointer &/*ioDevice*/, qint64 /*id*/)
            {
                this->beginResetModel();
            });
    connect(ioDeviceManager, &QExtDAIODeviceManager::ioDeviceDeleted, this,
            [=](qint64 /*id*/)
            {
                this->endResetModel();
            });

    connect(ioDeviceManager, &QExtDAIODeviceManager::ioDeviceAboutToBeCreated, this,
            [=](qint64 /*id*/)
            {
                this->beginResetModel();
            });
    connect(ioDeviceManager, &QExtDAIODeviceManager::ioDeviceCreated, this,
            [=](const QExtDAIODevice::SharedPointer &/*ioDevice*/, qint64 /*id*/)
            {
                this->endResetModel();
            });

    connect(ioDeviceManager, &QExtDAIODeviceManager::ioDevicePropertyChanged, this,
            [=](const QExtDAIODevice::SharedPointer &ioDevice, const QString &name)
            {
                int row = d->mIODeviceManager->ioDeviceIndex(ioDevice);
                QModelIndex leftTopIndex = this->index(row, 0);
                QModelIndex rightBottomIndex = this->index(row, ColumnEnumNum - 1);
                emit this->dataChanged(leftTopIndex, rightBottomIndex);
            });
}

QExtDAIODeviceModel::~QExtDAIODeviceModel()
{
}

int QExtDAIODeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const QExtDAIODeviceModel);
    return d->mIODeviceManager->ioDeviceCount();
}

int QExtDAIODeviceModel::columnCount(const QModelIndex &parent) const
{
    return ColumnEnumNum;
}

QVariant QExtDAIODeviceModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QExtDAIODeviceModel);
    // check index
    if (!index.isValid())
    {
        return QVariant();
    }

    QExtDAIODevice::SharedPointer ioDevice = d->mIODeviceManager->ioDevice(index.row());
    if (ioDevice)
    {
        switch (index.column())
        {
        case Column_Name:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->name();
            }
            break;
        }
        case Column_Alias:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->alias();
            }
            break;
        }
        case Column_Type:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->ioType();
            }
            break;
        }
        case Column_State:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->ioState();
            }
            break;
        }
        case Column_Path:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->ioPath();
            }
            break;
        }
        case Column_Error:
        {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return ioDevice->ioError();
            }
            break;
        }
        default:
            break;
        }
    }

    return QVariant();
}

bool QExtDAIODeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(QExtDAIODeviceModel);
    // check index
    if (!index.isValid())
    {
        return false;
    }

    bool ret = false;
    QExtDAIODevice::SharedPointer ioDevice = d->mIODeviceManager->ioDevice(index.row());
    if (ioDevice)
    {
        // set name
        switch (index.column())
        {
        case Column_Alias:
        {
            if (Qt::EditRole == role)
            {
                ioDevice->setAlias(value.toString());
                ret = true;
            }
            break;
        }
        default:
            break;
        }
    }

    if (ret)
    {
        emit this->dataChanged(index, index, QVector< int >({ role }));
    }

    return ret;
}

Qt::ItemFlags QExtDAIODeviceModel::flags(const QModelIndex &index) const
{
    switch (index.column())
    {
    case Column_Name:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_Alias:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case Column_Type:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_Path:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_State:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_Error:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    default:
        break;
    }

    return Qt::NoItemFlags;
}

QVariant QExtDAIODeviceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            if (section >= 0 && section < ColumnEnumNum)
            {
                return QExtDAIODeviceModel::columnEnumName(section);
            }
        }
    }
    else // vertical
    {
        if (role == Qt::DisplayRole)
        {
            return QString::number(section + 1);
        }
    }

    return QVariant();
}

bool QExtDAIODeviceModel::isEditable() const
{
    Q_D(const QExtDAIODeviceModel);
    return d->mEditable;
}

void QExtDAIODeviceModel::setEditable(bool enable)
{
    Q_D(QExtDAIODeviceModel);
    if (enable != d->mEditable)
    {
        d->mEditable = enable;
        QModelIndex leftTopIndex = this->index(0, 0);
        QModelIndex rightBottomIndex = this->index(this->rowCount() - 1, ColumnEnumNum - 1);
        emit this->dataChanged(leftTopIndex, rightBottomIndex);
    }
}

QExtDAIODeviceManager *QExtDAIODeviceModel::ioDeviceManager() const
{
    Q_D(const QExtDAIODeviceModel);
    return d->mIODeviceManager.data();
}

QExtDAIODevice::SharedPointer QExtDAIODeviceModel::ioDevice(int row) const
{
    Q_D(const QExtDAIODeviceModel);
    if (row < 0 || row >= d->mIODeviceManager->ioDeviceCount())
    {
        qCritical() << "QExtDAIODeviceModel::ioDevice():row out of range";
        return QEXT_NULLPTR;
    }
    return d->mIODeviceManager->ioDevice(row);
}

QExtDAIODevice::SharedPointer QExtDAIODeviceModel::ioDevice(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        qCritical() << "QExtDAIODeviceModel::ioDevice():index invalid";
        return QEXT_NULLPTR;
    }
    return this->ioDevice(index.row());
}

QString QExtDAIODeviceModel::columnEnumName(int type, bool isEng)
{
    switch (type)
    {
    case Column_Name:
        return isEng ? "Name" : tr("Name");
    case Column_Alias:
        return isEng ? "Alias" : tr("Alias");
    case Column_Type:
        return isEng ? "Type" : tr("Type");
    case Column_Path:
        return isEng ? "Path" : tr("Path");
    case Column_State:
        return isEng ? "State" : tr("State");
    case Column_Error:
        return isEng ? "Error" : tr("Error");
    default:
        break;
    }
    return "";
}
