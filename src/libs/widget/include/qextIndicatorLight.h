/***************************************************************************************************
 *@Brief:高亮发光按钮控件
 * 1:可设置文本,居中显示
 * 2:可设置文本颜色
 * 3:可设置外边框渐变颜色
 * 4:可设置里边框渐变颜色
 * 5:可设置背景色
 * 6:可直接调用内置的设置 绿色/红色/黄色/黑色/蓝色 等公有槽函数
 * 7:可设置是否在容器中可移动,当成一个对象使用
 * 8:可设置是否显示矩形
 * 9:可设置报警颜色+非报警颜色
 * 10:可控制启动报警和停止报警,报警时闪烁
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2019-08-03
 *@History:
***************************************************************************************************/
#ifndef QTKINDICATORLIGHT_H
#define QTKINDICATORLIGHT_H

#include <qextWidgetGlobal.h>
#include <qextobject.h>

#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif

#include <QWidget>
#include <QObject>

class QEXTIndicatorLightPrivate;
class QEXT_WIDGET_API QEXTIndicatorLight : public QWidget, public QEXTObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QColor textLightColor READ lightTextColor WRITE setTextLightColor)
    Q_PROPERTY(QColor textNormalColor READ normalTextColor WRITE setTextNormalColor)
    Q_PROPERTY(QColor backgroundLightColor READ lightBackgroundColor WRITE setBackgroundLightColor)
    Q_PROPERTY(QColor backgroundNormalColor READ normalBackgroundColor WRITE setBackgroundNormalColor)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)

    Q_PROPERTY(QColor borderOutStartColor READ outBorderStartColor WRITE setBorderOutStartColor)
    Q_PROPERTY(QColor borderOutEndColor READ outBorderEndColor WRITE setBorderOutEndColor)
    Q_PROPERTY(QColor borderInStartColor READ inBorderStartColor WRITE setBorderInStartColor)
    Q_PROPERTY(QColor borderInEndColor READ inBorderEndColor WRITE setBorderInEndColor)

    Q_PROPERTY(bool isMoveEnable READ isMoveEnable WRITE setMoveEnable)
    Q_PROPERTY(bool overlayVisiable READ isOverlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(Style styleType READ styleType WRITE setStyleType)
    Q_PROPERTY(Shape shapeType READ shapeType WRITE setShapeType)

    Q_PROPERTY(bool lightState READ lightState WRITE setLightState)
    Q_PROPERTY(bool flickerState READ flickerState WRITE setFlickerState)
    Q_PROPERTY(int flickerInterval READ flickerInterval WRITE setFlickerInterval)

public:
    enum Style {
        Style_Green = 0,        //0-绿色
        Style_Red,              //1-红色
        Style_Yellow,           //2-黄色
        Style_Black,            //3-黑色
        Style_Gray,             //4-灰色
        Style_Blue,             //5-蓝色
        Style_LightBlue,        //6-淡蓝色
        Style_LightRed,         //7-淡红色
        Style_LightGreen        //8-淡绿色
    };
    Q_ENUMS(Style)

    enum Shape {
        Shape_Circle = 0,       //0-圆形
        Shape_Square,           //1-方形
        Shape_Triangle,         //2-三角形
        Shape_Rounded           //3-椭圆形
    };
    Q_ENUMS(Shape)

public:
    explicit QEXTIndicatorLight(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIndicatorLight();

    QString text() const;
    QColor lightTextColor() const;
    QColor normalTextColor() const;
    QColor lightBackgroundColor() const;
    QColor normalBackgroundColor() const;
    int fontPixelSize() const;

    QColor outBorderStartColor() const;
    QColor outBorderEndColor() const;
    QColor inBorderStartColor() const;
    QColor inBorderEndColor() const;

    bool isMoveEnable() const;
    bool isOverlayVisiable() const;
    QColor overlayColor() const;

    Style styleType() const;
    Shape shapeType() const;

    bool lightState() const;
    bool flickerState() const;
    int flickerInterval() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    //设置文本
    void setText(const QString &text);
    //设置文本颜色
    void setTextLightColor(const QColor &color);
    void setTextNormalColor(const QColor &color);

    //设置背景报警颜色+正常颜色
    void setBackgroundLightColor(const QColor &color);
    void setBackgroundNormalColor(const QColor &color);

    void setFontPixelSize(const int &size);

    //设置外边框渐变颜色
    void setBorderOutStartColor(const QColor &color);
    void setBorderOutEndColor(const QColor &color);

    //设置里边框渐变颜色
    void setBorderInStartColor(const QColor &color);
    void setBorderInEndColor(const QColor &color);

    //设置是否可移动
    void setMoveEnable(const bool &enable);
    //设置是否显示遮罩层
    void setOverlayVisiable(const bool &visiable);
    //设置遮罩层颜色
    void setOverlayColor(const QColor &color);

    //设置风格
    void setStyleType(const Style &type);
    void setShapeType(const Shape &type);

    //设置亮、闪烁
    void setLightState(const bool &state);
    void setFlickerState(const bool &state);
    void setFlickerInterval(const int &interval);
    void startFlicker();
    void stopFlicker();

protected Q_SLOTS:
    void flicker();

protected:
    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBorderOut(QPainter *painter);
    void drawBorderIn(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawOverlay(QPainter *painter);

private:
    QEXT_DECL_PRIVATE(QEXTIndicatorLight)
    QEXT_DISABLE_COPY_MOVE(QEXTIndicatorLight)
};

#endif // QTKINDICATORLIGHT_H
