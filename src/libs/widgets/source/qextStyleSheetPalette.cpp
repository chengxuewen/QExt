#include <private/qextStyleSheetPalette_p.h>


QEXTStyleSheetPalettePrivate::QEXTStyleSheetPalettePrivate(QEXTStyleSheetPalette *q)
    : q_ptr(q)
{

}

QEXTStyleSheetPalettePrivate::~QEXTStyleSheetPalettePrivate()
{

}




QEXTStyleSheetPalette::QEXTStyleSheetPalette()
    : dd_ptr(new QEXTStyleSheetPalettePrivate(this))
{

}

QEXTStyleSheetPalette::~QEXTStyleSheetPalette()
{

}
