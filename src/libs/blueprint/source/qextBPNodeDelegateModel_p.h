#ifndef _QEXTBPNODEDELEGATEMODEL_P_H
#define _QEXTBPNODEDELEGATEMODEL_P_H

#include <qextBPNodeDelegateModel.h>

class QExtBPNodeDelegateModelPrivate
{
public:
    explicit QExtBPNodeDelegateModelPrivate(QExtBPNodeDelegateModel *q);
    virtual ~QExtBPNodeDelegateModelPrivate();

    QExtBPNodeDelegateModel * const q_ptr;

    QExtBPNodeStyle m_nodeStyle;

private:
    QEXT_DECLARE_PUBLIC(QExtBPNodeDelegateModel)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPNodeDelegateModelPrivate)
};

#endif // _QEXTBPNODEDELEGATEMODEL_P_H
