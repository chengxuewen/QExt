#ifndef _QEXTSELECTSLIDER_H
#define _QEXTSELECTSLIDER_H

/***************************************************************************************************
 *@Brief:滑动选择条控件
 *  1.可设置范围值,支持负数值
 *  2.可设置当前范围值
 *  3.可设置范围值颜色/范围值外颜色/文字颜色
 *  4.自适应窗体拉伸,刻度尺和文字自动缩放
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武-feiyangqingyun（QQ:517216493）代码。
 *        原作者:逆风微光(QQ:787701109)
 *@Date:2017-08-30
 *@History:
 *  Modification data:2021-10-17
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTSelectSliderPrivate;
class QEXT_WIDGETS_API QEXTSelectSlider : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(int m_maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(int m_leftValue READ leftValue WRITE setLeftValue)
    Q_PROPERTY(int m_rightValue READ rightValue WRITE setRightValue)

    Q_PROPERTY(int m_rangeValue READ rangeValue WRITE setRangeValue)
    Q_PROPERTY(int m_step READ step WRITE setStep)

    Q_PROPERTY(int m_borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(bool m_horizontal READ horizontal WRITE setHorizontal)

    Q_PROPERTY(QColor m_usedColor READ usedColor WRITE setUsedColor)
    Q_PROPERTY(QColor m_freeColor READ freeColor WRITE setFreeColor)
    Q_PROPERTY(QColor m_textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor m_rangeTextColor READ rangeTextColor WRITE setRangeTextColor)
    Q_PROPERTY(QColor m_sliderColor READ sliderColor WRITE setSliderColor)
    Q_PROPERTY(QColor m_borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor m_buttonNormalColor READ buttonNormalColor WRITE setButtonNormalColor)
    Q_PROPERTY(QColor m_buttonPressColor READ buttonPressColor WRITE setButtonPressColor)

public:
    explicit QEXTSelectSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSelectSlider();

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawButton(QPainter *painter);
    void drawSlider(QPainter *painter);
    void updateUI();

    QScopedPointer<QEXTSelectSliderPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSelectSlider)
    QEXT_DECL_PRIVATE(QEXTSelectSlider)

public:
    int minValue() const;
    int maxValue() const;
    int leftValue() const;
    int rightValue() const;

    int rangeValue() const;
    int step() const;

    int borderWidth() const;
    bool horizontal() const;

    QColor usedColor() const;
    QColor freeColor() const;
    QColor textColor() const;
    QColor rangeTextColor() const;
    QColor sliderColor() const;
    QColor borderColor() const;
    QColor buttonNormalColor() const;
    QColor buttonPressColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置范围值
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    //设置当前范围值
    void setCurrentRange(int leftValue, int rightValue);
    void setLeftValue(int leftValue);
    void setRightValue(int rightValue);

    //设置范围宽度
    void setRangeValue(int rangeValue);

    //设置单步步长
    void setStep(int step);

    //设置滑块边框宽度
    void setBorderWidth(int borderWidth);

    //设置方向
    void setHorizontal(bool horizontal);

    //设置刻度值颜色
    void setUsedColor(const QColor &usedColor);
    //设置指针颜色
    void setFreeColor(const QColor &freeColor);
    //设置文本颜色
    void setTextColor(const QColor &textColor);
    //设置文本颜色
    void setRangeTextColor(const QColor &rangeTextColor);
    //设置滑块颜色
    void setSliderColor(const QColor &sliderColor);
    //设置边框颜色
    void setBorderColor(const QColor &borderColor);

    //设置按钮正常颜色
    void setButtonNormalColor(const QColor &btnNormalColor);
    //设置按钮按下颜色
    void setButtonPressColor(const QColor &btnPressColor);

Q_SIGNALS:
    void valueChanged(int leftValue, int rightValue);
    void rangeChanged(int rangeValue);
};

#endif // _QEXTSELECTSLIDER_H
