#ifndef _QEXTDATCPSOCKETIODEVICE_H
#define _QEXTDATCPSOCKETIODEVICE_H

#include <QObject>
#include <QTcpSocket>

#include <qextDAIODevice.h>

class QExtDATcpSocketIODevicePrivate;
class QEXT_DAVIEW_API QExtDATcpSocketIODevice : public QExtDAIODevice
{
    Q_OBJECT
public:
    explicit QExtDATcpSocketIODevice(QObject *parent = QEXT_NULLPTR);
    ~QExtDATcpSocketIODevice() QEXT_OVERRIDE;

    quint16 remotePort() const;
    void setRemotePort(quint16 port);

    QString remoteIP() const;
    void setRemoteIP(const QString &ip);

    QString ioPath() const QEXT_OVERRIDE;
    QString ioType() const QEXT_OVERRIDE;

    QThread *initDevice(qint64 id) QEXT_OVERRIDE;

    void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE;
    SerializedItems serializeSave() const QEXT_OVERRIDE;

Q_SIGNALS:
    void remotePortChanged(quint16 port);
    void remoteIPChanged(const QString &ip);

protected Q_SLOTS:
    void onTcpSocketStateChanged(QAbstractSocket::SocketState state);
    void onTcpSocketErrorOccurred(QAbstractSocket::SocketError error);

protected:
    bool ioOpen() QEXT_OVERRIDE;
    void ioClose() QEXT_OVERRIDE;

    void initPropertyModel(QExtPropertyModel *propertyModel) QEXT_OVERRIDE;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDATcpSocketIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDATcpSocketIODevice)
};

class QExtDATcpSocketRemoteIPPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDATcpSocketRemoteIPPropertyItem(QExtDATcpSocketIODevice *ioDevice);
    ~QExtDATcpSocketRemoteIPPropertyItem() QEXT_OVERRIDE {}

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
    QPointer<QExtDATcpSocketIODevice> mIODevice;
};

class QExtDATcpSocketRemotePortPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDATcpSocketRemotePortPropertyItem(QExtDATcpSocketIODevice *ioDevice);
    ~QExtDATcpSocketRemotePortPropertyItem() QEXT_OVERRIDE {}

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
    QPointer<QExtDATcpSocketIODevice> mIODevice;
};

#endif // _QEXTDATCPSOCKETIODEVICE_H
