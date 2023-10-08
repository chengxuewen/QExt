#ifndef _QEXTSTYLESHEET_H
#define _QEXTSTYLESHEET_H

#include <qextWidgetGlobal.h>

#include <QObject>

class QEXTStyleSheetPrivate;
class QEXT_WIDGETS_API QEXTStyleSheet : public QObject
{
    Q_OBJECT

public:
    explicit QEXTStyleSheet(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTStyleSheet();


protected:
    QScopedPointer<QEXTStyleSheetPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleSheet)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTStyleSheet)
};

#endif // _QEXTSTYLESHEET_H
