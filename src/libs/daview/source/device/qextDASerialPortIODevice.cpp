#include <qextDASerialPortIODevice.h>
#include <private/qextDAIODevice_p.h>
#include <qextDAIODeviceUtils.h>
#include <qextDAConstants.h>

#include <QDebug>
#include <QListView>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>

class QExtDASerialPortIODevicePrivate : public QExtDAIODevicePrivate
{
public:
    explicit QExtDASerialPortIODevicePrivate(QExtDASerialPortIODevice *q);
    ~QExtDASerialPortIODevicePrivate() QEXT_OVERRIDE;

    QPointer<QSerialPort> mSerialPort;

private:
    Q_DECLARE_PUBLIC(QExtDASerialPortIODevice)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDASerialPortIODevicePrivate)
};

QExtDASerialPortIODevicePrivate::QExtDASerialPortIODevicePrivate(QExtDASerialPortIODevice *q)
    : QExtDAIODevicePrivate(q)
{
}

QExtDASerialPortIODevicePrivate::~QExtDASerialPortIODevicePrivate()
{
}

QExtDASerialPortIODevice::QExtDASerialPortIODevice(QObject *parent)
    : QExtDAIODevice(new QExtDASerialPortIODevicePrivate(this), parent)
{
}

QExtDASerialPortIODevice::~QExtDASerialPortIODevice()
{
}

qint32 QExtDASerialPortIODevice::baudRate() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->baudRate(QSerialPort::AllDirections);
}

void QExtDASerialPortIODevice::setBaudRate(qint32 baudRate)
{
    Q_D(QExtDASerialPortIODevice);
    if (baudRate != d->mSerialPort->baudRate(QSerialPort::AllDirections))
    {
        d->mSerialPort->setBaudRate(baudRate, QSerialPort::AllDirections);
        Q_EMIT this->baudRateChanged(baudRate);
    }
}

QSerialPort::Parity QExtDASerialPortIODevice::parity() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->parity();
}

void QExtDASerialPortIODevice::setParity(QSerialPort::Parity parity)
{
    Q_D(QExtDASerialPortIODevice);
    if (parity != d->mSerialPort->parity())
    {
        d->mSerialPort->setParity(parity);
        Q_EMIT this->parityChanged(parity);
    }
}

QSerialPort::StopBits QExtDASerialPortIODevice::stopBits() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->stopBits();
}

void QExtDASerialPortIODevice::setStopBits(QSerialPort::StopBits stopBits)
{
    Q_D(QExtDASerialPortIODevice);
    if (stopBits != d->mSerialPort->stopBits())
    {
        d->mSerialPort->setStopBits(stopBits);
        Q_EMIT this->stopBitsChanged(stopBits);
    }
}

QSerialPort::DataBits QExtDASerialPortIODevice::dataBits() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->dataBits();
}

void QExtDASerialPortIODevice::setDataBits(QSerialPort::DataBits dataBits)
{
    Q_D(QExtDASerialPortIODevice);
    if (dataBits != d->mSerialPort->dataBits())
    {
        d->mSerialPort->setDataBits(dataBits);
        Q_EMIT this->dataBitsChanged(dataBits);
    }
}

QSerialPort::FlowControl QExtDASerialPortIODevice::flowControl() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->flowControl();
}

void QExtDASerialPortIODevice::setFlowControl(QSerialPort::FlowControl flowControl)
{
    Q_D(QExtDASerialPortIODevice);
    if (flowControl != d->mSerialPort->flowControl())
    {
        d->mSerialPort->setFlowControl(flowControl);
        Q_EMIT this->flowControlChanged(flowControl);
    }
}

QString QExtDASerialPortIODevice::portName() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->portName();
}

void QExtDASerialPortIODevice::setPortName(const QString &name)
{
    Q_D(QExtDASerialPortIODevice);
    if (name != d->mSerialPort->portName())
    {
        d->mSerialPort->setPortName(name);
        Q_EMIT this->ioPathChanged(name);
        Q_EMIT this->portNameChanged(name);
    }
}

bool QExtDASerialPortIODevice::isDataTerminalReady()
{
    Q_D(QExtDASerialPortIODevice);
    return d->mSerialPort->isDataTerminalReady();
}

bool QExtDASerialPortIODevice::setDataTerminalReady(bool set)
{
    Q_D(QExtDASerialPortIODevice);
    return d->mSerialPort->setDataTerminalReady(set);
}

bool QExtDASerialPortIODevice::isRequestToSend()
{
    Q_D(QExtDASerialPortIODevice);
    return d->mSerialPort->isRequestToSend();
}

bool QExtDASerialPortIODevice::setRequestToSend(bool set)
{
    Q_D(QExtDASerialPortIODevice);
    return d->mSerialPort->setRequestToSend(set);
}

QString QExtDASerialPortIODevice::ioPath() const
{
    Q_D(const QExtDASerialPortIODevice);
    return d->mSerialPort->portName();
}

QString QExtDASerialPortIODevice::ioType() const
{
    return QExtDAConstants::IODEVICE_TYPE_SERIALPORT;
}

QThread *QExtDASerialPortIODevice::initDevice(qint64 id)
{
    Q_D(QExtDASerialPortIODevice);
    d->initIO(new QSerialPort);
    d->mSerialPort = static_cast<QSerialPort *>(d->mIO.data());
    d->mSerialPort->setBaudRate(QSerialPort::Baud9600);
    d->mSerialPort->setDataBits(QSerialPort::Data8);
    d->mSerialPort->setStopBits(QSerialPort::OneStop);
    d->mSerialPort->setParity(QSerialPort::NoParity);
    this->updateIOState(tr("Closed"));
    connect(d->mSerialPort.data(), &QSerialPort::errorOccurred,
            this, &QExtDASerialPortIODevice::onSerialPortErrorOccurred);
    return QExtDAIODevice::initDevice(id);
}

void QExtDASerialPortIODevice::serializeLoad(const SerializedItemsMap &items)
{
    QExtDAIODevice::serializeLoad(items);
    this->setParity(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_PARITY,
                                QSerialPort::NoParity).value<QSerialPort::Parity>());
    this->setBaudRate(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_BAUD_RATE,
                                  QSerialPort::Baud9600).value<QSerialPort::BaudRate>());
    this->setStopBits(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_STOP_BITS,
                                  QSerialPort::OneStop).value<QSerialPort::StopBits>());
    this->setDataBits(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_DATA_BITS,
                                  QSerialPort::Data8).value<QSerialPort::DataBits>());
    this->setPortName(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_PORT_NAME,
                                  "").toString());
    this->setFlowControl(items.value(QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_FLOW_CONTROL,
                                     QSerialPort::NoFlowControl).value<QSerialPort::FlowControl>());
}

QExtSerializable::SerializedItemsMap QExtDASerialPortIODevice::serializeSave() const
{
    QExtSerializable::SerializedItemsMap items = QExtDAIODevice::serializeSave();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_PARITY] = this->parity();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_BAUD_RATE] = this->baudRate();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_STOP_BITS] = this->stopBits();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_DATA_BITS] = this->dataBits();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_PORT_NAME] = this->portName();
    items[QExtDAConstants::SERIALPORT_IODEVICE_PROPERTY_FLOW_CONTROL] = this->flowControl();
    return items;
}

QString QExtDASerialPortIODevice::flowControlEnumString(int type, bool isEng)
{
    switch (type)
    {
    case QSerialPort::NoFlowControl:
        return isEng ? "None" : tr("None");
    case QSerialPort::HardwareControl:
        return isEng ? "RTS/CTS" : tr("RTS/CTS");
    case QSerialPort::SoftwareControl:
        return isEng ? "XON/XOFF" : tr("XON/XOFF");
    default:
        break;
    }
    return "Unknown";
}

QString QExtDASerialPortIODevice::baudRateEnumString(int type, bool isEng)
{
    const QString number = QString::number(type);
    return type > 0 ? (isEng ? number : tr(number.toLatin1().data())) : "Unknown";
}

QString QExtDASerialPortIODevice::dataBitsEnumString(int type, bool isEng)
{
    const QString number = QString::number(type);
    return type > 0 ? (isEng ? number : tr(number.toLatin1().data())) : "Unknown";
}

QString QExtDASerialPortIODevice::stopBitsEnumString(int type, bool isEng)
{
    switch (type)
    {
    case QSerialPort::OneStop:
        return isEng ? "1" : tr("1");
    case QSerialPort::OneAndHalfStop:
        return isEng ? "1.5" : tr("1.5");
    case QSerialPort::TwoStop:
        return isEng ? "2" : tr("2");
    default:
        break;
    }
    return "Unknown";
}

QString QExtDASerialPortIODevice::parityEnumString(int type, bool isEng)
{
    switch (type)
    {
    case QSerialPort::NoParity:
        return isEng ? "None" : tr("None");
    case QSerialPort::EvenParity:
        return isEng ? "Even" : tr("Even");
    case QSerialPort::OddParity:
        return isEng ? "Odd" : tr("Odd");
    case QSerialPort::SpaceParity:
        return isEng ? "Space" : tr("Space");
    case QSerialPort::MarkParity:
        return isEng ? "Mark" : tr("Mark");
    default:
        break;
    }
    return "Unknown";
}

void QExtDASerialPortIODevice::onSerialPortErrorOccurred(QSerialPort::SerialPortError error)
{
    this->updateIOError(QExtDAIODeviceUtils::serialPortErrorString(error));
}

bool QExtDASerialPortIODevice::ioOpen()
{
    Q_D(QExtDASerialPortIODevice);
    this->updateOpenState(d->mSerialPort->open(QIODevice::ReadWrite));
    this->updateIOState(d->mIsOpened.loadAcquire() ? tr("Opened") : tr("Closed"));
    return d->mIsOpened.loadAcquire();
}

void QExtDASerialPortIODevice::ioClose()
{
    Q_D(QExtDASerialPortIODevice);
    d->mSerialPort->close();
    this->updateOpenState(false);
    this->updateIOState(tr("Closed"));
}

void QExtDASerialPortIODevice::initPropertyModel(QExtPropertyModel *propertyModel)
{
    auto rootItem = propertyModel->rootItem();
    QExtDAIODevice::initPropertyModel(propertyModel);
    rootItem->appendChild(new QExtDASerialPortPortNamePropertyItem(this));
    rootItem->appendChild(new QExtDASerialPortBaudRatePropertyItem(this));
    rootItem->appendChild(new QExtDASerialPortParityPropertyItem(this));
    rootItem->appendChild(new QExtDASerialPortStopBitsPropertyItem(this));
    rootItem->appendChild(new QExtDASerialPortDataBitsPropertyItem(this));
    rootItem->appendChild(new QExtDASerialPortFlowControlPropertyItem(this));
}

QExtDASerialPortPortNamePropertyItem::QExtDASerialPortPortNamePropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::portNameChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortPortNamePropertyItem::name() const
{
    return tr("PortName");
}

Qt::ItemFlags QExtDASerialPortPortNamePropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortPortNamePropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortPortNamePropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                  const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setEditable(true);
        widget->setView(new QListView(widget));
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        for (auto &portInfo : availablePorts)
        {
            widget->addItem(portInfo.portName());
        }
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortPortNamePropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString text = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(text);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortPortNamePropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                        const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString data = widget->currentText();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortPortNamePropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->portName();
    }
    return QVariant();
}

bool QExtDASerialPortPortNamePropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        QString data = value.toString();
        mIODevice->setPortName(data);
        return true;
    }
    return false;
}

QExtDASerialPortBaudRatePropertyItem::QExtDASerialPortBaudRatePropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::baudRateChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortBaudRatePropertyItem::name() const
{
    return tr("BaudRate");
}

Qt::ItemFlags QExtDASerialPortBaudRatePropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortBaudRatePropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortBaudRatePropertyItem::initEditorProperty(QWidget *editor,
                                                                  const QStyleOptionViewItem &option,
                                                                  const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setView(new QListView(widget));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud1200));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud2400));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud4800));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud9600));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud19200));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud38400));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud57600));
        widget->addItem(QExtDASerialPortIODevice::baudRateEnumString(QSerialPort::Baud115200));
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortBaudRatePropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString value = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(value);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortBaudRatePropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                        const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            qint32 rate = widget->currentText().toInt();
            model->setData(index, rate, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortBaudRatePropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return QExtDASerialPortIODevice::baudRateEnumString(mIODevice->baudRate());
    }
    return QVariant();
}

bool QExtDASerialPortBaudRatePropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        qint32 baudRate = value.toInt();
        mIODevice->setBaudRate(baudRate);
        return true;
    }
    return false;
}

QExtDASerialPortParityPropertyItem::QExtDASerialPortParityPropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::parityChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortParityPropertyItem::name() const
{
    return tr("Parity");
}

Qt::ItemFlags QExtDASerialPortParityPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortParityPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortParityPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setView(new QListView(widget));
        widget->addItem(QExtDASerialPortIODevice::parityEnumString(QSerialPort::NoParity), QSerialPort::NoParity);
        widget->addItem(QExtDASerialPortIODevice::parityEnumString(QSerialPort::OddParity), QSerialPort::OddParity);
        widget->addItem(QExtDASerialPortIODevice::parityEnumString(QSerialPort::EvenParity), QSerialPort::EvenParity);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortParityPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString text = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(text);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortParityPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                      const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            qint32 data = widget->currentData().toInt();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortParityPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return QExtDASerialPortIODevice::parityEnumString(mIODevice->parity());
    }
    return QVariant();
}

bool QExtDASerialPortParityPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        qint32 data = value.toInt();
        mIODevice->setParity(static_cast<QSerialPort::Parity>(data));
        return true;
    }
    return false;
}

QExtDASerialPortStopBitsPropertyItem::QExtDASerialPortStopBitsPropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::stopBitsChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortStopBitsPropertyItem::name() const
{
    return tr("StopBits");
}

Qt::ItemFlags QExtDASerialPortStopBitsPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortStopBitsPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortStopBitsPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                  const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setView(new QListView(widget));
        widget->addItem(QExtDASerialPortIODevice::stopBitsEnumString(QSerialPort::OneStop), QSerialPort::OneStop);
        widget->addItem(QExtDASerialPortIODevice::stopBitsEnumString(QSerialPort::OneAndHalfStop), QSerialPort::OneAndHalfStop);
        widget->addItem(QExtDASerialPortIODevice::stopBitsEnumString(QSerialPort::TwoStop), QSerialPort::TwoStop);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortStopBitsPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString text = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(text);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortStopBitsPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                        const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            qint32 data = widget->currentData().toInt();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortStopBitsPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return QExtDASerialPortIODevice::stopBitsEnumString(mIODevice->stopBits());
    }
    return QVariant();
}

bool QExtDASerialPortStopBitsPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        qint32 data = value.toInt();
        mIODevice->setStopBits(static_cast<QSerialPort::StopBits>(data));
        return true;
    }
    return false;
}

QExtDASerialPortDataBitsPropertyItem::QExtDASerialPortDataBitsPropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::dataBitsChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortDataBitsPropertyItem::name() const
{
    return tr("DataBits");
}

Qt::ItemFlags QExtDASerialPortDataBitsPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortDataBitsPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortDataBitsPropertyItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                                  const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setView(new QListView(widget));
        widget->addItem(QExtDASerialPortIODevice::dataBitsEnumString(QSerialPort::Data5), QSerialPort::Data5);
        widget->addItem(QExtDASerialPortIODevice::dataBitsEnumString(QSerialPort::Data6), QSerialPort::Data6);
        widget->addItem(QExtDASerialPortIODevice::dataBitsEnumString(QSerialPort::Data7), QSerialPort::Data7);
        widget->addItem(QExtDASerialPortIODevice::dataBitsEnumString(QSerialPort::Data8), QSerialPort::Data8);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortDataBitsPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString text = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(text);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortDataBitsPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                        const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            qint32 data = widget->currentData().toInt();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortDataBitsPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return QExtDASerialPortIODevice::dataBitsEnumString(mIODevice->dataBits());
    }
    return QVariant();
}

bool QExtDASerialPortDataBitsPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        qint32 data = value.toInt();
        mIODevice->setDataBits(static_cast<QSerialPort::DataBits>(data));
        return true;
    }
    return false;
}

QExtDASerialPortFlowControlPropertyItem::QExtDASerialPortFlowControlPropertyItem(QExtDASerialPortIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDASerialPortIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
    connect(ioDevice, &QExtDASerialPortIODevice::flowControlChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDASerialPortFlowControlPropertyItem::name() const
{
    return tr("FlowControl");
}

Qt::ItemFlags QExtDASerialPortFlowControlPropertyItem::flags() const
{
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (!mIODevice->isOpened()) { flags = flags | Qt::ItemIsEnabled; }
    return flags;
}

QExtPropertyModelItem::EditorEnum QExtDASerialPortFlowControlPropertyItem::editorType() const
{
    return QExtPropertyModelItem::Editor_ComboBox;
}

QWidget *QExtDASerialPortFlowControlPropertyItem::initEditorProperty(QWidget *editor,
                                                                     const QStyleOptionViewItem &option,
                                                                     const QModelIndex &index) const
{
    QComboBox *widget = qobject_cast<QComboBox *>(editor);
    if (widget)
    {
        widget->setView(new QListView(widget));
        widget->addItem(QExtDASerialPortIODevice::flowControlEnumString(QSerialPort::NoFlowControl),
                        QSerialPort::NoFlowControl);
        widget->addItem(QExtDASerialPortIODevice::flowControlEnumString(QSerialPort::HardwareControl),
                        QSerialPort::HardwareControl);
        widget->addItem(QExtDASerialPortIODevice::flowControlEnumString(QSerialPort::SoftwareControl),
                        QSerialPort::SoftwareControl);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

bool QExtDASerialPortFlowControlPropertyItem::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            QString text = index.model()->data(index, Qt::EditRole).toString();
            widget->setCurrentText(text);
            return true;
        }
    }
    return false;
}

bool QExtDASerialPortFlowControlPropertyItem::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                           const QModelIndex &index) const
{
    if (index.isValid())
    {
        QComboBox *widget = qobject_cast<QComboBox *>(editor);
        if (widget)
        {
            qint32 data = widget->currentData().toInt();
            model->setData(index, data, Qt::EditRole);
            return true;
        }
    }
    return false;
}

QVariant QExtDASerialPortFlowControlPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return QExtDASerialPortIODevice::flowControlEnumString(mIODevice->flowControl());
    }
    return QVariant();
}

bool QExtDASerialPortFlowControlPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        qint32 data = value.toInt();
        mIODevice->setFlowControl(static_cast<QSerialPort::FlowControl>(data));
        return true;
    }
    return false;
}
