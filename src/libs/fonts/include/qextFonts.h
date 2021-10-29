#ifndef _QEXTFONTS_H
#define _QEXTFONTS_H

#include <qextFontsGlobal.h>

#include <QObject>

class QEXT_FONTS_API QEXTFonts : public QObject
{
    Q_OBJECT
public:
    explicit QEXTFonts(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTFonts();
};

#endif // _QEXTFONTS_H
