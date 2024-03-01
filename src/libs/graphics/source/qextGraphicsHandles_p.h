#ifndef _QEXTGRAPHICSITEMHANDLE_P_H
#define _QEXTGRAPHICSITEMHANDLE_P_H

#include <qextGraphicsItemHandle.h>

class QExtGraphicsSizeHandlePrivate
{
    QExtGraphicsSizeHandle * const q_ptr;
public:
    explicit QExtGraphicsSizeHandlePrivate(QExtGraphicsSizeHandle *q, int dir);
    virtual ~QExtGraphicsSizeHandlePrivate();

    SelectionHandleState m_state;
    QColor m_borderColor;
    bool m_controlPoint;
    const int m_dir;

private:
    QEXT_DECL_PUBLIC(QExtGraphicsSizeHandle)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsSizeHandlePrivate)
};

#endif // _QEXTGRAPHICSITEMHANDLE_P_H
