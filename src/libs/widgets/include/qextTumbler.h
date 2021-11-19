#ifndef _QEXTTUMBLER_H
#define _QEXTTUMBLER_H

/***************************************************************************************************
 *@Brief:滑动选择器控件
 *  1.可设置数据队列值
 *  2.可设置当前队列索引及当前值
 *  2.支持任意窗体大小缩放
 *  3.支持背景色前景色文字颜色线条颜色设置
 *  4.支持左右滑动和上下滑动两种形式
 *  5.支持鼠标滚动切换元素
 *  6.中间值自动放大显示且居中
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Date:2016-11-24
 *@History:
 *  Modification data:2021-10-15
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTTumblerPrivate;
class QEXT_WIDGETS_API QEXTTumbler : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString m_currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(bool m_isHorizontal READ isHorizontal WRITE setHorizontal)

    Q_PROPERTY(QColor m_foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor m_backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor m_lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor m_textColor READ textColor WRITE setTextColor)

public:
    explicit QEXTTumbler(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTumbler();

    QStringList valueList() const;
    int currentIndex() const;
    QString currentValue() const;
    bool isHorizontal() const;

    QColor foregroundColor() const;
    QColor backgroundColor() const;
    QColor lineColor() const;
    QColor textColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置值队列
    void setValueList(const QStringList &values);
    //设置当前索引
    void setCurrentIndex(int index);
    //设置当前值
    void setCurrentValue(const QString &value);
    //设置横向显示,如果为假则纵向显示
    void setHorizontal(bool horizontal);

    //设置前景色
    void setForegroundColor(const QColor &color);
    //设置背景色
    void setBackgroundColor(const QColor &color);
    //设置线条颜色
    void setLineColor(const QColor &color);
    //设置文本颜色
    void setTextColor(const QColor &color);

Q_SIGNALS:
    void currentIndexChanged(int index);
    void currentValueChanged(const QString &value);

protected:
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawText(QPainter *painter, int index, int offset);

    void checkPosition();

    QScopedPointer<QEXTTumblerPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTumbler)
    Q_DECLARE_PRIVATE(QEXTTumbler)
};

#endif // _QEXTTUMBLER_H
