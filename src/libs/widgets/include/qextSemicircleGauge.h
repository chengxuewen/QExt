#ifndef _QEXTSEMICIRCLEGAUGE_H
#define _QEXTSEMICIRCLEGAUGE_H

/***************************************************************************************************
 *@Brief:半圆仪表盘控件
 *  1.可设置范围值,支持负数值
 *  2.可设置大刻度数量/小刻度数量
 *  3.可设置开始旋转角度/结束旋转角度
 *  4.可设置是否启用动画效果以及动画效果每次移动的步长
 *  5.自适应窗体拉伸,刻度尺和文字自动缩放
 *  6.可自由拓展各种渐变色,各圆的半径
 *  7.指示器样式可选择 圆形指示器 指针指示器 圆角指针指示器 三角形指示器
 *  8.可设置当前值进度颜色和剩余值进度颜色
 *  9.背景透明,可自由设置背景图片
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2017-8-20
 *@History:
 *  Modification data:2021-11-05
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTSemicircleGaugePrivate;
class QEXT_WIDGETS_API QEXTSemicircleGauge : public QWidget
{
    Q_OBJECT
    Q_ENUMS(PointerStyleType)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(bool animationVisiable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor usedColor READ usedColor WRITE setUsedColor)
    Q_PROPERTY(QColor freeColor READ freeColor WRITE setFreeColor)

    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)

    Q_PROPERTY(bool overlayVisiable READ overlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(PointerStyleType pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyleType
    {
        PointerStyle_Circle = 0,        //圆形指示器
        PointerStyle_Indicator = 1,     //指针指示器
        PointerStyle_IndicatorR = 2,    //圆角指针指示器
        PointerStyle_Triangle = 3       //三角形指示器
    };

    explicit QEXTSemicircleGauge(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSemicircleGauge();

    double minValue() const;
    double maxValue() const;
    double value() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor usedColor() const;
    QColor freeColor() const;

    QColor scaleColor() const;
    QColor pointerColor() const;
    QColor textColor() const;
    QColor titleColor() const;

    bool overlayVisiable() const;
    QColor overlayColor() const;

    PointerStyleType pointerStyle() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置范围值
    void setRange(double minValue, double maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置主刻度数量
    void setScaleMajor(int scaleMajor);
    //设置小刻度数量
    void setScaleMinor(int scaleMinor);
    //设置开始旋转角度
    void setStartAngle(int startAngle);
    //设置结束旋转角度
    void setEndAngle(int endAngle);

    //设置是否启用动画显示
    void setAnimationEnable(bool enable);
    //设置动画显示的步长
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    //设置当前值颜色
    void setUsedColor(const QColor &usedColor);
    //设置剩余值颜色
    void setFreeColor(const QColor &freeColor);

    //设置刻度尺颜色
    void setScaleColor(const QColor &scaleColor);
    //设置指针颜色
    void setPointerColor(const QColor &pointerColor);
    //设置文本颜色
    void setTextColor(const QColor &textColor);
    //设置标题颜色
    void setTitleColor(const QColor &titleColor);

    //设置是否显示遮罩层
    void setOverlayVisiable(bool showOverlay);
    //设置遮罩层颜色
    void setOverlayColor(const QColor &overlayColor);

    //设置指针样式
    void setPointerStyle(const PointerStyleType &pointerStyle);

Q_SIGNALS:
    void valueChanged(double value);

protected:
    void paintEvent(QPaintEvent *);

    void drawArc(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawPointerCircle(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawRoundCircle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawOverlay(QPainter *painter);

    QScopedPointer<QEXTSemicircleGaugePrivate> d_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSemicircleGauge)
    Q_DECLARE_PRIVATE(QEXTSemicircleGauge)
};

#endif // _QEXTSEMICIRCLEGAUGE_H
