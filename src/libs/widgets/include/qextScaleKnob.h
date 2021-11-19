#ifndef _QEXTSCALEKNOB_H
#define _QEXTSCALEKNOB_H

/***************************************************************************************************
 *@Brief:刻度旋钮
 *  1.支持指示器样式选择 线条指示器/指针指示器/圆角指针指示器/三角形指示器
 *  2.支持鼠标按下旋转改变值
 *  3.支持负数刻度值
 *  4.支持设置当前值及范围值
 *  5.支持左右旋转角度设置
 *  6.支持设置刻度数量
 *  7.支持设置边框颜色/背景颜色/文本颜色/进度颜色
 *  8.支持设置是否等分显示左右值
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武-feiyangqingyun（QQ:517216493）代码。
 *  原作者:kimtaikee(http://www.qtcn.org/bbs/read-htm-tid-33719-ds-1.html#tpc)
 *@Date:2017-11-26
 *@History:
 *  Modification data:2021-11-06
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTScaleKnobPrivate;
class QEXT_WIDGETS_API QEXTScaleKnob : public QWidget
{
    Q_OBJECT
    Q_ENUMS(PointerStyle)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleStep READ scaleStep WRITE setScaleStep)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor percentColor READ percentColor WRITE setPercentColor)

    Q_PROPERTY(bool isRangeBisectionEnable READ isRangeBisectionEnable WRITE setRangeBisectionEnable)
    Q_PROPERTY(bool isValueVisiable READ isValueVisiable WRITE setValueVisiable)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyle
    {
        PointerStyle_Line = 0,          //线条指示器
        PointerStyle_Indicator = 1,     //指针指示器
        PointerStyle_IndicatorR = 2,    //圆角指针指示器
        PointerStyle_Triangle = 3       //三角形指示器
    };

    explicit QEXTScaleKnob(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTScaleKnob();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleStep() const;
    int startAngle() const;
    int endAngle() const;

    QColor borderColor() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor percentColor() const;

    bool isRangeBisectionEnable() const;
    bool isValueVisiable() const;
    PointerStyle pointerStyle() const;

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

    //设置刻度数量
    void setScaleStep(int step);
    //设置开始旋转角度
    void setStartAngle(int angle);
    //设置结束旋转角度
    void setEndAngle(int angle);

    //设置边框颜色
    void setBorderColor(const QColor &color);
    //设置背景颜色
    void setBackgroundColor(const QColor &color);
    //设置文本颜色
    void setTextColor(const QColor &color);
    //设置进度颜色
    void setPercentColor(const QColor &color);

    //设置是否对半等分范围值
    void setRangeBisectionEnable(bool enable);
    //设置是否显示当前值
    void setValueVisiable(bool visiable);
    //设置指针样式
    void setPointerStyle(const PointerStyle &style);

Q_SIGNALS:
    void valueChanged(double value);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawScale(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawPointerLine(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawValue(QPainter *painter);

    //根据鼠标按下的坐标设置当前按下坐标处的值
    void setPressedValue(QPointF pressedPoint);

    QScopedPointer<QEXTScaleKnobPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTScaleKnob)
    Q_DECLARE_PRIVATE(QEXTScaleKnob)
};

#endif // _QEXTSCALEKNOB_H
