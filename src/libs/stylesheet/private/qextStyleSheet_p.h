#ifndef QEXTSTYLESHEET_P_H
#define QEXTSTYLESHEET_P_H

#include <qextStyleSheetGlobal.h>

class QEXTStyleSheet;
class QEXT_STYLESHEET_API QEXTStyleSheetPrivate
{
public:
    explicit QEXTStyleSheetPrivate(QEXTStyleSheet *q);
    virtual ~QEXTStyleSheetPrivate();

    QEXTStyleSheet * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTStyleSheetPrivate)
    Q_DECLARE_PUBLIC(QEXTStyleSheet)
};

#endif // QEXTSTYLESHEET_P_H
