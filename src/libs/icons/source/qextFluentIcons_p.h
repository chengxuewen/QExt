#ifndef _QEXTFLUENTICONS_P_H
#define _QEXTFLUENTICONS_P_H

#include <qextFluentIcons.h>

class QExtFluentIconsPrivate
{
    QExtFluentIcons * const q_ptr;
    QEXT_DECL_PUBLIC(QExtFluentIcons)
    QEXT_DISABLE_COPY_MOVE(QExtFluentIconsPrivate)
public:
    explicit QExtFluentIconsPrivate(QExtFluentIcons *q);
    virtual ~QExtFluentIconsPrivate();

};

#endif // _QEXTFLUENTICONS_P_H
