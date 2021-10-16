#ifndef _QEXTTHEMEPALETTE_H
#define _QEXTTHEMEPALETTE_H

#include <qextThemeGlobal.h>

#include <QPalette>

class QEXTThemePalettePrivate;
class QEXT_THEME_API QEXTThemePalette : public QPalette
{
public:
    enum ColorType
    {
        Color_ItemBackground,     //列表项的背景色
        Color_TextTitle,          //标题型文本的颜色
        Color_TextTips,           //提示性文本的颜色
        Color_TextWarning,        //警告类型的文本颜色
        Color_TextLively,         //活跃式文本颜色（不受活动色影响）
        Color_LightLively,        //活跃式按钮（recommend button）背景色中的亮色（不受活跃色影响）
        Color_DarkLively,         //活跃式按钮（recommend button）背景色中的暗色，会从亮色渐变到暗色（不受活跃色影响）
        Color_FrameBorder,        //控件边框颜色
        Color_PlaceholderText,    //占位类型的文本颜色，可用于输入框占位内容等提示性文字
        Color_FrameShadowBorder,  //用于跟阴影叠加的边框颜色
        Color_ObviousBackground,  //明显的背景色
        Color_NColorTypes
    };

    QEXTThemePalette();
    QEXTThemePalette(const QPalette &palette);
    QEXTThemePalette(const QEXTThemePalette &palette);
    ~QEXTThemePalette();

    QEXTThemePalette &operator=(const QEXTThemePalette &palette);

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
        return brush(Color_ItemBackground);
    }
    inline const QBrush &textTiele() const
    {
        return brush(Color_TextTitle);
    }
    inline const QBrush &textTips() const
    {
        return brush(Color_TextTips);
    }
    inline const QBrush &textWarning() const
    {
        return brush(Color_TextWarning);
    }
    inline const QBrush &textLively() const
    {
        return brush(Color_TextLively);
    }
    inline const QBrush &lightLively() const
    {
        return brush(Color_LightLively);
    }
    inline const QBrush &darkLively() const
    {
        return brush(Color_DarkLively);
    }
    inline const QBrush &frameBorder() const
    {
        return brush(Color_FrameBorder);
    }
    inline const QBrush &placeholderText() const
    {
        return brush(Color_PlaceholderText);
    }
    inline const QBrush &frameShadowBorder() const
    {
        return brush(Color_FrameShadowBorder);
    }

    using QPalette::color;
    using QPalette::brush;
    using QPalette::setBrush;
    using QPalette::setColor;

protected:
    QScopedPointer<QEXTThemePalettePrivate> d;

    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &s, const QEXTThemePalette &p);
};


QT_BEGIN_NAMESPACE
/*****************************************************************************
  QEXTThemePalette stream functions
 *****************************************************************************/
#ifndef QT_NO_DATASTREAM
Q_GUI_EXPORT QDataStream &operator<<(QDataStream &ds, const QEXTThemePalette &p);
Q_GUI_EXPORT QDataStream &operator>>(QDataStream &ds, QEXTThemePalette &p);
#endif // QT_NO_DATASTREAM
QT_END_NAMESPACE

#endif // _QEXTTHEMEPALETTE_H
