#include <private/qextStyleSheet_p.h>

QEXTStyleSheetPrivate::QEXTStyleSheetPrivate(QEXTStyleSheet *q)
    : q_ptr(q)
{

}

QEXTStyleSheetPrivate::~QEXTStyleSheetPrivate()
{

}



QEXTStyleSheet::QEXTStyleSheet(QObject *parent)
    : QObject(parent), dd_ptr(new QEXTStyleSheetPrivate(this))
{

}

QEXTStyleSheet::~QEXTStyleSheet()
{

}
