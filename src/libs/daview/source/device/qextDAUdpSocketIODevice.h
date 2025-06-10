#ifndef _QEXTDAUDPSOCKETIODEVICE_H
#define _QEXTDAUDPSOCKETIODEVICE_H

#include <qextDAIODevice.h>

#include <QObject>
#include <QUdpSocket>

class QExtDAUdpSocketIODevicePrivate;
class QEXT_DAVIEW_API QExtDAUdpSocketIODevice : public QExtDAIODevice
{
    Q_OBJECT
public:
    explicit QExtDAUdpSocketIODevice(QObject *parent = QEXT_NULLPTR);
    ~QExtDAUdpSocketIODevice() QEXT_OVERRIDE;

    quint16 localPort() const;
    void setLocalPort(quint16 port);

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
    void localPortChanged(quint16 port);
    void remotePortChanged(quint16 port);
    void remoteIPChanged(const QString &ip);

protected Q_SLOTS:
    void onUdpSocketStateChanged(QAbstractSocket::SocketState state);
    void onUdpSocketErrorOccurred(QAbstractSocket::SocketError error);

protected:
    bool ioOpen() QEXT_OVERRIDE;
    void ioClose() QEXT_OVERRIDE;

    QByteArray ioRead() QEXT_OVERRIDE;
    qint64 ioWrite(const char *data, qint64 len) QEXT_OVERRIDE;

    void initPropertyModel(QExtPropertyModel *propertyModel) QEXT_OVERRIDE;    

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAUdpSocketIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAUdpSocketIODevice)
};

class QExtDAUdpSocketRemoteIPPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDAUdpSocketRemoteIPPropertyItem(QExtDAUdpSocketIODevice *ioDevice);
    ~QExtDAUdpSocketRemoteIPPropertyItem() QEXT_OVERRIDE {}

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
    QPointer<QExtDAUdpSocketIODevice> mIODevice;
};

class QExtDAUdpSocketRemotePortPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDAUdpSocketRemotePortPropertyItem(QExtDAUdpSocketIODevice *ioDevice);
    ~QExtDAUdpSocketRemotePortPropertyItem() QEXT_OVERRIDE {}

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
    QPointer<QExtDAUdpSocketIODevice> mIODevice;
};

class QExtDAUdpSocketLocalPortPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDAUdpSocketLocalPortPropertyItem(QExtDAUdpSocketIODevice *ioDevice);
    ~QExtDAUdpSocketLocalPortPropertyItem() QEXT_OVERRIDE {}

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
    QPointer<QExtDAUdpSocketIODevice> mIODevice;
};

#endif // _QEXTDAUDPSOCKETIODEVICE_H
