#ifndef _QEXTDASERIALPORTIODEVICE_H
#define _QEXTDASERIALPORTIODEVICE_H

#include <QObject>
#include <QSerialPort>

#include <qextDAIODevice.h>

class QExtDASerialPortIODevicePrivate;
class QEXT_DAVIEW_API QExtDASerialPortIODevice : public QExtDAIODevice
{
    Q_OBJECT
public:
    enum RoleType
    {
        Role_PortName = Qt::UserRole + 1, // portName as QString
        Role_BaudRate,
        Role_DataBits,
        Role_Direction,
        Role_Parity,
        Role_StopBits,
        Role_FlowControl,
        Role_PinoutSignal,
        Role_Error,
    };
    Q_ENUM(RoleType)

    explicit QExtDASerialPortIODevice(QObject *parent = QEXT_NULLPTR);
    ~QExtDASerialPortIODevice() QEXT_OVERRIDE;

    qint32 baudRate() const;
    void setBaudRate(qint32 baudRate);

    QSerialPort::Parity parity() const;
    void setParity(QSerialPort::Parity parity);

    QSerialPort::StopBits stopBits() const;
    void setStopBits(QSerialPort::StopBits stopBits);

    QSerialPort::DataBits dataBits() const;
    void setDataBits(QSerialPort::DataBits dataBits);

    QSerialPort::FlowControl flowControl() const;
    void setFlowControl(QSerialPort::FlowControl flowControl);

    QString portName() const;
    void setPortName(const QString &name);

    bool isDataTerminalReady();
    bool setDataTerminalReady(bool set);

    bool isRequestToSend();
    bool setRequestToSend(bool set);

    QString ioPath() const QEXT_OVERRIDE;
    QString ioType() const QEXT_OVERRIDE;

    QThread *initDevice(qint64 id) QEXT_OVERRIDE;

    void load(const Items &items) QEXT_OVERRIDE;
    Items save() const QEXT_OVERRIDE;

    static QString flowControlEnumString(int type, bool isEng = false);
    static QString baudRateEnumString(int type, bool isEng = false);
    static QString dataBitsEnumString(int type, bool isEng = false);
    static QString stopBitsEnumString(int type, bool isEng = false);
    static QString parityEnumString(int type, bool isEng = false);

Q_SIGNALS:
    void baudRateChanged(qint32 rate);
    void portNameChanged(const QString &name);
    bool parityChanged(QSerialPort::Parity parity);
    bool dataBitsChanged(QSerialPort::DataBits dataBits);
    bool stopBitsChanged(QSerialPort::StopBits stopBits);
    bool flowControlChanged(QSerialPort::FlowControl flowControl);

protected Q_SLOTS:
    void onSerialPortErrorOccurred(QSerialPort::SerialPortError error);

protected:
    bool ioOpen() QEXT_OVERRIDE;
    void ioClose() QEXT_OVERRIDE;

    void initPropertyModel(QExtPropertyModel *propertyModel) QEXT_OVERRIDE;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDASerialPortIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDASerialPortIODevice)
};

class QExtDASerialPortPortNamePropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortPortNamePropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortPortNamePropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};

class QExtDASerialPortBaudRatePropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortBaudRatePropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortBaudRatePropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};

class QExtDASerialPortDataBitsPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortDataBitsPropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortDataBitsPropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};

class QExtDASerialPortStopBitsPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortStopBitsPropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortStopBitsPropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};

class QExtDASerialPortParityPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortParityPropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortParityPropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};


class QExtDASerialPortFlowControlPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDASerialPortFlowControlPropertyItem(QExtDASerialPortIODevice *ioDevice);
    ~QExtDASerialPortFlowControlPropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE;
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    bool setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDASerialPortIODevice> mIODevice;
};

#endif // _QEXTDASERIALPORTIODEVICE_H
