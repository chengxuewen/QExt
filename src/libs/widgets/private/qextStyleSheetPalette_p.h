#ifndef _QEXTSTYLESHEETPALETTE_P_H
#define _QEXTSTYLESHEETPALETTE_P_H

#include <qextWidgetGlobal.h>

class QEXTStyleSheetPalette;
class QEXT_WIDGETS_API QEXTStyleSheetPalettePrivate
{
    Q_DISABLE_COPY(QEXTStyleSheetPalettePrivate)
    Q_DECLARE_PUBLIC(QEXTStyleSheetPalette)
public:
    explicit QEXTStyleSheetPalettePrivate(QEXTStyleSheetPalette *q);
    virtual ~QEXTStyleSheetPalettePrivate();

    QEXTStyleSheetPalette * const q_ptr;
};


#endif // _QEXTSTYLESHEETPALETTE_P_H
