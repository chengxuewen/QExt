#ifndef _QEXTSTYLESHEET_P_H
#define _QEXTSTYLESHEET_P_H

#include <qextWidgetGlobal.h>

class QEXTStyleSheet;
class QEXT_WIDGETS_API QEXTStyleSheetPrivate
{
    Q_DISABLE_COPY(QEXTStyleSheetPrivate)
    Q_DECLARE_PUBLIC(QEXTStyleSheet)
public:
    explicit QEXTStyleSheetPrivate(QEXTStyleSheet *q);
    virtual ~QEXTStyleSheetPrivate();

    QEXTStyleSheet * const q_ptr;
};

#endif // _QEXTSTYLESHEET_P_H
