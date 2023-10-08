#ifndef _QEXTSTYLESHEET_P_H
#define _QEXTSTYLESHEET_P_H

#include <qextStyleSheet.h>

class QEXTStyleSheet;
class QEXT_WIDGETS_API QEXTStyleSheetPrivate
{
public:
    explicit QEXTStyleSheetPrivate(QEXTStyleSheet *q);
    virtual ~QEXTStyleSheetPrivate();

    QEXTStyleSheet * const q_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleSheetPrivate)
    QEXT_DECL_PUBLIC(QEXTStyleSheet)
};

#endif // _QEXTSTYLESHEET_P_H
