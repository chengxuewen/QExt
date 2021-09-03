#ifndef QEXTTHEMEQSSPALETTE_H
#define QEXTTHEMEQSSPALETTE_H

#include <qextThemeGlobal.h>

#include <QPalette>

class QEXTThemeQSSPalettePrivate;
class QEXT_THEME_API QEXTThemeQSSPalette : public QPalette
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

    QEXTThemeQSSPalette();
    QEXTThemeQSSPalette(const QPalette &palette);
    QEXTThemeQSSPalette(const QEXTThemeQSSPalette &palette);
    ~QEXTThemeQSSPalette();


    QEXTThemeQSSPalette &operator=(const QEXTThemeQSSPalette &palette);

    inline const QColor &color(ColorGroup cg, ColorType ct) const
    {
        return brush(cg, ct).color();
    }
    const QBrush &brush(ColorGroup cg, ColorType ct) const;
    inline void setColor(ColorGroup cg, ColorType ct, const QColor &color)
    {
        setBrush(cg, ct, color);
    }
    inline void setColor(ColorType ct, const QColor &color)
    {
        setColor(All, ct, color);
    }
    inline void setBrush(ColorType ct, const QBrush &brush)
    {
        setBrush(All, ct, brush);
    }
    void setBrush(ColorGroup cg, ColorType ct, const QBrush &brush);

    inline const QColor &color(ColorType ct) const
    {
        return color(Current, ct);
    }
    inline const QBrush &brush(ColorType ct) const
    {
        return brush(Current, ct);
    }
    inline const QBrush &itemBackground() const
    {
        return brush(ItemBackground);
    }
    inline const QBrush &textTiele() const
    {
        return brush(TextTitle);
    }
    inline const QBrush &textTips() const
    {
        return brush(TextTips);
    }
    inline const QBrush &textWarning() const
    {
        return brush(TextWarning);
    }
    inline const QBrush &textLively() const
    {
        return brush(TextLively);
    }
    inline const QBrush &lightLively() const
    {
        return brush(LightLively);
    }
    inline const QBrush &darkLively() const
    {
        return brush(DarkLively);
    }
    inline const QBrush &frameBorder() const
    {
        return brush(FrameBorder);
    }
    inline const QBrush &placeholderText() const
    {
        return brush(PlaceholderText);
    }
    inline const QBrush &frameShadowBorder() const
    {
        return brush(FrameShadowBorder);
    }

protected:
    QScopedPointer<QEXTThemePalettePrivate> d;

    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &s, const QEXTThemePalette &p);
};

#endif // QEXTTHEMEQSSPALETTE_H
