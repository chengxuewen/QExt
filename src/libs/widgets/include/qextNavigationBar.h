#ifndef _QEXTNAVIGATIONBAR_H
#define _QEXTNAVIGATIONBAR_H

/***************************************************************************************************
 *@Brief:滑动导航条控件
 *  1.可键盘按键上下移动元素功能
 *  2.支持窗体大小改变控件自动拉伸
 *  3.支持移动到第一个/末一个/上移/下移/移动到指定索引/移动到指定元素
 *  4.支持扁平处理
 *  5.支持纵向风格
 *  6.可设置圆角角度,包括主背景和选中元素背景
 *  7.可设置间距
 *  8.可设置导航条主背景渐变色
 *  9.可设置当前条目选中背景渐变色
 *  10.可设置条目未选中和选中的文字颜色
 *  11.可设置五种选中风格样式
 *  12.可设置线条颜色和宽度
 *  13.选中条目的宽度为条目文字集合中最长的一个
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2016-10-8
 *@History:
 *  Modification data:2021-11-09
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTNavigationBarPrivate;
class QEXT_WIDGETS_API QEXTNavigationBar : public QWidget
{
    Q_OBJECT
    Q_ENUMS(BarStyleType)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor barStartColor READ barStartColor WRITE setBarStartColor)
    Q_PROPERTY(QColor barEndColor READ barEndColor WRITE setBarEndColor)

    Q_PROPERTY(QColor textNormalColor READ textNormalColor WRITE setTextNormalColor)
    Q_PROPERTY(QColor textSelectColor READ textSelectColor WRITE setTextSelectColor)

    Q_PROPERTY(QString items READ items WRITE setItems)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString currentItem READ currentItem WRITE setCurrentItem)

    Q_PROPERTY(int backgroundRadius READ backgroundRadius WRITE setBackgroundRadius)
    Q_PROPERTY(int barRadius READ barRadius WRITE setBarRadius)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(BarStyleType barStyle READ barStyle WRITE setBarStyle)

    Q_PROPERTY(bool keyMoveEnable READ keyMoveEnable WRITE setKeyMoveEnable)
    Q_PROPERTY(bool isHorizontal READ isHorizontal WRITE setHorizontal)
    Q_PROPERTY(bool isFlat READ isFlat WRITE setFlat)

public:
    enum BarStyleType {
        BarStyle_Rect = 0,              //圆角矩形
        BarStyle_Line_Top = 1,          //上边线条
        BarStyle_Line_Right = 2,        //右边线条
        BarStyle_Line_Bottom = 3,       //下边线条
        BarStyle_Line_Left = 4          //左边线条
    };

    explicit QEXTNavigationBar(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationBar();

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor barStartColor() const;
    QColor barEndColor() const;

    QColor textNormalColor() const;
    QColor textSelectColor() const;

    QString items() const;
    int currentIndex() const;
    QString currentItem() const;

    int backgroundRadius() const;
    int barRadius() const;
    int space() const;

    int lineWidth() const;
    QColor lineColor() const;

    BarStyleType barStyle() const;

    bool keyMoveEnable() const;
    bool isHorizontal() const;
    bool isFlat() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //删除所有条目
    void clearItem();

    //设置导航条主背景渐变色
    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    //设置当前条目选中背景渐变色
    void setBarStartColor(const QColor &color);
    void setBarEndColor(const QColor &color);

    //设置文字颜色
    void setTextNormalColor(const QColor &color);
    void setTextSelectColor(const QColor &color);

    //设置子项元素及当前索引及值
    void setItems(const QString &items);
    void setCurrentIndex(int index);
    void setCurrentItem(const QString &item);

    //设置边框圆角
    void setBackgroundRadius(int radius);
    void setBarRadius(int radius);
    //设置条目间距
    void setSpace(int space);

    //设置线条宽度
    void setLineWidth(int width);
    //设置线条颜色
    void setLineColor(const QColor &color);

    //设置选中元素样式
    void setBarStyle(const BarStyleType &style);

    //设置键盘按键是否能够移动条目
    void setKeyMoveEnable(bool enable);
    //设置横向显示,如果为假则纵向显示
    void setHorizontal(bool horizontal);
    //设置扁平,默认不扁平
    void setFlat(bool flat);

    //移动到第一个条目
    void moveFirst();
    //移动到最后一个条目
    void moveLast();
    //往前移动条目
    void movePrevious();
    //往后移动条目
    void moveNext();
    //移动到指定索引条目
    void moveTo(int index);
    //移动到指定文字条目
    void moveTo(const QString &item);
    //移动到指定坐标位置条目
    void moveTo(const QPointF &point);

Q_SIGNALS:
    //当前条目改变信号,index为当前条目索引索引 item为当前条目文字
    void currentItemChanged(int index, const QString &item);

protected Q_SLOTS:
    void slide();

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawBar(QPainter *painter);
    void drawText(QPainter *painter);

    QScopedPointer<QEXTNavigationBarPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationBar)
    QEXT_DECL_PRIVATE(QEXTNavigationBar)
};

#endif // _QEXTNAVIGATIONBAR_H
