#include <qexttcpservertransferinfomodel.h>
#include <qexttcpservertransferinfomodel_p.h>

#include <QDebug>



QEXTTcpServerTransferInfoModelPrivate::QEXTTcpServerTransferInfoModelPrivate(QEXTTcpServerTransferInfoModel *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpServerTransferInfoModelPrivate::~QEXTTcpServerTransferInfoModelPrivate()
{

}



QEXTTcpServerTransferInfoModel::QEXTTcpServerTransferInfoModel(QObject *parent)
    : QAbstractItemModel(parent), QEXTObject(*(new QEXTTcpServerTransferInfoModelPrivate(this)))
{

}

QEXTTcpServerTransferInfoModel::~QEXTTcpServerTransferInfoModel()
{

}
