#ifndef QEXTSTYLESHEET_H
#define QEXTSTYLESHEET_H

#include <qextGlobal.h>
#include <qextStyleSheetGlobal.h>

#include <QObject>

class QEXTStyleSheetPrivate;
class QEXT_STYLESHEET_API QEXTStyleSheet : public QObject
{
    Q_OBJECT
public:
    explicit QEXTStyleSheet(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTStyleSheet();


protected:
    QScopedPointer<QEXTStyleSheetPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTStyleSheet)
    Q_DECLARE_PRIVATE(QEXTStyleSheet)
};

#endif // QEXTSTYLESHEET_H
