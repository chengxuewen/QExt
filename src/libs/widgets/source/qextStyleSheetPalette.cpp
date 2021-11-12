#include <qextStyleSheetPalette.h>
#include <qextStyleSheetPalette_p.h>


QEXTStyleSheetPalettePrivate::QEXTStyleSheetPalettePrivate(QEXTStyleSheetPalette *q)
    : q_ptr(q)
{

}

QEXTStyleSheetPalettePrivate::~QEXTStyleSheetPalettePrivate()
{

}




QEXTStyleSheetPalette::QEXTStyleSheetPalette()
    : d_ptr(new QEXTStyleSheetPalettePrivate(this))
{

}

QEXTStyleSheetPalette::~QEXTStyleSheetPalette()
{

}
