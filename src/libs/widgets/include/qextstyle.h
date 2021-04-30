#ifndef QEXTSTYLE_H
#define QEXTSTYLE_H

#include <qextglobal.h>
#include <qextpalette.h>

#include <QPainter>
#include <QObject>
#include <QCommonStyle>
#include <QIconEngine>
#include <QStyleOption>



namespace QEXTDrawUtils
{
enum Corner {
    TopLeftCorner = 0x00001,
    TopRightCorner = 0x00002,
    BottomLeftCorner = 0x00004,
    BottomRightCorner = 0x00008
};
Q_DECLARE_FLAGS(Corners, Corner)

QEXT_API void drawShadow(QPainter *pa, const QRect &rect, qreal xRadius, qreal yRadius, const QColor &sc, qreal radius, const QPoint &offset);
QEXT_API void drawShadow(QPainter *pa, const QRect &rect, const QPainterPath &path, const QColor &sc, int radius, const QPoint &offset);
QEXT_API void drawRoundedRect(QPainter *pa, const QRect &rect, qreal xRadius, qreal yRadius, Corners corners, Qt::SizeMode mode = Qt::AbsoluteSize);
QEXT_API void drawFork(QPainter *pa, const QRectF &rect, const QColor &color, int width = 2);
QEXT_API void drawMark(QPainter *pa, const QRectF &rect, const QColor &boxInside, const QColor &boxOutside, const int penWidth, const int outLineLeng = 2);
QEXT_API void drawBorder(QPainter *pa, const QRectF &rect, const QBrush &brush, int borderWidth, int radius);
QEXT_API void drawArrow(QPainter *pa, const QRectF &rect, const QColor &color, Qt::ArrowType arrow, int width = 2);
QEXT_API void drawPlus(QPainter *painter, const QRectF &rect, const QColor &color , qreal width);
QEXT_API void drawSubtract(QPainter *painter, const QRectF &rect, const QColor &color, qreal width);

QEXT_API void drawForkElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowElement(Qt::ArrowType arrow, QPainter *pa, const QRectF &rect);
QEXT_API void drawDecreaseElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawIncreaseElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMarkElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawSelectElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawEditElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawExpandElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawReduceElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawLockElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawUnlockElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMediaVolumeElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMediaVolumeFullElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMediaVolumeMutedElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMediaVolumeLeftElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawMediaVolumeRightElement(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowEnter(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowLeave(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowNext(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowPrev(QPainter *pa, const QRectF &rect);
QEXT_API void drawShowPassword(QPainter *pa, const QRectF &rect);
QEXT_API void drawHidePassword(QPainter *pa, const QRectF &rect);
QEXT_API void drawCloseButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawIndicatorMajuscule(QPainter *pa, const QRectF &rect);
QEXT_API void drawIndicatorUnchecked(QPainter *pa, const QRectF &rect);
QEXT_API void drawIndicatorChecked(QPainter *pa, const QRectF &rect);
QEXT_API void drawDeleteButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawAddButton(QPainter *pa, const QRectF &rect);

QEXT_API void drawTitleBarMenuButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawTitleBarMinButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawTitleBarMaxButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawTitleBarCloseButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawTitleBarNormalButton(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowUp(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowDown(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowLeft(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowRight(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowBack(QPainter *pa, const QRectF &rect);
QEXT_API void drawArrowForward(QPainter *pa, const QRectF &rect);
QEXT_API void drawLineEditClearButton(QPainter *pa, const QRectF &rect);

Q_DECLARE_OPERATORS_FOR_FLAGS(Corners)
}


class QEXT_API QEXTStyle : public QCommonStyle
{
    Q_OBJECT
public:
    enum PrimitiveElement {
        PE_ItemBackground = QStyle::PE_CustomBase + 1,          //列表项的背景色
        PE_IconButtonPanel,
        PE_IconButtonIcon,
        PE_Icon,
        PE_SwitchButtonGroove,
        PE_SwitchButtonHandle,
        PE_FloatingWidget,
        PE_CustomBase = QStyle::PE_CustomBase + 0xf0000000
    };

    enum ControlElement {
        CE_IconButton = QStyle::CE_CustomBase + 1,
        CE_SwitchButton,
        CE_FloatingWidget,
        CE_ButtonBoxButton,
        CE_ButtonBoxButtonBevel,
        CE_ButtonBoxButtonLabel,
        CE_TextButton,
        CE_CustomBase = QStyle::CE_CustomBase + 0xf0000000
    };

    enum PixelMetric {
        PM_FocusBorderWidth = QStyle::PM_CustomBase + 1,        //控件焦点状态的边框宽度
        PM_FocusBorderSpacing,                                  //控件内容和border之间的间隔
        PM_FrameRadius,                                         //控件的圆角大小
        PM_ShadowRadius,                                        //控件阴影效果的半径
        PM_ShadowHOffset,                                       //阴影在水平方向的偏移
        PM_ShadowVOffset,                                       //阴影在竖直方向的偏移
        PM_FrameMargins,                                        //控件的margins区域，控件内容 = 控件大小 - FrameMargins
        PM_IconButtonIconSize,
        PM_TopLevelWindowRadius,                                //窗口的圆角大小
        PM_SwitchButtonHandleWidth,
        PM_SwithcButtonHandleHeight,
        PM_FloatingWidgetRadius,                                //(基类)的圆角半径:控件内容-Radius < 控件内容 < 控件显示大小
        PM_FloatingWidgetShadowRadius,                          //(基类)的阴影Radius区域:控件内容 < 控件内容+阴影margins < 控件内容+阴影margins+阴影Radius = 控件显示大小
        PM_FloatingWidgetShadowMargins,                         //(基类)阴影的宽度 = 控件显示大小 - 阴影Radius - 控件内容
        PM_FloatingWidgetShadowHOffset,                         //(基类)的阴影水平偏移
        PM_FloatingWidgetShadowVOffset,                         //(基类)的阴影竖直偏移
        PM_ContentsMargins,                                     //内容的边距（一般只用于左右边距）
        PM_ContentsSpacing,                                     //内容的间距（可用于列表项中每一项的距离）
        PM_ButtonMinimizedSize,                                 //按钮控件的最小大小
        PM_CustomBase = QStyle::PM_CustomBase + 0xf0000000
    };

    enum SubElement {
        SE_IconButtonIcon = QStyle::SE_CustomBase + 1,
        SE_SwitchButtonGroove,
        SE_SwitchButtonHandle,
        SE_FloatingWidget,
        SE_ButtonBoxButtonContents,
        SE_ButtonBoxButtonFocusRect,
        SE_CustomBase = QStyle::SE_CustomBase + 0xf0000000
    };

    enum ContentsType {
        CT_IconButton = QStyle::CT_CustomBase + 1,
        CT_SwitchButton,
        CT_FloatingWidget,
        CT_ButtonBoxButton,
        CT_CustomBase = QStyle::CT_CustomBase + 0xf0000000
    };

    enum StyleState {
        SS_NormalState = 0x00000000,
        SS_HoverState = 0x00000001,
        SS_PressState = 0x00000002,
        SS_StateCustomBase = 0x000000f0,

        StyleState_Mask = 0x000000ff,
        SS_CheckedFlag = 0x00000100,
        SS_SelectedFlag = 0x00000200,
        SS_FocusFlag = 0x00000400,
        SS_FlagCustomBase = 0xf00000
    };
    Q_DECLARE_FLAGS(StateFlags, StyleState)

    enum StandardPixmap {
        SP_ForkElement = QStyle::SP_CustomBase + 1,
        SP_DecreaseElement,                         //减少（-）
        SP_IncreaseElement,                         //增加（+）
        SP_MarkElement,                             //对勾
        SP_SelectElement,                           //选择（...）
        SP_EditElement,                             //编辑
        SP_ExpandElement,                           //展开
        SP_ReduceElement,                           //收缩
        SP_LockElement,                             //锁定
        SP_UnlockElement,                           //解锁
        SP_MediaVolumeLowElement,                   //音量
        SP_MediaVolumeHighElement,                  //满音量
        SP_MediaVolumeMutedElement,                 //静音
        SP_MediaVolumeLeftElement,                  //左声道
        SP_MediaVolumeRightElement,                 //右声道
        SP_ArrowEnter,                              //进入
        SP_ArrowLeave,                              //离开
        SP_ArrowNext,                               //下一页
        SP_ArrowPrev,                               //上一页
        SP_ShowPassword,                            //显示密码
        SP_HidePassword,                            //因此密码
        SP_CloseButton,                             //关闭按钮（X）
        SP_IndicatorMajuscule,                      //大写标识
        SP_IndicatorSearch,                         //搜索标识（放大镜）
        SP_IndicatorUnchecked,                      //搜索标识（对应对勾的选中状态）
        SP_IndicatorChecked,                        //搜索标识（对勾）
        SP_DeleteButton,                            //删除按钮
        SP_AddButton,                               //新增按钮
        SP_CustomBase = QStyle::SP_CustomBase + 0xf0000000
    };

    QEXTStyle();

    static QColor adjustColor(const QColor &base, qint8 hueFloat = 0, qint8 saturationFloat = 0, qint8 lightnessFloat = 0,
                              qint8 redFloat = 0, qint8 greenFloat = 0, qint8 blueFloat = 0, qint8 alphaFloat = 0);
    static QColor blendColor(const QColor &substrate, const QColor &superstratum);
    static QPair<QIcon::Mode, QIcon::State> toIconModeState(const QStyleOption *option);

    static void setTooltipTextFormat(Qt::TextFormat format);
    static Qt::TextFormat tooltipTextFormat();
    static QEXTStyle::StyleState getState(const QStyleOption *option);
    static void setFocusRectVisible(QWidget *widget, bool visible);
    static void setFrameRadius(QWidget *widget, int radius);

    static void drawPrimitive(const QStyle *style, QEXTStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w = QEXT_NULLPTR);
    static void drawControl(const QStyle *style, QEXTStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w = QEXT_NULLPTR);
    static int pixelMetric(const QStyle *style, QEXTStyle::PixelMetric m, const QStyleOption *opt = QEXT_NULLPTR, const QWidget *widget = QEXT_NULLPTR);
    static QRect subElementRect(const QStyle *style, QEXTStyle::SubElement r, const QStyleOption *opt, const QWidget *widget = QEXT_NULLPTR);
    static QSize sizeFromContents(const QStyle *style, QEXTStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget = QEXT_NULLPTR);
    static QIcon standardIcon(const QStyle *style, StandardPixmap st, const QStyleOption *opt = QEXT_NULLPTR, const QWidget *widget = QEXT_NULLPTR);

    void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w = QEXT_NULLPTR) const QEXT_OVERRIDE;
    void drawControl(QStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w = QEXT_NULLPTR) const QEXT_OVERRIDE;
    int pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt = QEXT_NULLPTR, const QWidget *widget = QEXT_NULLPTR) const QEXT_OVERRIDE;
    int styleHint(StyleHint sh, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *shret) const QEXT_OVERRIDE;
    QRect subElementRect(QStyle::SubElement r, const QStyleOption *opt, const QWidget *widget = QEXT_NULLPTR) const QEXT_OVERRIDE;
    QSize sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget = QEXT_NULLPTR) const QEXT_OVERRIDE;
    QIcon standardIcon(QStyle::StandardPixmap st, const QStyleOption *opt = QEXT_NULLPTR, const QWidget *widget = QEXT_NULLPTR) const QEXT_OVERRIDE;

    QPalette standardPalette() const QEXT_OVERRIDE;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const QEXT_OVERRIDE;

    // 获取一个加工后的画笔
    QBrush generatedBrush(const QStyleOption *option, const QBrush &base,
                          QPalette::ColorGroup cg = QPalette::Normal,
                          QPalette::ColorRole role = QPalette::NoRole) const;
    QBrush generatedBrush(StyleState state, const QStyleOption *option, const QBrush &base,
                          QPalette::ColorGroup cg = QPalette::Normal,
                          QPalette::ColorRole role = QPalette::NoRole) const;
    virtual QBrush generatedBrush(StateFlags flags, const QBrush &base,
                                  QPalette::ColorGroup cg = QPalette::Normal,
                                  QPalette::ColorRole role = QPalette::NoRole,
                                  const QStyleOption *option = QEXT_NULLPTR) const;

    QBrush generatedBrush(const QStyleOption *option, const QBrush &base,
                          QEXTPalette::ColorGroup cg = QEXTPalette::Normal,
                          QEXTPalette::ColorType type = QEXTPalette::ItemBackground) const;
    QBrush generatedBrush(StyleState state, const QStyleOption *option, const QBrush &base,
                          QEXTPalette::ColorGroup cg = QEXTPalette::Normal,
                          QEXTPalette::ColorType type = QEXTPalette::ItemBackground) const;
    virtual QBrush generatedBrush(StateFlags flags, const QBrush &base,
                                  QEXTPalette::ColorGroup cg = QEXTPalette::Normal,
                                  QEXTPalette::ColorType type = QEXTPalette::ItemBackground,
                                  const QStyleOption *option = QEXT_NULLPTR) const;
};


class QEXT_API QEXTStyleHelper
{
public:
    inline QEXTStyleHelper(const QStyle *style = QEXT_NULLPTR) {
        setStyle(style);
    }

    inline void setStyle(const QStyle *style) {
        m_style = style;
        m_dstyle = qobject_cast<const QEXTStyle*>(style);
    }

    inline const QStyle *style() const
    { return m_style; }
    inline const QEXTStyle *dstyle() const
    { return m_dstyle; }

    inline QBrush generatedBrush(const QStyleOption *option, const QBrush &base,
                                 QPalette::ColorGroup cg = QPalette::Normal,
                                 QPalette::ColorRole role = QPalette::NoRole) const
    { return m_dstyle ? m_dstyle->generatedBrush(option, base, cg, role) : base; }
    inline QBrush generatedBrush(const QStyleOption *option, const QBrush &base,
                                 QPalette::ColorGroup cg = QPalette::Normal,
                                 QEXTPalette::ColorType type = QEXTPalette::NoType) const

    { return m_dstyle ? m_dstyle->generatedBrush(option, base, cg, type) : base; }
    inline QColor getColor(const QStyleOption *option, QPalette::ColorRole role) const
    { return generatedBrush(option, option->palette.brush(role), option->palette.currentColorGroup(), role).color(); }
    inline QColor getColor(const QStyleOption *option, const QEXTPalette &palette, QEXTPalette::ColorType type) const
    { return generatedBrush(option, palette.brush(type), palette.currentColorGroup(), type).color(); }
//    template<class T>
//    inline QColor getColor(const T *option, QEXTPalette::ColorType type) const
//    { return getColor(option, option->dpalette, type); }

//    inline void drawPrimitive(QEXTStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w = nullptr) const
//    { m_dstyle ? m_dstyle->drawPrimitive(pe, opt, p, w) : QEXTStyle::drawPrimitive(m_style, pe, opt, p, w); }
//    inline void drawControl(QEXTStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w = nullptr) const
//    { m_dstyle ? m_dstyle->drawControl(ce, opt, p, w) : QEXTStyle::drawControl(m_style, ce, opt, p, w); }
//    inline int pixelMetric(QEXTStyle::PixelMetric m, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr) const
//    { return m_dstyle ? m_dstyle->pixelMetric(m, opt, widget) : QEXTStyle::pixelMetric(m_style, m, opt, widget); }
//    inline QRect subElementRect(QEXTStyle::SubElement r, const QStyleOption *opt, const QWidget *widget = nullptr) const
//    { return m_dstyle ? m_dstyle->subElementRect(r, opt, widget) : QEXTStyle::subElementRect(m_style, r, opt, widget); }
//    inline QSize sizeFromContents(QEXTStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget = nullptr) const
//    { return m_dstyle ? m_dstyle->sizeFromContents(ct, opt, contentsSize, widget) : QEXTStyle::sizeFromContents(m_style, ct, opt, contentsSize, widget); }
//    inline QIcon standardIcon(QEXTStyle::StandardPixmap standardIcon, const QStyleOption *opt, const QWidget *widget = nullptr) const
//    { return m_dstyle ? m_dstyle->standardIcon(standardIcon, opt, widget) : QEXTStyle::standardIcon(m_style, standardIcon, opt, widget); }

private:
    const QStyle *m_style;
    const QEXTStyle *m_dstyle;
};

class QEXT_API QEXTStylePainter : public QPainter
{
public:
    inline QEXTStylePainter() : QPainter(), widget(QEXT_NULLPTR), wstyle(QEXT_NULLPTR) {}
    inline explicit QEXTStylePainter(QWidget *w) { begin(w, w); }
    inline QEXTStylePainter(QPaintDevice *pd, QWidget *w) { begin(pd, w); }
    inline bool begin(QWidget *w) { return begin(w, w); }
    inline bool begin(QPaintDevice *pd, QWidget *w) {
        Q_ASSERT_X(w, "QEXTStylePainter::QEXTStylePainter", "Widget must be non-zero");
        widget = w;
        wstyle = w->style();
        dstyle.setStyle(wstyle);
        return QPainter::begin(pd);
    }
    inline void drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption &opt);
    inline void drawPrimitive(QEXTStyle::PrimitiveElement pe, const QStyleOption &opt);
    inline void drawControl(QStyle::ControlElement ce, const QStyleOption &opt);
    inline void drawControl(QEXTStyle::ControlElement ce, const QStyleOption &opt);
    inline void drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex &opt);
    inline void drawItemText(const QRect &r, int flags, const QPalette &pal, bool enabled,
                             const QString &text, QPalette::ColorRole textRole = QPalette::NoRole);
    inline void drawItemPixmap(const QRect &r, int flags, const QPixmap &pixmap);
    inline QStyle *style() const { return wstyle; }

private:
    QWidget *widget;
    QStyle *wstyle;
    QEXTStyleHelper dstyle;
    Q_DISABLE_COPY(QEXTStylePainter)
};

void QEXTStylePainter::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption &opt)
{
    wstyle->drawPrimitive(pe, &opt, this, widget);
}

void QEXTStylePainter::drawPrimitive(QEXTStyle::PrimitiveElement pe, const QStyleOption &opt)
{
//    dstyle.drawPrimitive(pe, &opt, this, widget);
}

void QEXTStylePainter::drawControl(QStyle::ControlElement ce, const QStyleOption &opt)
{
    wstyle->drawControl(ce, &opt, this, widget);
}

void QEXTStylePainter::drawControl(QEXTStyle::ControlElement ce, const QStyleOption &opt)
{
//    dstyle.drawControl(ce, &opt, this, widget);
}

void QEXTStylePainter::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex &opt)
{
    wstyle->drawComplexControl(cc, &opt, this, widget);
}

void QEXTStylePainter::drawItemText(const QRect &r, int flags, const QPalette &pal, bool enabled,
                                 const QString &text, QPalette::ColorRole textRole)
{
    wstyle->drawItemText(this, r, flags, pal, enabled, text, textRole);
}

void QEXTStylePainter::drawItemPixmap(const QRect &r, int flags, const QPixmap &pixmap)
{
    wstyle->drawItemPixmap(this, r, flags, pixmap);
}



class QEXT_API QEXTStyledIconEngine : public QIconEngine
{
public:
    static void drawIcon(const QIcon &icon, QPainter *pa, const QRectF &rect);

    typedef void(DrawFun)(QPainter *, const QRectF &rect);
    QEXTStyledIconEngine(const QString &iconName = QString());

//    void bindDrawFun(DrawFun drawFun);
    void setIconName(const QString &name);

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE;
    void paint(QPainter *painter, const QPalette &palette, const QRectF &rect);
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE;

//    QIconEngine *clone() const override;
    void setFrontRole(const QWidget* widget, QPalette::ColorRole role);

protected:
//    void virtual_hook(int id, void *data) override;

//    DrawFun m_drawFun;
    QString m_iconName;
    QPalette::ColorRole m_painterRole;
    const QWidget *m_widget;
};

#endif // QEXTSTYLE_H
