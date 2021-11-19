#ifndef _QEXTDIAL_H
#define _QEXTDIAL_H

/***************************************************************************************************
 *@Brief:旋转仪表盘控件
 *  1.支持指示器样式选择 圆形指示器/指针指示器/圆角指针指示器/三角形指示器
 *  2.支持鼠标按下旋转改变值
 *  3.支持负数刻度值
 *  4.支持设置当前值及范围值
 *  5.支持左右旋转角度设置
 *  6.支持设置大刻度数量和小刻度数量
 *  7.支持设置各种颜色
 *  8.字号随窗体拉伸自动变化
 *  9.可设置是否显示当前值
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Date:2016-11-11
 *@History:
 *  Modification data:2021-10-15
 *  Author:chengxuewen
 *  Brief:1.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTDialPrivate;
class QEXT_WIDGETS_API QEXTDial : public QWidget
{
    Q_OBJECT
    Q_ENUMS(PointerStyleType)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool valueVisiable READ valueVisiable WRITE setShowValue)
    Q_PROPERTY(PointerStyleType pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyleType
    {
        PointerStyle_Circle = 0,     //圆形指示器
        PointerStyle_Indicator = 1,  //指针指示器
        PointerStyle_IndicatorR = 2, //圆角指针指示器
        PointerStyle_Triangle = 3    //三角形指示器
    };

    explicit QEXTDial(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTDial();



    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    QColor darkColor() const;
    QColor lightColor() const;
    QColor textColor() const;

    bool valueVisiable() const;
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
    void setStartAngle(int angle);
    //设置结束旋转角度
    void setEndAngle(int angle);

    //设置颜色
    void setDarkColor(const QColor &color);
    void setLightColor(const QColor &color);

    //设置文本颜色
    void setTextColor(const QColor &color);

    //设置是否显示当前值
    void setShowValue(bool visiable);
    //设置指针样式
    void setPointerStyle(const PointerStyleType &style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawBorderCircle(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawPointerCircle(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    //根据鼠标按下的坐标设置当前按下坐标处的值
    void setPressedValue(QPointF point);

    QScopedPointer<QEXTDialPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY(QEXTDial)
    Q_DECLARE_PRIVATE(QEXTDial)
};

#endif // _QEXTDIAL_H
