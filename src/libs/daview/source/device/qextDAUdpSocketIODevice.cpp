#include <qextDAUdpSocketIODevice.h>
#include <private/qextDAIODevice_p.h>
#include <qextDAIODeviceUtils.h>
#include <qextDAConstants.h>

#include <QDebug>
#include <QSpinBox>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>

class QExtDAUdpSocketIODevicePrivate : public QExtDAIODevicePrivate
{
public:
    explicit QExtDAUdpSocketIODevicePrivate(QExtDAUdpSocketIODevice *q);
    ~QExtDAUdpSocketIODevicePrivate() QEXT_OVERRIDE;

    QPointer<QUdpSocket> mUdpSocket;
    QHostAddress mRemoteAddress;
    quint16 mRemotePort;
    quint16 mLocalPort;
    QString mRemoteIP;

protected:
    Q_DECLARE_PUBLIC(QExtDAUdpSocketIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAUdpSocketIODevicePrivate)
};

QExtDAUdpSocketIODevicePrivate::QExtDAUdpSocketIODevicePrivate(QExtDAUdpSocketIODevice *q)
    : QExtDAIODevicePrivate(q)
{
}

QExtDAUdpSocketIODevicePrivate::~QExtDAUdpSocketIODevicePrivate()
{
}

QExtDAUdpSocketIODevice::QExtDAUdpSocketIODevice(QObject *parent)
    : QExtDAIODevice(new QExtDAUdpSocketIODevicePrivate(this), parent)
{
}

QExtDAUdpSocketIODevice::~QExtDAUdpSocketIODevice()
{
}

quint16 QExtDAUdpSocketIODevice::localPort() const
{
    Q_D(const QExtDAUdpSocketIODevice);
    return d->mLocalPort;
}

void QExtDAUdpSocketIODevice::setLocalPort(quint16 port)
{
    Q_D(QExtDAUdpSocketIODevice);
    if (port != d->mLocalPort)
    {
        d->mLocalPort = port;
        Q_EMIT this->localPortChanged(port);
    }
}

quint16 QExtDAUdpSocketIODevice::remotePort() const
{
    Q_D(const QExtDAUdpSocketIODevice);
    return d->mRemotePort;
}

void QExtDAUdpSocketIODevice::setRemotePort(quint16 port)
{
    Q_D(QExtDAUdpSocketIODevice);
    if (port != d->mRemotePort)
    {
        d->mRemotePort = port;
        Q_EMIT this->remotePortChanged(port);
    }
}

QString QExtDAUdpSocketIODevice::remoteIP() const
{
    Q_D(const QExtDAUdpSocketIODevice);
    return d->mRemoteIP;
}

void QExtDAUdpSocketIODevice::setRemoteIP(const QString &ip)
{
    Q_D(QExtDAUdpSocketIODevice);
    if (ip != d->mRemoteIP)
    {
        d->mRemoteIP = ip;
        d->mRemoteAddress = QHostAddress(ip);
        Q_EMIT this->remoteIPChanged(ip);
    }
}

QString QExtDAUdpSocketIODevice::ioPath() const
{
    Q_D(const QExtDAUdpSocketIODevice);
    return QString("local[%1]remote[%2:%3]").arg(d->mLocalPort).arg(d->mRemoteIP).arg(d->mRemotePort);
}

QString QExtDAUdpSocketIODevice::ioType() const
{
    return QExtDAConstants::IODEVICE_TYPE_UDPSOCKET;
}

QThread *QExtDAUdpSocketIODevice::initDevice(qint64 id)
{
    Q_D(QExtDAUdpSocketIODevice);
    d->initIO(new QUdpSocket);
    d->mUdpSocket = static_cast<QUdpSocket *>(d->mIO.data());
    this->updateIOState(QExtDAIODeviceUtils::socketStateString(QAbstractSocket::UnconnectedState));
    connect(d->mUdpSocket.data(), &QUdpSocket::stateChanged, this, &QExtDAUdpSocketIODevice::onUdpSocketStateChanged);
    connect(d->mUdpSocket.data(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onUdpSocketErrorOccurred(QAbstractSocket::SocketError)));
    return QExtDAIODevice::initDevice(id);
}

void QExtDAUdpSocketIODevice::serializeLoad(const SerializedItems &items)
{
    QExtDAIODevice::serializeLoad(items);
    this->setRemoteIP(items.value(QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_REMOTE_IP, "").toString());
    this->setRemotePort(items.value(QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_REMOTE_PORT, 8089).value<quint16>());
    this->setLocalPort(items.value(QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_LOCAL_PORT, 8089).value<quint16>());
}

QExtSerializable::SerializedItems QExtDAUdpSocketIODevice::serializeSave() const
{
    QExtSerializable::SerializedItems items = QExtDAIODevice::serializeSave();
    items[QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_REMOTE_IP] = this->remoteIP();
    items[QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_REMOTE_PORT] = this->remotePort();
    items[QExtDAConstants::UDPSOCKET_IODEVICE_PROPERTY_LOCAL_PORT] = this->localPort();
    return items;
}

void QExtDAUdpSocketIODevice::onUdpSocketStateChanged(QAbstractSocket::SocketState state)
{
    this->updateIOState(QExtDAIODeviceUtils::socketStateString(state));
    this->updateOpenState(QAbstractSocket::BoundState == state);
}

void QExtDAUdpSocketIODevice::onUdpSocketErrorOccurred(QAbstractSocket::SocketError error)
{
    this->updateIOError(QExtDAIODeviceUtils::socketErrorString(error));
}

bool QExtDAUdpSocketIODevice::ioOpen()
{
    Q_D(QExtDAUdpSocketIODevice);
    return d->mUdpSocket->bind(d->mLocalPort, QAbstractSocket::ShareAddress);
}

void QExtDAUdpSocketIODevice::ioClose()
{
    Q_D(QExtDAUdpSocketIODevice);
    d->mUdpSocket->abort();
    d->mUdpSocket->close();
}

QByteArray QExtDAUdpSocketIODevice::ioRead()
{
    Q_D(QExtDAUdpSocketIODevice);
    return d->mUdpSocket->receiveDatagram().data();
}

qint64 QExtDAUdpSocketIODevice::ioWrite(const char *data, qint64 len)
{
    Q_D(QExtDAUdpSocketIODevice);
    return d->mUdpSocket->writeDatagram(data, len, d->mRemoteAddress, d->mRemotePort);
}

void QExtDAUdpSocketIODevice::initPropertyModel(QExtPropertyModel *propertyModel)
{
    auto rootItem = propertyModel->rootItem();
    QExtDAIODevice::initPropertyModel(propertyModel);
    rootItem->appendChild(new QExtDAUdpSocketRemoteIPPropertyItem(this));
    rootItem->appendChild(new QExtDAUdpSocketRemotePortPropertyItem(this));
    rootItem->appendChild(new QExtDAUdpSocketLocalPortPropertyItem(this));
}

QExtDAUdpSocketRemoteIPPropertyItem::QExtDAUdpSocketRemoteIPPropertyItem(QExtDAUdpSocketIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAUdpSocketIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDAUdpSocketIODevice::remoteIPChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDAUdpSocketRemoteIPPropertyItem::name() const
{
    return tr("RemoteIP");
}

Qt::ItemFlags QExtDAUdpSocketRemoteIPPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDAUdpSocketRemoteIPPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_LineEdit;
}

QWidget *QExtDAUdpSocketRemoteIPPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                 const QModelIndex &index) const
{
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDAUdpSocketRemoteIPPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QExtPropertyModelItem::setEditorData(editor, index);
}

bool QExtDAUdpSocketRemoteIPPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                       const QModelIndex &index) const
{
    return QExtPropertyModelItem::setModelData(editor, model, index);
}

QVariant QExtDAUdpSocketRemoteIPPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->remoteIP();
    }
    return QVariant();
}

bool QExtDAUdpSocketRemoteIPPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        QString ip = value.toString();
        mIODevice->setRemoteIP(ip);
        return true;
    }
    return false;
}

QExtDAUdpSocketRemotePortPropertyItem::QExtDAUdpSocketRemotePortPropertyItem(QExtDAUdpSocketIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAUdpSocketIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDAUdpSocketIODevice::remotePortChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDAUdpSocketRemotePortPropertyItem::name() const
{
    return tr("RemotePort");
}

Qt::ItemFlags QExtDAUdpSocketRemotePortPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDAUdpSocketRemotePortPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_SpinBox;
}

QWidget *QExtDAUdpSocketRemotePortPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                   const QModelIndex &index) const
{
    QSpinBox *widget = qobject_cast<QSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(1024, 65535);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDAUdpSocketRemotePortPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
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

bool QExtDAUdpSocketRemotePortPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
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

QVariant QExtDAUdpSocketRemotePortPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->remotePort();
    }
    return QVariant();
}

bool QExtDAUdpSocketRemotePortPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        quint16 port = value.value<quint16>();
        mIODevice->setRemotePort(port);
        return true;
    }
    return false;
}

QExtDAUdpSocketLocalPortPropertyItem::QExtDAUdpSocketLocalPortPropertyItem(QExtDAUdpSocketIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAUdpSocketIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDAUdpSocketIODevice::localPortChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDAUdpSocketLocalPortPropertyItem::name() const
{
    return tr("LocalPort");
}

Qt::ItemFlags QExtDAUdpSocketLocalPortPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDAUdpSocketLocalPortPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_SpinBox;
}

QWidget *QExtDAUdpSocketLocalPortPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                  const QModelIndex &index) const
{
    QSpinBox *widget = qobject_cast<QSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(1024, 65535);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDAUdpSocketLocalPortPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
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

bool QExtDAUdpSocketLocalPortPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
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

QVariant QExtDAUdpSocketLocalPortPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->localPort();
    }
    return QVariant();
}

bool QExtDAUdpSocketLocalPortPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        quint16 port = value.value<quint16>();
        mIODevice->setLocalPort(port);
        return true;
    }
    return false;
}
