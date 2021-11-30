#ifndef _QEXTSTYLESHEET_H
#define _QEXTSTYLESHEET_H

#include <qextGlobal.h>
#include <qextWidgetGlobal.h>

#include <QObject>

class QEXTStyleSheetPrivate;
class QEXT_WIDGETS_API QEXTStyleSheet : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTStyleSheet)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTStyleSheet)

public:
    explicit QEXTStyleSheet(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTStyleSheet();


protected:
    QScopedPointer<QEXTStyleSheetPrivate> dd_ptr;
};

#endif // _QEXTSTYLESHEET_H
