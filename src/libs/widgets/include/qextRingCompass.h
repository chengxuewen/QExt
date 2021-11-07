#ifndef _QEXTRINGCOMPASS_H
#define _QEXTRINGCOMPASS_H

/***************************************************************************************************
 *@Brief:圆环指南针控件
 * 1:可设置当前度数
 * 2:可设置背景颜色+文字颜色
 * 3:可设置边框颜色+边框宽度
 * 4:可设置正北点颜色
 * 5:可设置其他方向点颜色
 * 6:可设置指针颜色
 * 7:自动计算方位变显示
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Date:2019-4-23
 *@History:
 *  Modification data:2021-10-17
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTRingCompassPrivate;
class QEXT_WIDGETS_API QEXTRingCompass : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)

    Q_PROPERTY(QColor northDotColor READ northDotColor WRITE setNorthDotColor)
    Q_PROPERTY(QColor otherDotColor READ otherDotColor WRITE setOtherDotColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)

public:
    explicit QEXTRingCompass(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTRingCompass();

    double value() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor borderColor() const;
    int borderWidth() const;

    QColor northDotColor() const;
    QColor otherDotColor() const;
    QColor pointerColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置值
    void setValue(double value);
    //设置背景色
    void setBackgroundColor(const QColor &color);
    //设置文字颜色
    void setTextColor(const QColor &color);
    //设置外边框颜色
    void setBorderColor(const QColor &color);
    //设置外边框宽度
    void setBorderWidth(int width);

    //设置正北点颜色
    void setNorthDotColor(const QColor &color);
    //设置其它方向点颜色
    void setOtherDotColor(const QColor &color);
    //设置指针颜色
    void setPointerColor(const QColor &color);

Q_SIGNALS:
    void valueChanged(double value);

protected:
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawFourDots(QPainter *painter);
    void drawFourText(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTRingCompassPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRingCompass)
    QEXT_DECL_PRIVATE(QEXTRingCompass)
};

#endif // _QEXTRINGCOMPASS_H
