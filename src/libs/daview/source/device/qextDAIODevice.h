#ifndef _QEXTDAIODEVICE_H
#define _QEXTDAIODEVICE_H

#include <QObject>
#include <QPointer>
#include <QIODevice>

#include <qextDAViewGlobal.h>
#include <qextPropertyModel.h>

class QExtDAIODevicePrivate;
class QEXT_DAVIEW_API QExtDAIODevice : public QObject
{
    Q_OBJECT
public:
    explicit QExtDAIODevice(QObject *parent = QEXT_NULLPTR);
    QExtDAIODevice(QExtDAIODevicePrivate *d, QObject *parent = QEXT_NULLPTR);
    ~QExtDAIODevice() QEXT_OVERRIDE;

    quint64 id() const;
    QString name() const;
    QString nameAlias() const;

    QString alias() const;
    void setAlias(const QString &alias);

    virtual QString path() const = 0;
    virtual QString deviceTypeName() const = 0;

    virtual bool isOpened() const;
    virtual QIODevice *io() const;
    virtual QString stateString() const;
    virtual QString errorString() const;
    virtual QExtPropertyModel *propertyModel();
    virtual QExtPropertyDelegate *propertyDelegate(QObject *parent = QEXT_NULLPTR);

    virtual QThread *initDevice(quint64 id);

    virtual void close();
    virtual void open(QIODevice::OpenMode mode = QIODevice::ReadWrite);
    void write(const char *data, qint64 size);

Q_SIGNALS:
    void readyWrite();
    void dataReaded(const QByteArray &data);

    void pathChanged(const QString &path);
    void aliasChanged(const QString &alias);

    void aboutToClose();
    void stateChanged(bool opened);

    void bpsChanged(double bps);

protected Q_SLOTS:
    virtual void onIOReadyRead();
    virtual void onIOReadyWrite();
    virtual void onIOWriteFailed();
    virtual void onIOOpenFailed();
    virtual void onIOOpenSuccessed();

    virtual void initPropertyModel(QExtPropertyModel *propertyModel);

protected:
    QScopedPointer<QExtDAIODevicePrivate> dd_ptr;

private:
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
