#ifndef _QEXTARROWCOMPASS_H
#define _QEXTARROWCOMPASS_H

/***************************************************************************************************
 *@Brief:指南针仪表盘控件
 *  1.可设置当前度数
 *  2.可设置精确度
 *  3.可设置是否启用动画及步长
 *  4.可设置边框渐变颜色
 *  5.可设置背景渐变颜色
 *  6.可设置加深和明亮颜色
 *  7.可设置指南指北指针颜色
 *  8.可设置中心点渐变颜色
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2016-11-12
 *@History:
 *  Modification data:2021-11-05
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTArrowCompassPrivate;
class QEXT_WIDGETS_API QEXTArrowCompass : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(bool animationVisiable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor crownStartColor READ crownStartColor WRITE setCrownStartColor)
    Q_PROPERTY(QColor crownEndColor READ crownEndColor WRITE setCrownEndColor)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor)

    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(QColor northPointerColor READ northPointerColor WRITE setNorthPointerColor)
    Q_PROPERTY(QColor southPointerColor READ southPointerColor WRITE setSouthPointerColor)

    Q_PROPERTY(QColor centerStartColor READ centerStartColor WRITE setCenterStartColor)
    Q_PROPERTY(QColor centerEndColor READ centerEndColor WRITE setCenterEndColor)

public:
    explicit QEXTArrowCompass(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTArrowCompass();

    double value() const;
    int precision() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor crownStartColor() const;
    QColor crownEndColor() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor darkColor() const;
    QColor lightColor() const;

    QColor foregroundColor() const;
    QColor textColor() const;

    QColor northPointerColor() const;
    QColor southPointerColor() const;

    QColor centerStartColor() const;
    QColor centerEndColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度
    void setPrecision(int precision);

    //设置是否启用动画显示
    void setAnimationEnable(bool enable);
    //设置动画显示的步长
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    //设置外边框渐变颜色
    void setCrownStartColor(const QColor &color);
    void setCrownEndColor(const QColor &color);

    //设置背景渐变颜色
    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    //设置加深和明亮颜色
    void setDarkColor(const QColor &color);
    void setLightColor(const QColor &color);

    //设置前景色
    void setForegroundColor(const QColor &color);
    //设置文本颜色
    void setTextColor(const QColor &color);

    //设置指针颜色
    void setNorthPointerColor(const QColor &color);
    void setSouthPointerColor(const QColor &color);

    //设置中心圆颜色
    void setCenterStartColor(const QColor &color);
    void setCenterEndColor(const QColor &color);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawCrownCircle(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawCoverOuterCircle(QPainter *painter);
    void drawCoverInnerCircle(QPainter *painter);
    void drawCoverCenterCircle(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTArrowCompassPrivate> d_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTArrowCompass)
    QEXT_DECL_PRIVATE(QEXTArrowCompass)
};

#endif // _QEXTARROWCOMPASS_H
