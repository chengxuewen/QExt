#ifndef QEXTTCPSERVERTRANSFERINFOMODEL_H
#define QEXTTCPSERVERTRANSFERINFOMODEL_H

#include <qextobject.h>

#include <qextnetworkglobal.h>

#include <QAbstractItemModel>

class QEXTTcpServerTransferInfoModelPrivate;
class QEXT_NETWORK_API QEXTTcpServerTransferInfoModel : public QAbstractItemModel, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTTcpServerTransferInfoModel(QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpServerTransferInfoModel();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpServerTransferInfoModel)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerTransferInfoModel)
};

#endif // QEXTTCPSERVERTRANSFERINFOMODEL_H
