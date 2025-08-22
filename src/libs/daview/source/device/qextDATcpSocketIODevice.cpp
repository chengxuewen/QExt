#include <qextDATcpSocketIODevice.h>
#include <private/qextDAIODevice_p.h>
#include <qextDAIODeviceUtils.h>
#include <qextDAConstants.h>

#include <QDebug>
#include <QSpinBox>

class QExtDATcpSocketIODevicePrivate : public QExtDAIODevicePrivate
{
public:
    explicit QExtDATcpSocketIODevicePrivate(QExtDATcpSocketIODevice *q);
    ~QExtDATcpSocketIODevicePrivate() QEXT_OVERRIDE;

    bool mIsOpened;
    QString mRemoteIP;
    quint16 mRemotePort;
    QPointer<QTcpSocket> mTcpSocket;

protected:
    Q_DECLARE_PUBLIC(QExtDATcpSocketIODevice)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDATcpSocketIODevicePrivate)
};

QExtDATcpSocketIODevicePrivate::QExtDATcpSocketIODevicePrivate(QExtDATcpSocketIODevice *q)
    : QExtDAIODevicePrivate(q)
    , mIsOpened(false)
{
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
}

QExtDATcpSocketIODevicePrivate::~QExtDATcpSocketIODevicePrivate()
{
}

QExtDATcpSocketIODevice::QExtDATcpSocketIODevice(QObject *parent)
    : QExtDAIODevice(new QExtDATcpSocketIODevicePrivate(this), parent)
{
}

QExtDATcpSocketIODevice::~QExtDATcpSocketIODevice()
{
}

quint16 QExtDATcpSocketIODevice::remotePort() const
{
    Q_D(const QExtDATcpSocketIODevice);
    return d->mRemotePort;
}

void QExtDATcpSocketIODevice::setRemotePort(quint16 port)
{
    Q_D(QExtDATcpSocketIODevice);
    if (port != d->mRemotePort)
    {
        d->mRemotePort = port;
        Q_EMIT this->remotePortChanged(port);
    }
}

QString QExtDATcpSocketIODevice::remoteIP() const
{
    Q_D(const QExtDATcpSocketIODevice);
    return d->mRemoteIP;
}

void QExtDATcpSocketIODevice::setRemoteIP(const QString &ip)
{
    Q_D(QExtDATcpSocketIODevice);
    if (ip != d->mRemoteIP)
    {
        d->mRemoteIP = ip;
        Q_EMIT this->remoteIPChanged(ip);
    }
}

QString QExtDATcpSocketIODevice::ioPath() const
{
    Q_D(const QExtDATcpSocketIODevice);
    return QString("remote[%1:%2]").arg(d->mRemoteIP).arg(d->mRemotePort);
}

QString QExtDATcpSocketIODevice::ioType() const
{
    return QExtDAConstants::IODEVICE_TYPE_TCPSOCKET;
}

QThread *QExtDATcpSocketIODevice::initDevice(qint64 id)
{
    Q_D(QExtDATcpSocketIODevice);
    d->initIO(new QTcpSocket);
    d->mTcpSocket = static_cast<QTcpSocket *>(d->mIO.data());
    this->updateIOState(QExtDAIODeviceUtils::socketStateString(QAbstractSocket::UnconnectedState));
    connect(d->mTcpSocket.data(), &QTcpSocket::stateChanged, this, &QExtDATcpSocketIODevice::onTcpSocketStateChanged);
    connect(d->mTcpSocket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onTcpSocketErrorOccurred(QAbstractSocket::SocketError)));
    return QExtDAIODevice::initDevice(id);
}

void QExtDATcpSocketIODevice::serializeLoad(const SerializedItemsMap &items)
{
    QExtDAIODevice::serializeLoad(items);
    this->setRemoteIP(items.value(QExtDAConstants::TCPSOCKET_IODEVICE_PROPERTY_REMOTE_IP, "").toString());
    this->setRemotePort(items.value(QExtDAConstants::TCPSOCKET_IODEVICE_PROPERTY_REMOTE_PORT, 0).value<quint16>());
}

QExtSerializable::SerializedItemsMap QExtDATcpSocketIODevice::serializeSave() const
{
    QExtSerializable::SerializedItemsMap items = QExtDAIODevice::serializeSave();
    items[QExtDAConstants::TCPSOCKET_IODEVICE_PROPERTY_REMOTE_IP] = this->remoteIP();
    items[QExtDAConstants::TCPSOCKET_IODEVICE_PROPERTY_REMOTE_PORT] = this->remotePort();
    return items;
}

void QExtDATcpSocketIODevice::onTcpSocketStateChanged(QAbstractSocket::SocketState state)
{
    this->updateIOState(QExtDAIODeviceUtils::socketStateString(state));
    this->updateOpenState(QAbstractSocket::ConnectedState == state);
}

void QExtDATcpSocketIODevice::onTcpSocketErrorOccurred(QAbstractSocket::SocketError error)
{
    this->updateIOError(QExtDAIODeviceUtils::socketErrorString(error));
}

bool QExtDATcpSocketIODevice::ioOpen()
{
    Q_D(QExtDATcpSocketIODevice);
    d->mTcpSocket->connectToHost(d->mRemoteIP, d->mRemotePort);
    return d->mTcpSocket->waitForConnected(3000);
}

void QExtDATcpSocketIODevice::ioClose()
{
    Q_D(QExtDATcpSocketIODevice);
    d->mTcpSocket->abort();
    d->mTcpSocket->close();
}

void QExtDATcpSocketIODevice::initPropertyModel(QExtPropertyModel *propertyModel)
{
    auto rootItem = propertyModel->rootItem();
    QExtDAIODevice::initPropertyModel(propertyModel);
    rootItem->appendChild(new QExtDATcpSocketRemoteIPPropertyItem(this));
    rootItem->appendChild(new QExtDATcpSocketRemotePortPropertyItem(this));
}


QExtDATcpSocketRemoteIPPropertyItem::QExtDATcpSocketRemoteIPPropertyItem(QExtDATcpSocketIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDATcpSocketIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDATcpSocketIODevice::remoteIPChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDATcpSocketRemoteIPPropertyItem::name() const
{
    return tr("RemoteIP");
}

Qt::ItemFlags QExtDATcpSocketRemoteIPPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDATcpSocketRemoteIPPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_LineEdit;
}

QWidget *QExtDATcpSocketRemoteIPPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                 const QModelIndex &index) const
{
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDATcpSocketRemoteIPPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QExtPropertyModelItem::setEditorData(editor, index);
}

bool QExtDATcpSocketRemoteIPPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                       const QModelIndex &index) const
{
    return QExtPropertyModelItem::setModelData(editor, model, index);
}

QVariant QExtDATcpSocketRemoteIPPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->remoteIP();
    }
    return QVariant();
}

bool QExtDATcpSocketRemoteIPPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        QString ip = value.toString();
        mIODevice->setRemoteIP(ip);
        return true;
    }
    return false;
}

QExtDATcpSocketRemotePortPropertyItem::QExtDATcpSocketRemotePortPropertyItem(QExtDATcpSocketIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDATcpSocketIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDATcpSocketIODevice::remotePortChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDATcpSocketRemotePortPropertyItem::name() const
{
    return tr("RemotePort");
}

Qt::ItemFlags QExtDATcpSocketRemotePortPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDATcpSocketRemotePortPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_SpinBox;
}

QWidget *QExtDATcpSocketRemotePortPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                   const QModelIndex &index) const
{
    QSpinBox *widget = qobject_cast<QSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(1024, 65535);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDATcpSocketRemotePortPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QSpinBox *widget = qobject_cast<QSpinBox *>(editor);
        if (widget)
        {
            quint16 port = index.model()->data(index, Qt::EditRole).value<quint16>();
            widget->setValue(port);
            return true;
        }
    }
    return false;
}

bool QExtDATcpSocketRemotePortPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                         const QModelIndex &index) const
{
    if (index.isValid())
    {
        QSpinBox *widget = qobject_cast<QSpinBox *>(editor);
        if (widget)
        {
            quint16 port = quint16(widget->value());
            model->setData(index, port, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDATcpSocketRemotePortPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->remotePort();
    }
    return QVariant();
}

bool QExtDATcpSocketRemotePortPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        quint16 port = value.value<quint16>();
        mIODevice->setRemotePort(port);
        return true;
    }
    return false;
}
