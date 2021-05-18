#ifndef QEXTTCPSERVERTRANSFERINFOMODEL_P_H
#define QEXTTCPSERVERTRANSFERINFOMODEL_P_H

#include <qextobject_p.h>



class QEXTTcpServerTransferInfoModel;
class QEXTTcpServerTransferInfoModelPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpServerTransferInfoModelPrivate(QEXTTcpServerTransferInfoModel *qq);
    ~QEXTTcpServerTransferInfoModelPrivate();

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpServerTransferInfoModel)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerTransferInfoModelPrivate)
};



#endif // QEXTTCPSERVERTRANSFERINFOMODEL_P_H
