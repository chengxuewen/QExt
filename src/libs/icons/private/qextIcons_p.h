#ifndef _QEXTICONS_P_H
#define _QEXTICONS_P_H

#include <qextIconsGlobal.h>

class QEXTIcons;
class QEXT_ICONS_API QEXTIconsPrivate
{
public:
    explicit QEXTIconsPrivate(QEXTIcons *q);
    virtual ~QEXTIconsPrivate();

    QEXTIcons * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTIconsPrivate)
    Q_DECLARE_PUBLIC(QEXTIcons)
};

#endif // _QEXTICONS_P_H
