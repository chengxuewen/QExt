#ifndef _QEXTFLUENTICONS_P_H
#define _QEXTFLUENTICONS_P_H

#include <qextFluentIcons.h>

class QEXTFluentIconsPrivate
{
    QEXTFluentIcons * const q_ptr;
    QEXT_DECL_PUBLIC(QEXTFluentIcons)
    QEXT_DISABLE_COPY_MOVE(QEXTFluentIconsPrivate)
public:
    explicit QEXTFluentIconsPrivate(QEXTFluentIcons *q);
    virtual ~QEXTFluentIconsPrivate();

};

#endif // _QEXTFLUENTICONS_P_H
