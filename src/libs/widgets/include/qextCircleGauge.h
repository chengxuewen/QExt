#ifndef _QEXTCIRCLEGAUGE_H
#define _QEXTCIRCLEGAUGE_H

/***************************************************************************************************
 *@Brief:圆形仪表盘控件
 *  1.可设置范围值,支持负数值
 *  2.可设置精确度,最大支持小数点后3位
 *  3.可设置大刻度数量/小刻度数量
 *  4.可设置开始旋转角度/结束旋转角度
 *  5.可设置是否启用动画效果以及动画效果每次移动的步长
 *  6.可设置外圆背景/内圆背景/饼圆三种颜色/刻度尺颜色/文字颜色
 *  7.自适应窗体拉伸,刻度尺和文字自动缩放
 *  8.可自由拓展各种渐变色,各圆的半径
 *  9.三色圆环按照比例设置范围角度 用户可以自由设置三色占用比例
 *  10.圆环样式可选择 三色圆环 当前圆环
 *  11.指示器样式可选择 圆形指示器 指针指示器 圆角指针指示器 三角形指示器
 *  12.可设置中间圆的宽度,以便使用更大数值
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2016-11-20
 *@History:
 *  Modification data:2021-11-05
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTCircleGaugePrivate;
class QEXT_WIDGETS_API QEXTCircleGauge : public QWidget
{
    Q_OBJECT
    Q_ENUMS(PieStyleType)
    Q_ENUMS(PointerStyleType)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(bool animationEnable READ animationEnable WRITE setAnimation)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor outerCircleColor READ outerCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor innerCircleColor READ innerCircleColor WRITE setInnerCircleColor)

    Q_PROPERTY(QColor pieColorStart READ pieColorStart WRITE setPieColorStart)
    Q_PROPERTY(QColor pieColorMid READ pieColorMid WRITE setPieColorMid)
    Q_PROPERTY(QColor pieColorEnd READ pieColorEnd WRITE setPieColorEnd)

    Q_PROPERTY(QColor coverCircleColor READ coverCircleColor WRITE setCoverCircleColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor centerCircleColor READ centerCircleColor WRITE setCenterCircleColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool overlayVisiable READ overlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(int circleWidth READ circleWidth WRITE setCircleWidth)
    Q_PROPERTY(PieStyleType pieStyle READ pieStyle WRITE setPieStyle)
    Q_PROPERTY(PointerStyleType pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PieStyleType
    {
        PieStyle_Three = 0,         	//三色圆环
        PieStyle_Current = 1        	//当前圆环
    };

    enum PointerStyleType
    {
        PointerStyle_Circle = 0,        //圆形指示器
        PointerStyle_Indicator = 1,     //指针指示器
        PointerStyle_IndicatorR = 2,    //圆角指针指示器
        PointerStyle_Triangle = 3       //三角形指示器
    };

    explicit QEXTCircleGauge(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTCircleGauge();

public:
    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor outerCircleColor() const;
    QColor innerCircleColor() const;

    QColor pieColorStart() const;
    QColor pieColorMid() const;
    QColor pieColorEnd() const;

    QColor coverCircleColor() const;
    QColor scaleColor() const;
    QColor pointerColor() const;
    QColor centerCircleColor() const;
    QColor textColor() const;

    bool overlayVisiable() const;
    QColor overlayColor() const;

    int circleWidth() const;
    PieStyleType pieStyle() const;
    PointerStyleType pointerStyle() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度
    void setPrecision(int precision);

    //设置主刻度数量
    void setScaleMajor(int scaleMajor);
    //设置小刻度数量
    void setScaleMinor(int scaleMinor);
    //设置开始旋转角度
    void setStartAngle(int startAngle);
    //设置结束旋转角度
    void setEndAngle(int endAngle);

    //设置是否启用动画显示
    void setAnimation(bool animation);
    //设置动画显示时长
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    //设置外圆背景颜色
    void setOuterCircleColor(const QColor &color);
    //设置内圆背景颜色
    void setInnerCircleColor(const QColor &color);

    //设置饼圆三种颜色
    void setPieColorStart(const QColor &color);
    void setPieColorMid(const QColor &color);
    void setPieColorEnd(const QColor &color);

    //设置覆盖圆背景颜色
    void setCoverCircleColor(const QColor &color);
    //设置刻度尺颜色
    void setScaleColor(const QColor &color);
    //设置指针颜色
    void setPointerColor(const QColor &color);
    //设置中心圆颜色
    void setCenterCircleColor(const QColor &color);
    //设置文本颜色
    void setTextColor(const QColor &color);

    //设置是否显示遮罩层
    void setOverlayVisiable(bool visiable);
    //设置遮罩层颜色
    void setOverlayColor(const QColor &color);

    //设置中间圆宽度
    void setCircleWidth(int width);
    //设置饼图样式
    void setPieStyle(const PieStyleType &style);
    //设置指针样式
    void setPointerStyle(const PointerStyleType &style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawOuterCircle(QPainter *painter);
    void drawInnerCircle(QPainter *painter);
    void drawColorPie(QPainter *painter);
    void drawCoverCircle(QPainter *painter);
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

    QScopedPointer<QEXTCircleGaugePrivate> d_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTCircleGauge)
    QEXT_DECL_PRIVATE(QEXTCircleGauge)
};

#endif // _QEXTCIRCLEGAUGE_H
