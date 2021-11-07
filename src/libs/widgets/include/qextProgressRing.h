#ifndef _QEXTPROGRESSRING_H
#define _QEXTPROGRESSRING_H

/***************************************************************************************************
 *@Brief:环形进度条控件
 * 1.可设置范围值,支持负数值
 * 2.可设置精确度,最大支持小数点后3位
 * 3.可设置起始角度
 * 4.可设置三种值+三种颜色,启用自动检测值后绘制不同的颜色
 * 5.可设置是否启用动画效果以及动画效果每次移动的步长
 * 6.可设置背景颜色/文字颜色/进度颜色/中间圆颜色
 * 7.可设置值警戒报警比较模式 0-不比较 1-最大值报警 2-最小值报警
 * 8.可设置显示的值是百分比
 * 9.可设置圆环与背景之间的距离即间距
 * 10:可设置圆环的宽度
 * 11:可设置圆环背景颜色,形成两种颜色差
 * 12:可设置顺时针逆时针转
 * 13:可设置中间圆是否扣掉透明
 * 14:可设置直接显示的文字优先显示
 * 15:自适应窗体拉伸,刻度尺和文字自动缩放
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武-feiyangqingyun（QQ:517216493）代码。
 *@Date:2019-05-01
 *@History:
 *  Modification data:2021-10-16
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTProgressRingPrivate;
class QEXT_WIDGETS_API QEXTProgressRing : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)
    Q_PROPERTY(QString text READ text WRITE setText)

    Q_PROPERTY(bool clipCenter READ clipCenter WRITE setClipCenter)
    Q_PROPERTY(bool clockWise READ clockWise WRITE setClockWise)
    Q_PROPERTY(bool percentVisiable READ percentVisiable WRITE setPercentVisiable)

    Q_PROPERTY(int alarmMode READ alarmMode WRITE setAlarmMode)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int ringPadding READ ringPadding WRITE setRingPadding)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)

    Q_PROPERTY(bool animationEnable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor ringColor READ ringColor WRITE setRingColor)
    Q_PROPERTY(QColor ringBackgroundColor READ ringBackgroundColor WRITE setRingBgColor)
    Q_PROPERTY(QColor circleColor READ circleColor WRITE setCircleColor)

    Q_PROPERTY(int ringValue1 READ ringValue1 WRITE setRingValue1)
    Q_PROPERTY(int ringValue2 READ ringValue2 WRITE setRingValue2)
    Q_PROPERTY(int ringValue3 READ ringValue3 WRITE setRingValue3)

    Q_PROPERTY(QColor ringColor1 READ ringColor1 WRITE setRingColor1)
    Q_PROPERTY(QColor ringColor2 READ ringColor2 WRITE setRingColor2)
    Q_PROPERTY(QColor ringColor3 READ ringColor3 WRITE setRingColor3)

public:
    explicit QEXTProgressRing(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTProgressRing();

    double minValue() const;
    double maxValue() const;
    double getValue() const;
    int precision() const;
    QString text() const;

    bool clipCenter() const;
    bool clockWise() const;
    bool percentVisiable() const;

    int alarmMode() const;
    int startAngle() const;
    int ringPadding() const;
    int ringWidth() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor backgroundColor() const;
    QColor textColor() const;
    QColor ringColor() const;
    QColor ringBackgroundColor() const;
    QColor circleColor() const;

    int ringValue1() const;
    int ringValue2() const;
    int ringValue3() const;

    QColor ringColor1() const;
    QColor ringColor2() const;
    QColor ringColor3() const;

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
    //设置显示的文字
    void setText(const QString &text);

    //设置中间部分是否扣掉成透明
    void setClipCenter(bool clipCenter);
    //设置顺时针逆时针转
    void setClockWise(bool clockWise);
    //设置显示百分比
    void setPercentVisiable(bool visiable);

    //设置启动自动检验
    void setAlarmMode(int alarmMode);
    //设置起始角度
    void setStartAngle(int startAngle);
    //设置圆环间距
    void setRingPadding(int padding);
    //设置圆环宽度
    void setRingWidth(int width);

    //设置是否启用动画显示
    void setAnimationEnable(bool enable);
    //设置动画显示长
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    //设置背景颜色
    void setBackgroundColor(const QColor &color);
    //设置文本颜色
    void setTextColor(const QColor &color);
    //设置圆环进度颜色
    void setRingColor(const QColor &color);
    //设置圆环背景颜色
    void setRingBgColor(const QColor &color);
    //设置中心圆颜色
    void setCircleColor(const QColor &color);

    //设置三种值
    void setRingValue1(int value);
    void setRingValue2(int value);
    void setRingValue3(int value);

    //设置三种颜色
    void setRingColor1(const QColor &color);
    void setRingColor2(const QColor &color);
    void setRingColor3(const QColor &color);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawRing(QPainter *painter);
    void drawPadding(QPainter *painter);
    void drawCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTProgressRingPrivate> d_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressRing)
    QEXT_DECL_PRIVATE(QEXTProgressRing)
};

#endif // _QEXTPROGRESSRING_H
