#ifndef _QEXTDAIODEVICEMODEL_H
#define _QEXTDAIODEVICEMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include <qextDAViewGlobal.h>

class QExtDAIODevice;
class QExtDAIODeviceManager;
class QExtDAIODeviceModelPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ColumnEnum
    {
        Column_Name = 0,
        Column_Alias,
        Column_Type,
        Column_State,
        Column_Path
    };
    Q_ENUM(ColumnEnum)
    QEXT_STATIC_CONSTANT_NUMBER(ColumnEnumNum, 5)

    QExtDAIODeviceModel(QExtDAIODeviceManager *ioDeviceManager, QObject *parent = QEXT_NULLPTR);
    ~QExtDAIODeviceModel() QEXT_OVERRIDE;

    // implemented from QAbstractItemModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const QEXT_OVERRIDE;

    bool isEditable() const;
    void setEditable(bool enable);

    QExtDAIODeviceManager *ioDeviceManager() const;

    QExtDAIODevice *ioDevice(int row) const;
    QExtDAIODevice *ioDevice(const QModelIndex &index) const;

    static QString columnEnumName(int type, bool isEng = false);

protected:
    QScopedPointer<QExtDAIODeviceModelPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceModel)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceModel)
};

#endif // _QEXTDAIODEVICEMODEL_H
