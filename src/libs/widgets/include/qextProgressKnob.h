#ifndef _QEXTPROGRESSKNOB_H
#define _QEXTPROGRESSKNOB_H

/***************************************************************************************************
 *@Brief:进度条旋钮
 *  1.支持指示器样式选择 圆形指示器/指针指示器/圆角指针指示器/三角形指示器
 *  2.支持鼠标按下旋转改变值
 *  3.支持负数范围值
 *  4.支持设置当前值及范围值
 *  5.支持设置起始旋转角度和结束旋转角度
 *  6.支持设置背景色/进度颜色/中间圆渐变颜色
 *  7.随窗体拉伸自动变化
 *  8.支持鼠标进入和离开动画效果
 *  9.可设置是否显示当前值
 *  10.可设置是否显示指示器
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2016-12-03
 *@History:
 *  Modification data:2021-10-16
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QVariant>

class QPropertyAnimation;
class QEXTProgressKnobPrivate;
class QEXT_WIDGETS_API QEXTProgressKnob : public QWidget
{
	Q_OBJECT
	Q_ENUMS(PointerStyle)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(QColor progressBackgroundColor READ progressBackgroundColor WRITE setProgressBackgroundColor)
    Q_PROPERTY(QColor circleStartColor READ circleStartColor WRITE setCircleStartColor)
    Q_PROPERTY(QColor circleEndColor READ circleEndColor WRITE setCircleEndColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool pointerVisiable READ pointerVisiable WRITE setPointerVisiable)
    Q_PROPERTY(bool valueVisiable READ valueVisiable WRITE setValueVisiable)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
	enum PointerStyle {
		PointerStyle_Circle = 0,        //圆形指示器
        PointerStyle_Indicator,     //指针指示器
        PointerStyle_IndicatorR,    //圆角指针指示器
        PointerStyle_Triangle       //三角形指示器
	};

    explicit QEXTProgressKnob(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTProgressKnob();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int startAngle() const;
    int endAngle() const;

    QColor backgroundColor() const;
    QColor progressColor() const;
    QColor progressBackgroundColor() const;
    QColor circleStartColor() const;
    QColor circleEndColor() const;
    QColor textColor() const;

    bool pointerVisiable() const;
    bool valueVisiable() const;
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

    //设置开始旋转角度
    void setStartAngle(int angle);
    //设置结束旋转角度
    void setEndAngle(int angle);

    //设置背景色
    void setBackgroundColor(const QColor &color);

    //设置进度颜色
    void setProgressColor(const QColor &color);
    void setProgressBackgroundColor(const QColor &color);

    //设置中间圆颜色
    void setCircleStartColor(const QColor &color);
    void setCircleEndColor(const QColor &color);

    //设置文本颜色
    void setTextColor(const QColor &color);

    //设置是否显示指示器
    void setPointerVisiable(bool visiable);
    //设置是否显示当前值
    void setValueVisiable(bool visiable);
    //设置指针样式
    void setPointerStyle(PointerStyle style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
	void drawColorPie(QPainter *painter);
	void drawCoverCircle(QPainter *painter);
	void drawCircle(QPainter *painter);
	void drawPointerCircle(QPainter *painter);
	void drawPointerIndicator(QPainter *painter);
	void drawPointerIndicatorR(QPainter *painter);
	void drawPointerTriangle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTProgressKnobPrivate> d_ptr;

private slots:
    void setEasingCurve();
    void updateRadius(QVariant radius);

private:
    //根据鼠标按下的坐标设置当前按下坐标处的值
    void setPressedValue(QPointF pressedPoint);

private:	
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressKnob)
    QEXT_DECL_PRIVATE(QEXTProgressKnob)
};

#endif // _QEXTPROGRESSKNOB_H
