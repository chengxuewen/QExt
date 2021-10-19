#ifndef _QEXTSTYLESHEETPALETTE_P_H
#define _QEXTSTYLESHEETPALETTE_P_H

#include <qextStyleSheetGlobal.h>

class QEXTStyleSheetPalette;
class QEXT_STYLESHEET_API QEXTStyleSheetPalettePrivate
{
public:
    explicit QEXTStyleSheetPalettePrivate(QEXTStyleSheetPalette *q);
    virtual ~QEXTStyleSheetPalettePrivate();

    QEXTStyleSheetPalette * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTStyleSheetPalettePrivate)
    Q_DECLARE_PUBLIC(QEXTStyleSheetPalette)
};


#endif // _QEXTSTYLESHEETPALETTE_P_H
