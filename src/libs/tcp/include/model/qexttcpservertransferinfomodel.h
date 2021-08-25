#ifndef QEXTTCPSERVERTRANSFERINFOMODEL_H
#define QEXTTCPSERVERTRANSFERINFOMODEL_H

#include <qextobject.h>

#include <qexttcpglobal.h>

#include <QAbstractItemModel>



class QEXTTcpServerTransferInfoModelPrivate;
class QEXT_TCP_API QEXTTcpServerTransferInfoModel : public QAbstractItemModel, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTTcpServerTransferInfoModel(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTTcpServerTransferInfoModel();

private:
    QEXT_DECL_PRIVATE(QEXTTcpServerTransferInfoModel)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerTransferInfoModel)
};



#endif // QEXTTCPSERVERTRANSFERINFOMODEL_H
