#ifndef _QEXTSTYLESHEETPALETTE_H
#define _QEXTSTYLESHEETPALETTE_H

#include <qextWidgetGlobal.h>

#include <QPalette>

class QEXTStyleSheetPalettePrivate;
class QEXT_WIDGETS_API QEXTStyleSheetPalette : public QPalette
{
    Q_GADGET

public:
    enum ColorType
    {
        Color_Text,
        Color_Panel,
        Color_Border,
        Color_NormalStart,
        Color_NormalEnd,
        Color_DarkStart,
        Color_DarkEnd,
        Color_Highlight,
        Color_Warning,
        Color_Color_NoColorTypes
    };

    QEXTStyleSheetPalette();
    ~QEXTStyleSheetPalette();


protected:
    QScopedPointer<QEXTStyleSheetPalettePrivate> dd_ptr;

    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &s, const QEXTStyleSheetPalette &p);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleSheetPalette)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTStyleSheetPalette)
};

#endif // _QEXTSTYLESHEETPALETTE_H
