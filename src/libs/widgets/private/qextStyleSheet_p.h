#ifndef _QEXTSTYLESHEET_P_H
#define _QEXTSTYLESHEET_P_H

#include <qextWidgetGlobal.h>

class QEXTStyleSheet;
class QEXT_WIDGETS_API QEXTStyleSheetPrivate
{
public:
    explicit QEXTStyleSheetPrivate(QEXTStyleSheet *q);
    virtual ~QEXTStyleSheetPrivate();

    QEXTStyleSheet * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTStyleSheetPrivate)
    Q_DECLARE_PUBLIC(QEXTStyleSheet)
};

#endif // _QEXTSTYLESHEET_P_H
