#ifndef _QEXTSTYLESHEETPALETTE_H
#define _QEXTSTYLESHEETPALETTE_H

#include <qextStyleSheetGlobal.h>

#include <QPalette>

class QEXTStyleSheetPalettePrivate;
class QEXT_STYLESHEET_API QEXTStyleSheetPalette : public QPalette
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
//    QEXTStyleSheetPalette(const QPalette &palette);
//    QEXTStyleSheetPalette(const QEXTStyleSheetPalette &palette);
    ~QEXTStyleSheetPalette();


protected:
    QScopedPointer<QEXTStyleSheetPalettePrivate> d_ptr;

    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &s, const QEXTStyleSheetPalette &p);

private:
    Q_DISABLE_COPY(QEXTStyleSheetPalette)
    Q_DECLARE_PRIVATE(QEXTStyleSheetPalette)
};

#endif // _QEXTSTYLESHEETPALETTE_H
