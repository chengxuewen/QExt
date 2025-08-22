#ifndef _QEXTDAIODEVICE_H
#define _QEXTDAIODEVICE_H

#include <QObject>
#include <QPointer>
#include <QIODevice>
#include <QSharedPointer>
#include <QScopedPointer>

#include <qextDAViewGlobal.h>
#include <qextPropertyModel.h>
#include <qextSerializable.h>

class QExtDAIODevicePrivate;
class QEXT_DAVIEW_API QExtDAIODevice : public QObject, public QExtSerializable
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtDAIODevice> SharedPtr;

    explicit QExtDAIODevice(QObject *parent = QEXT_NULLPTR);
    QExtDAIODevice(QExtDAIODevicePrivate *d, QObject *parent = QEXT_NULLPTR);
    ~QExtDAIODevice() QEXT_OVERRIDE;

    int bps() const;
    qint64 id() const;
    QString name() const;
    bool isOpened() const;
    QThread *thread() const;
    QString nameAlias() const;

    qint64 bufferSize() const;
    void setBufferSize(qint64 size);

    bool isBufferEnabled() const;
    void setBufferEnable(bool enable);

    QString alias() const;
    void setAlias(const QString &alias);

    virtual QString ioType() const = 0;

    virtual QIODevice *io() const;
    virtual QString ioPath() const;
    virtual QString ioState() const;
    virtual QString ioError() const;
    virtual QExtPropertyModel *propertyModel();
    virtual QExtPropertyDelegate *propertyDelegate(QObject *parent = QEXT_NULLPTR);

    virtual QThread *initDevice(qint64 id);
    virtual bool clearDevice();

    virtual void open();
    virtual void close();

    SerializedItemsMap serializeSave() const QEXT_OVERRIDE;
    void serializeLoad(const SerializedItemsMap &items) QEXT_OVERRIDE;

    QByteArray readAll();
    bool canReadLine() const;
    qint64 bytesAvailable() const;
    int getChar(bool *ok = QEXT_NULLPTR);
    qint64 read(char *target, qint64 size);
    qint64 peek(char *target, qint64 size);
    qint64 readLine(char *target, qint64 size);
    void write(const char *data, qint64 size);

    static qint64 loadId(const SerializedItemsMap &items);
    static QString loadType(const SerializedItemsMap &items);

    static QString nameFromId(qint64 id);
    static qint64 idFromName(const QString &name);

Q_SIGNALS:
    void readyRead();
    void readyWrite();

    void dataReaded(const QByteArray &data, qint64 timestamp);
    void dataWrited(const QByteArray &data, qint64 timestamp);

    void aliasChanged(const QString &alias);
    void stateChanged(bool opened);
    void rxdBpsChanged(int bps);
    void txdBpsChanged(int bps);

    void ioPathChanged(const QString &path);
    void ioStateChanged(const QString &state);
    void ioErrorChanged(const QString &error);

    void aboutToClose();

protected Q_SLOTS:
    virtual void onIOReadyRead();
    virtual void onIOReadyWrite();
    virtual void onIOWriteFailed();
    virtual void onIOOpenFailed();
    virtual void onIOOpenSuccessed();

    virtual void onStateChanged(bool opened) { Q_UNUSED(opened); }
    virtual void onIOPathChanged(const QString &path) { Q_UNUSED(path); }
    virtual void onIOStateChanged(const QString &state) { Q_UNUSED(state); }
    virtual void onIOErrorChanged(const QString &error) { Q_UNUSED(error); }

protected:
    virtual bool ioOpen();
    virtual void ioClose();

    virtual QByteArray ioRead();
    virtual qint64 ioWrite(const char *data, qint64 len);

    virtual void initPropertyModel(QExtPropertyModel *propertyModel);

    void updateOpenState(bool opened);
    void updateIOPath(const QString &path);
    void updateIOState(const QString &state);
    void updateIOError(const QString &error = "");

    QScopedPointer<QExtDAIODevicePrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODevice)
};

class QExtDAIODeviceStatePropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDAIODeviceStatePropertyItem(QExtDAIODevice *ioDevice);
    ~QExtDAIODeviceStatePropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDAIODevice> mIODevice;
};

class QExtDAIODeviceAliasPropertyItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtDAIODeviceAliasPropertyItem(QExtDAIODevice *ioDevice);
    ~QExtDAIODeviceAliasPropertyItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtDAIODevice> mIODevice;
};

#endif // _QEXTDAIODEVICE_H
