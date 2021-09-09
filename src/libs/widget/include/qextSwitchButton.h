// clang-format off
/***************************************************************************************************
 *@Brief:该文件定义了自定义选择开关控件，可制作成Qtcreator插件使用。
 *          （1）：可设置开关按钮的样式 圆角矩形/内圆形/外圆形/图片；
 *          （2）：可设置选中和未选中时的背景颜色；
 *          （3）：可设置选中和未选中时的滑块颜色；
 *          （4）：可设置显示的文本；
 *          （5）：可设置滑块离背景的间隔；
 *          （6）：可设置圆角角度；
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Version:V0.5
 *@Date:2016-11-06
 *@History:
 *  Modification data:2017-10-17
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
 *  Modification data:2017-11-02
 *  Author:chengxuewen
 *  Brief:  （1）.修复BUG，设置按钮checked状态时按钮滑动条未滑动问题；
 *          （2）.修复BUG，设置按钮外圆角风格时，按钮显示不正常；
 *  Modification data:2018-05-30
 *  Author:chengxuewen
 *  Brief:  （1）.重写为自定义选择按钮私有实现类。
            （2）.增加选择按钮使能颜色设置。
 *  Modification data:2018-06-15
 *  Author:chengxuewen
 *  Brief:  （1）.添加选择按钮使能控制及使能颜色显示。
 *  Modification data:2019-06-26
 *  Author:chengxuewen
 *  Brief:  （1）.添加插件元对象属性导出暴露功能。
 *          （1）.修复最后设置check状态属性时会导致初次显示开关出现绘制slider位置偏差bug。
***************************************************************************************************/

#ifndef QEXTSWITCHBUTTON_H
#define QEXTSWITCHBUTTON_H

#include <qextWidgetGlobal.h>
#include <qextObject.h>

#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif

#include <QWidget>

class QEXTSwitchButtonPrivate;
class QEXT_WIDGET_API QEXTSwitchButton : public QWidget, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int rectRadius READ rectRadius WRITE setRectRadius)
    Q_PROPERTY(bool checked READ checked WRITE setChecked)
    Q_PROPERTY(bool isTextVisiable READ isTextVisiable WRITE setTextVisiable)
    Q_PROPERTY(bool isCircleVisiable READ isCircleVisiable WRITE setCircleVisiable)
    Q_PROPERTY(bool isAnimationEnable READ isAnimationEnable WRITE setAnimationEnable)
    Q_PROPERTY(Style styleType READ styleType WRITE setStyleType)

    Q_PROPERTY(QColor backgroundOffColor READ backgroundOffColor WRITE setOffBackgroundColor)
    Q_PROPERTY(QColor backgroundOnColor READ backgroundOnColor WRITE setOnBackgroundColor)
    Q_PROPERTY(QColor sliderOffColor READ sliderOffColor WRITE setOffSliderColor)
    Q_PROPERTY(QColor sliderOnColor READ sliderOnColor WRITE setOnSliderColor)
    Q_PROPERTY(QColor textOffColor READ textOffColor WRITE setOffTextColor)
    Q_PROPERTY(QColor textOnColor READ textOnColor WRITE setOnTextColor)

    Q_PROPERTY(QString offText READ offText WRITE setOffText)
    Q_PROPERTY(QString onText READ onText WRITE setOnText)

public:
    enum Style
    {
        Style_Rect = 0,       //圆角矩形
        Style_CircleIn = 1,   //内圆形
        Style_CircleOut = 2   //外圆形
    };
    Q_ENUMS(Style)

    explicit QEXTSwitchButton(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSwitchButton();

    int space() const;
    int rectRadius() const;
    bool checked() const;
    bool isTextVisiable() const;
    bool isCircleVisiable() const;
    bool isAnimationEnable() const;

    Style styleType() const;

    QColor backgroundOffColor() const;
    QColor backgroundOnColor() const;
    QColor sliderOffColor() const;
    QColor sliderOnColor() const;
    QColor textOffColor() const;
    QColor textOnColor() const;

    QString offText() const;
    QString onText() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int radius);
    //设置是否选中
    void setChecked(bool checked);
    //设置是否显示文字
    void setTextVisiable(bool visiable);
    //设置是否显示小圆
    void setCircleVisiable(bool visiable);
    //设置是否动画过渡
    void setAnimationEnable(bool enable);

    //设置风格样式
    void setStyleType(const Style &style);

    //设置背景颜色
    void setOffBackgroundColor(const QColor &color);
    void setOnBackgroundColor(const QColor &color);

    //设置滑块颜色
    void setOffSliderColor(const QColor &color);
    void setOnSliderColor(const QColor &color);

    //设置文字颜色
    void setOffTextColor(const QColor &color);
    void setOnTextColor(const QColor &color);

    //设置文字
    void setOffText(const QString &text);
    void setOnText(const QString &text);

Q_SIGNALS:
    void checkedChanged(bool checked);

protected:
    void mousePressEvent(QMouseEvent *) QEXT_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawSlider(QPainter *painter);

private Q_SLOTS:
    void change();
    void updateValue();

private:
    QEXT_DECL_PRIVATE(QEXTSwitchButton)
    QEXT_DISABLE_COPY_MOVE(QEXTSwitchButton)
};

#endif // QEXTSWITCHBUTTON_H

// clang-format on
