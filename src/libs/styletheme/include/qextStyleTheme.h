#ifndef _QEXTSTYLETHEME_H
#define _QEXTSTYLETHEME_H

#include <qextStyleThemeGlobal.h>

#include <QObject>

class QEXT_STYLETHEM_API QEXTStyleTheme : public QObject
{
    Q_OBJECT
public:
    explicit QEXTStyleTheme(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTStyleTheme();
};

#endif // _QEXTSTYLETHEME_H
